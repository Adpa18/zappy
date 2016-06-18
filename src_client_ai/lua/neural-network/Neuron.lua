--
-- Created by IntelliJ IDEA.
-- User: gaspar_q
-- Date: 6/16/16
-- Time: 7:31 PM
-- To change this template use File | Settings | File Templates.
--

local Neuron = {}

function Neuron.new()
    return {synapses = {}, value = 0};
end

function Neuron.link(this, neuronToLink, weight)
    this[#this.synapses + 1] = {neuron = neuronToLink, weight = weight};
end

function Neuron.compute(this)
    this.value = 0;
    for obj in this.synapses do
        this.value = this.value + obj.neuron.value * obj.weight;
    end
    return this.value;
end

function Neuron.activate(this, actFunc)
    this.value = actFunc(this.value);
    return this.value;
end

return Neuron;