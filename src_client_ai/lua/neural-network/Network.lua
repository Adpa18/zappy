--
-- Created by IntelliJ IDEA.
-- User: gaspar_q
-- Date: 6/16/16
-- Time: 7:26 PM
-- To change this template use File | Settings | File Templates.
--

layer = require "Layer";
json = require "json/json";

local NeuralNetwork = {}

function NeuralNetwork.new(nbInput, nbOutput, layersNb)
    local toret = {input = {}, output = {}, layers = {}};

    layersNb = layersNb or {};
    nbInput = nbInput or 1;
    nbOutput = nbOutput or 1;
    toret.input = layer.new(nbInput);

    local prevLayer = {ref = toret.input};

    for i=1, #layersNb do
        toret.layers[i] = layer.new(layersNb[i], prevLayer.ref);
        prevLayer.ref = toret.layers[i];
    end
    toret.output = layer.new(nbOutput, prevLayer.ref);
    return toret;
end

function NeuralNetwork.setInputs(this, inputs)
    layer.copy(this.input, inputs);
end

function NeuralNetwork.compute(this, inputs)
    if (inputs ~= nil) then
        layer.copy(this.input, inputs);
    end
    for i=1, #this.layers do
        layer.compute(this.layers[i], function (x)
            return  1.0 / (1.0 + math.exp(-x));
        end);
    end
    layer.compute(this.output, function (x) return x; end);
    return this.output;
end

function NeuralNetwork.deserialize(filename)
    local neur = json.decode(filename);
    local toret = NeuralNetwork.new(neur.inputs, #neur.output);
    local prevLayer = toret.input;

    for i=1, #toret.layers do
        toret.layers[i] = Layer.new(neur.layers[i]);
        Layer.SetSynapsesWeight(toret.layers[i], neur.layers[i], prevLayer);
        prevLayer = toret.layers[i];
    end
    return toret;
end

return NeuralNetwork;