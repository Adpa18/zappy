--
-- Created by IntelliJ IDEA.
-- User: gaspar_q
-- Date: 6/16/16
-- Time: 7:31 PM
-- To change this template use File | Settings | File Templates.
--

neuron = require "Neuron";

local Layer = {}

function Layer.setNbNeurons(this, nbNeurons)
    print("of "..nbNeurons.." neurons");
    this.neurons = {};
    for i=1, nbNeurons do
        this.neurons[i] = neuron.new();
    end
end

function Layer.link(this, prevLayer)
    print("linked to ");
    print(prevLayer);
    for i=1, #this.neurons do
        print("i: "..i);
        for j=1, #prevLayer.neurons do
            neuron.link(this.neurons[i], prevLayer.neurons[j], math.random(0, 100) / 100);
        end
        print("===>ok");
    end
end

function Layer.new(nbNeuron, prevLayer)
    local lay = {neurons = {}};

    print("creating a layer");
    if (nbNeuron ~= nil) then
        Layer.setNbNeurons(lay, nbNeuron);
    end
    if (prevLayer ~= nil) then
        Layer.link(lay, prevLayer);
    end
    return lay;
end

function Layer.compute(this, actFunc)
    for i=1, #this.neurons do
        neuron.compute(this.neurons[i]);
        neuron.activate(this.neurons[i], actFunc);
    end
end

function Layer.copy(this, tocopy)
    for i=1, #tocopy do
        this.neurons[i].value = tocopy[i];
    end
end

return Layer;