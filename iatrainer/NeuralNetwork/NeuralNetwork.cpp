//
// Created by gaspar_q on 6/14/16.
//

#include <iostream>
#include <tgmath.h>
#include <valarray>
#include <sstream>
#include <boost/property_tree/ptree.hpp>
#include "NeuralNetwork.hpp"

NeuralNetwork::NeuralNetwork(Layer const &in, std::vector<size_t> const &neuronsPerLayer, size_t nbOutput,
                             const std::function<double(double)> &activationFunction) :
    inputs(in),
    outputs(nbOutput),
    activationFunction(activationFunction)
{
    Layer   *prevLayer = &inputs;

    for (size_t i = 0, max = neuronsPerLayer.size(); i < max; ++i)
    {
        hiddenLayers.push_back(Layer(neuronsPerLayer[i], *prevLayer));
        prevLayer = &hiddenLayers.back();
    }
    outputs.LinkTo(*prevLayer);
}

NeuralNetwork::NeuralNetwork(NeuralNetwork const &ref) :
    inputs(ref.inputs),
    outputs(ref.outputs),
    activationFunction(ref.activationFunction),
    hiddenLayers(ref.hiddenLayers)
{
    if (hiddenLayers.size() == 0)
    {
        outputs.LinkTo(inputs);
    }
    else
    {
        hiddenLayers[0].LinkTo(inputs);
        outputs.LinkTo(hiddenLayers.back());
    }
}

NeuralNetwork::NeuralNetwork()
{

}

NeuralNetwork::~NeuralNetwork()
{

}

NeuralNetwork &NeuralNetwork::operator=(NeuralNetwork const &ref)
{
    inputs = ref.inputs;
    outputs = ref.outputs;
    activationFunction = ref.activationFunction;
    hiddenLayers = ref.hiddenLayers;
    return *this;
}

double NeuralNetwork::sigmoid(double x)
{
    return 1.0 / (1.0 + exp(-x));
}

Layer const &NeuralNetwork::Compute(Layer const &inp)
{
    if (inp.size() != 0)
        inputs.Copy(inp);
    for (Layer &curr : hiddenLayers)
    {
        curr.Compute(activationFunction);
    }
    outputs.Compute([](double i) { return (i); });
    return outputs;
}

double &NeuralNetwork::operator[](int i)
{
    return inputs[i];
}

void NeuralNetwork::SetInputs(std::vector<Neuron> const &inp)
{
    for (size_t i = 0, max = inp.size(); i < max; ++i)
    {
        inputs[i] = inp[i].Value();
    }
}

std::vector<Layer> const &NeuralNetwork::Layers(void) const
{
    return hiddenLayers;
}

std::vector<Layer> &NeuralNetwork::Layers(void)
{
    return hiddenLayers;
}

size_t NeuralNetwork::getInputSize(void) const
{
    return inputs.size();
}

void NeuralNetwork::deserialize(boost::property_tree::ptree &ptree)
{
    boost::property_tree::ptree layers, output;
    Layer   *prevLayer = &inputs;

    layers = ptree.get_child("layers");
    output = ptree.get_child("output");
    inputs.setNbOfNeurons(ptree.get<size_t>("inputs"));
    hiddenLayers.clear();
    outputs.clear();
    for (std::pair<const std::string, boost::property_tree::ptree> &currLayer : layers)
    {
        hiddenLayers.push_back(Layer());
        hiddenLayers.back().derialize(currLayer.second, *prevLayer);
        prevLayer = &hiddenLayers.back();
    }
    outputs.derialize(output, *prevLayer);
}

Layer const &NeuralNetwork::Outputs(void) const
{
    return outputs;
}

std::ostream    &operator<<(std::ostream &output, NeuralNetwork const &ref)
{
    boost::property_tree::ptree layers, ptree;

    ptree.put("inputs", ref.getInputSize());
    for (Layer const &curr : ref.Layers())
    {
        layers.push_back(std::make_pair("", curr.serialize()));
    }
    ptree.push_back(std::make_pair("layers", layers));
    layers.clear();
    ptree.push_back(std::make_pair("output", ref.Outputs().serialize()));
    boost::property_tree::write_json(output, ptree, true);
    return output;
}

std::istream    &operator>>(std::istream &input, NeuralNetwork &ref)
{
    boost::property_tree::ptree ptree;

    boost::property_tree::read_json(input, ptree);
    ref.deserialize(ptree);
    return input;
}