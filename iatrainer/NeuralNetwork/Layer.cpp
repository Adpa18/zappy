#include <iostream>
#include <sstream>
#include <boost/foreach.hpp>
#include "Layer.hpp"

Layer::Layer(size_t nbNeurons, Layer &prevLayer)
{
    for (size_t i = 0; i < nbNeurons; ++i)
    {
        Neuron  topush;

        LinkNeuronTo(topush, prevLayer);
        push_back(topush);
    }
}

Layer::Layer()
{

}

Layer::Layer(std::initializer_list<Neuron> const &init) :
        std::vector<Neuron>(init)
{

}

Layer::Layer(size_t nbNeurons)
{
    setNbOfNeurons(nbNeurons);
}

Layer::Layer(Layer const &ref) :
    std::vector<Neuron>(ref)
{

}

void Layer::LinkNeuronTo(Neuron &toLink, Layer &ref)
{
    for (Neuron &curr : ref)
    {
        toLink[&curr] = static_cast<double>(rand() % 100) / 100.0;
    }
}

void Layer::LinkTo(Layer &ref)
{
    for (Neuron &curr : *this)
    {
        LinkNeuronTo(curr, ref);
    }
}

void Layer::Compute(std::function<double (double)> const &activationFunction)
{
    for (Neuron &curr : *this)
    {
        curr.Compute();
        curr.activate(activationFunction);
    }
}

double &Layer::operator[](size_t i)
{
    return at(i).Value();
}

double const &Layer::operator[](size_t i) const
{
    return at(i).Value();
}

Layer::Layer(const std::vector<Neuron> &ref) :
    std::vector<Neuron>(ref)
{

}

boost::property_tree::ptree Layer::serialize(void) const
{
    boost::property_tree::ptree neurons;

    for (Neuron const &neur : *this)
    {
        boost::property_tree::ptree neuron;

        for (std::pair<Neuron *, double> const &weg : neur.Links())
        {
            boost::property_tree::ptree we;

            we.put("", weg.second);
            neuron.push_back(std::make_pair("", we));
        }
        neurons.push_back(std::make_pair("", neuron));
    }
    return neurons;
}

void Layer::derialize(boost::property_tree::ptree &ptree, Layer &prevLayer)
{
    clear();
    for (std::pair<const std::string, boost::property_tree::ptree> &neuron : ptree)
    {
        Neuron  newNeuron;
        size_t i = 0, max = prevLayer.size();

        for (std::pair<const std::string, boost::property_tree::ptree> &weight : neuron.second)
        {
            newNeuron[&prevLayer.at(i++)] = weight.second.get<double>("");
            if (i == max)
                break;
        }
        push_back(newNeuron);
    }
}

void Layer::setNbOfNeurons(size_t nb)
{
    clear();
    for (size_t i = 0; i < nb; ++i)
    {
        push_back(Neuron());
    }
}

void Layer::Copy(Layer const &toCopy)
{
    size_t i = 0;

    if (size() != toCopy.size())
        throw std::logic_error("Attempt to copy layers of different size");
    for (Neuron const &curr : toCopy)
    {
        at(i).Value() = curr.Value();
        ++i;
    }
}

std::ostream    &operator<<(std::ostream &output, Layer const &layer)
{
    size_t max = layer.size();
    size_t i = 0;

    output << "{";
    for (Neuron const &curr : layer)
    {
        output << curr;
        ++i;
        if (i < max)
            output << ", ";
    }
    output << "}";
    return output;
}
