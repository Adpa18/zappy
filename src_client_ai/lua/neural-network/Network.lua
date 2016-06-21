--
-- Created by IntelliJ IDEA.
-- User: gaspar_q
-- Date: 6/16/16
-- Time: 7:26 PM
-- To change this template use File | Settings | File Templates.
--

local path = debug.getinfo(1).source:match("@?(.*/)") or "";

local layer = require(path.."Layer");
local json = require(path.."json/json");

local NeuralNetwork = {}

local function sigmoid(x)
    return  1.0 / (1.0 + math.exp(-x));
end

--[[
--Neural Network constructor
-- nbInput  Number of inputs present in the network
-- nbOutput Number of outputs of the Network
-- layersNb Array with the number of neurons in each layers of the network
 ]]
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
        layer.compute(this.layers[i], sigmoid);
    end
    layer.compute(this.output, sigmoid);
    return this.output;
end

function NeuralNetwork.deserialize(filename)
    local file = assert(io.open(filename, "r"))
    local neur = json.decode(file:read("*all"));
    local toret = NeuralNetwork.new(neur.inputs, #neur.output);
    local prevLayer = toret.input;

    for i=1, #neur.layers do
        toret.layers[i] = layer.new(#neur.layers[i]);
        layer.SetSynapsesWeight(toret.layers[i], neur.layers[i], prevLayer);
        prevLayer = toret.layers[i];
    end
    layer.SetSynapsesWeight(toret.output, neur.output, prevLayer);
    file:close();
    return toret;
end

function NeuralNetwork.serialize(this, filename)
    local file = assert(io.open(filename, "w"));
    local toEncode = {};

    toEncode.output = layer.getNeuronsWeight(this.output);
    toEncode.layers = {};
    for i=1, #this.layers do
        toEncode.layers[i] = layer.getNeuronsWeight(this.layers[i]);
    end
    toEncode.inputs = #this.input.neurons;
    file:write(json.encode(toEncode));
    file:close();
end

return NeuralNetwork;