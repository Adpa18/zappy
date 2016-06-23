//
// Created by gaspar_q on 6/14/16.
//

#include <iostream>
#include <sstream>
#include "Neuron.hpp"

Neuron::Neuron(double val, std::map<Neuron *, double> const &links) :
    value(val),
    links(links)
{

}

Neuron::Neuron(Neuron const &ref) :
    Neuron(ref.value, ref.links)
{

}

Neuron::~Neuron()
{

}

Neuron &Neuron::operator=(Neuron const &ref)
{
    value = ref.value;
    links = ref.links;
    return *this;
}

double Neuron::activate(std::function<double(double)> const &activationFunction)
{
    value = activationFunction(value);
    return value;
}

void Neuron::linkTo(Neuron *neuron, double weight)
{
    links[neuron] = weight;
}

double &Neuron::operator[](Neuron *neuron)
{
    return links[neuron];
}

std::map<Neuron *, double> const &Neuron::Links(void) const
{
    return links;
}

double const &Neuron::operator[](Neuron *neuron) const
{
    std::map<Neuron *, double >::const_iterator it = links.find(neuron);

    return it->second;
}

double Neuron::Compute(void)
{
    value = 0;
    for (std::pair<Neuron *, double> const &curr : links)
    {
        value += curr.first->value * curr.second;
    }
    return value;
}

double &Neuron::Value(void)
{
    return value;
}

double const &Neuron::Value(void) const
{
    return value;
}

std::ostream    &operator<<(std::ostream &output, Neuron const &ref)
{
    output << ref.Value();
    return output;
}