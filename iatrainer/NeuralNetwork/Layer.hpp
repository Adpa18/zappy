//
// Created by gaspar_q on 6/14/16.
//

#ifndef NEURALNETWORK_LAYER_HPP
#define NEURALNETWORK_LAYER_HPP

#include <vector>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include "Neuron.hpp"

class Layer : public std::vector<Neuron>
{
public:
    Layer();
    Layer(std::initializer_list<Neuron> const &init);
    Layer(std::vector<Neuron> const &ref);
    Layer(Layer const &ref);
    Layer(size_t nbNeurons, Layer &prevLayer);
    Layer(size_t nbNeurons);

public:
    void LinkNeuronTo(Neuron &toLink, Layer &ref);
    void LinkTo(Layer &ref);
    void Compute(std::function<double (double)> const &activationFunction);
    boost::property_tree::ptree serialize(void) const;
    void derialize(boost::property_tree::ptree &ptree, Layer &prevLayer);
    double &operator[](size_t i);
    double const &operator[](size_t i) const;
    void setNbOfNeurons(size_t nb);
    void Copy(Layer const &toCopy);
};

std::ostream    &operator<<(std::ostream &output, Layer const &layer);

#endif //NEURALNETWORK_LAYER_HPP
