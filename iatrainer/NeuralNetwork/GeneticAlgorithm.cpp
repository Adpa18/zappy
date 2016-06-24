//
// Created by gaspar_q on 6/15/16.
//

#include "GeneticAlgorithm.hpp"

/**
 * \brief Constructor that initialise the GeneticAlgorithm parameters
 * \param popSize The population size at each iterations
 * \param mutRation The mutation ratio that decide if a Network can mute
 * \param mutAmp The mutation amplitude that act on the mutation value
 * \param selectRatio The selection ratio that choose the percentage of the population that will be used for the mutation process
 * \param inputNb The number of inputs for the generated networks
 * \param layerSchema The schema of the hidden layers of the generated networks
 * \param outputNb The number of outputs in the generated networks
 */
GeneticAlgorithm::GeneticAlgorithm(size_t popSize, size_t mutRatio, size_t mutAmp, size_t selectRatio,
                                   size_t inputNb, std::vector<size_t> const &layerSchema, size_t outputNb) :
    popSize(popSize),
    mutRatio(mutRatio),
    mutAmp(mutAmp),
    selectRatio(selectRatio),
    inputNb(inputNb),
    layerSchema(layerSchema),
    outputNb(outputNb)
{
    std::cout << "Pop size: " << popSize << std::endl;
    std::cout << "Mutation ratio: " << mutRatio << std::endl;
    std::cout << "Mutation amplitude: " << mutAmp << std::endl;
    std::cout << "Selection ratio: " << selectRatio << std::endl;
    std::cout << "Input nb: " << inputNb << std::endl;
    std::cout << "Layer schema: {" << std::endl;
    for (size_t const &curr : layerSchema)
    {
        std::cout << "\t" << curr << "," << std::endl;
    }
    std::cout << "}" << std::endl;
    std::cout << "Output nb: " << outputNb << std::endl;
    srand(static_cast<unsigned int>(time(NULL)));
}

/**
 * \brief Copy constructor that will copy all the parameters given in the first constructor
 */
GeneticAlgorithm::GeneticAlgorithm(GeneticAlgorithm const &ref) :
    GeneticAlgorithm(ref.popSize, ref.mutRatio, ref.mutAmp, ref.selectRatio, ref.inputNb, ref.layerSchema, ref.outputNb)
{

}

/**
 * \brief Destructor that does nothing
 */
GeneticAlgorithm::~GeneticAlgorithm()
{

}

/**
 * \brief Get the random population index for choosing a mother or a father during the mutation process
 * \return The index of a random individual in the population
 */
size_t GeneticAlgorithm::GetRandPopIndex(void) const
{
    return rand() % static_cast<size_t >(popSize * static_cast<double>(selectRatio / 100));
}

/**
 * \brief Get the mutation value that will be used in the addition of the weights
 * \return The mutation value in the mutation process
 */
double GeneticAlgorithm::GetMutationValue(void) const
{
    return ((static_cast<double>(rand() % 20000) - 10000.0) / 10000.0) * mutAmp;
}

/**
 * \brief Check if a gene of a network can mute
 * \return If a gene of a network can mute
 */
bool GeneticAlgorithm::CanMute(void) const
{
    return rand() % 100 < mutRatio;
}

/**
 * \brief Will generatie a new population in function of the previous population
 * \param prevPopulation The previous population used for mute the new population, give no parameter or give invalid parameter provoke completely new generation
 * \return A new generation create
 */
GeneticAlgorithm::Generation GeneticAlgorithm::GeneratePopulation(const Generation &prevPopulation) const
{
    Generation  generation;
    bool proc = (prevPopulation.size() == popSize);

    if (proc)
        generation[0] = prevPopulation.find(0)->second;
    for (size_t i = (proc ? 1 : 0); i < popSize; ++i)
    {
        if (proc)
        {
            std::cout << "Procreating" << std::endl;
            generation[i] = Procreate(prevPopulation.find(GetRandPopIndex())->second, prevPopulation.find(GetRandPopIndex())->second);
        }
        else
        {
            std::cout << "Creating" << std::endl;
            std::ifstream   input("neural/neural_" + std::to_string(i) + ".json");

            if (input.is_open())
            {
                input >> generation[i];
                input.close();
            }
            else
                generation[i] = NeuralNetwork(inputNb, layerSchema, outputNb);
        }
        std::cout << "generation[" << i << "] = " << generation[i] << std::endl;
    }
    return generation;
}

/**
 * \brief Will create a new neural network in function of its mother and its father
 * \param mother The mother of the child procreated
 * \param father The father of the child procreated
 * \return A child create from its mother and its father
 */
NeuralNetwork GeneticAlgorithm::Procreate(NeuralNetwork const &mother, NeuralNetwork const &father) const
{
    NeuralNetwork   child(inputNb, layerSchema, outputNb);

    for (size_t lay = 0, maxLay = layerSchema.size(); lay < maxLay; ++lay)
    {
        Layer   &layer = child.Layers()[lay];
        Layer const &motherLay = mother.Layers()[lay];
        Layer const &fatherLay = father.Layers()[lay];
        size_t i = 0;

        for (size_t max = rand() % (layer.size() + 1); i < max; ++i)
        {
            layer[i] = motherLay[i];
            if (CanMute())
                layer[i] += GetMutationValue();
        }
        for (size_t max = layer.size(); i < max; ++i)
        {
            layer[i] = fatherLay[i];
            if (CanMute())
                layer[i] += GetMutationValue();
        }
    }
    return child;
}

/**
 * \brief Will run the genetic algorithm with its function of run and sort, and its maximum iteration
 * \param runAndSort The function of running and sorting call just before regenerating a new generation
 * \param maxIteration The maximum number of iterations for the genetic algorithm
 * \return The best neural network generated
 */
NeuralNetwork GeneticAlgorithm::Run(std::function<int(Generation &)> const &runAndSort, size_t maxIteration) const
{
    Generation   generation = GeneratePopulation();

    for (size_t i = 0; i < maxIteration; ++i)
    {
        std::cout << "itération" << std::endl;
        if (runAndSort(generation) == 1)
            break;
        generation = GeneratePopulation(generation);
    }
    return generation[0];
}
