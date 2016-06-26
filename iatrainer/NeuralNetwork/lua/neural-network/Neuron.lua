--
-- Created by IntelliJ IDEA.
-- User: gaspar_q
-- Date: 6/16/16
-- Time: 7:31 PM
-- To change this template use File | Settings | File Templates.
--

local Neuron = {}

local path = debug.getinfo(1).source:match("@?(.*/)") or "";

local json = require(path.."json/json");

function Neuron.new()
    return {synapses = {}, value = 0};
end

function Neuron.link(this, neuronToLink, weight)
    this.synapses[#this.synapses + 1] = {neuron = neuronToLink, weight = weight};
end

function Neuron.compute(this)
    this.value = 0;
    for i=1, #this.synapses do
        this.value = this.value + this.synapses[i].neuron.value * this.synapses[i].weight;
    end
    return this.value;
end

function Neuron.setWeights(this, prevneurons, weights)
    this.synapses = {};
    for i=1, #prevneurons do
        this.synapses[i] = {neuron = prevneurons[i], weight = weights[i]};
    end
end

function Neuron.activate(this, actFunc)
    this.value = actFunc(this.value);
    return this.value;
end

function Neuron.getWeights(this)
    local weights = {};

    for i=1, #this.synapses do
        weights[i] = this.synapses[i].weight;
    end
    return weights;
end

return Neuron;