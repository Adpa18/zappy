//
// Created by gaspar_q on 6/14/16.
//

#ifndef NEURALNETWORK_NEURALNETWORK_HPP
#define NEURALNETWORK_NEURALNETWORK_HPP

#include <vector>
#include "Layer.hpp"

class NeuralNetwork
{
public:
    NeuralNetwork();
    NeuralNetwork(Layer const &inputs, std::vector<size_t > const &neuronsPerLayer = {},  size_t nbOutput = 1,
                  std::function<double(double)> const &activationFunction = NeuralNetwork::sigmoid);
    NeuralNetwork(NeuralNetwork const &ref);
    ~NeuralNetwork();
    NeuralNetwork   &operator=(NeuralNetwork const &ref);

public:
    Layer const &Compute(Layer const &inp = {});
    double &operator[](int i);
    void    SetInputs(std::vector<Neuron> const &inp);
    std::vector<Layer>  const &Layers(void) const;
    std::vector<Layer>  &Layers(void);
    size_t getInputSize(void) const;
    void deserialize(boost::property_tree::ptree &ptree);
    Layer const &Outputs(void) const;

public:
    static double sigmoid(double x);

private:
    Layer                           inputs;
    Layer                           outputs;
    std::function<double (double)>  activationFunction;
    std::vector<Layer>              hiddenLayers;
};

std::ostream    &operator<<(std::ostream &output, NeuralNetwork const &ref);
std::istream    &operator>>(std::istream &input, NeuralNetwork &ref);

#endif //NEURALNETWORK_NEURALNETWORK_HPP
