//
// Created by gaspar_q on 6/15/16.
//

#ifndef NEURALNETWORK_GENETICALGORITHM_HPP
#define NEURALNETWORK_GENETICALGORITHM_HPP

#include <cstdlib>
#include <vector>
#include "NeuralNetwork.hpp"

class GeneticAlgorithm
{
public:
    typedef std::map<size_t, NeuralNetwork> Generation;
    GeneticAlgorithm(size_t popSize, size_t mutRatio, size_t mutAmp, size_t selectRatio,
                     size_t inputNb, std::vector<size_t> const &layerSchema, size_t outputNb);
    GeneticAlgorithm(GeneticAlgorithm const &ref);
    ~GeneticAlgorithm();
    GeneticAlgorithm    &operator=(GeneticAlgorithm const &ref) = delete;

public:
    NeuralNetwork   Procreate(NeuralNetwork const &mother, NeuralNetwork const &father) const;
    Generation      GeneratePopulation(Generation const &prevPopulation = {}) const;
    NeuralNetwork   Run(std::function<int(Generation &)> const &runAndSort, size_t maxIteration = 100) const;

private:
    size_t GetRandPopIndex(void) const;
    double GetMutationValue(void) const;
    bool   CanMute(void) const;

private:
    const size_t popSize;
    const size_t mutRatio;
    const size_t mutAmp;
    const size_t selectRatio;
    const size_t inputNb;
    const std::vector<size_t > layerSchema;
    const size_t outputNb;
};

#endif //NEURALNETWORK_GENETICALGORITHM_HPP
