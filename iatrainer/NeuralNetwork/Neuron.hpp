//
// Created by gaspar_q on 6/14/16.
//

#ifndef NEURALNETWORK_NEURON_HPP
#define NEURALNETWORK_NEURON_HPP

#include <functional>
#include <vector>
#include <map>

class Neuron
{
public:
    Neuron(double val = 0, std::map<Neuron *, double> const &links = {});
    Neuron(Neuron const &ref);
    ~Neuron();
    Neuron  &operator=(Neuron const &ref);

public:
    double activate(std::function<double (double)> const &activationFunction);
    void   linkTo(Neuron *neuron, double weight);
    double &operator[](Neuron *neuron);
    double const &operator[](Neuron *neuron) const;
    std::map<Neuron *, double> const &Links(void) const;
    double Compute(void);
    double &Value(void);
    double const &Value(void) const;

private:
    double value;
    std::map<Neuron *, double>  links;
};

std::ostream    &operator<<(std::ostream &output, Neuron const &ref);

#endif //NEURALNETWORK_NEURON_HPP
