#include <iostream>
#include <wait.h>
#include "NeuralNetwork.hpp"
#include "GeneticAlgorithm.hpp"
#include "UnsortMap.hpp"

std::vector<size_t >        getLayerSchema(int ac, char **av)
{
    std::vector<size_t >    layerSchema;

    for (int i = 1; i < ac; ++i)
    {
        layerSchema.push_back(static_cast<size_t >(atol(av[i])));
    }
    return layerSchema;
}

size_t  resolvePoints(std::string const &filename, size_t num)
{
    std::ifstream   neurInput(filename);
    size_t score = num;

    if (neurInput.is_open())
    {
        std::stringstream stringstream;
        std::string filecontent;
        std::string upmsg("You have been upgraded");
        size_t i;

        stringstream << neurInput.rdbuf();
        filecontent = stringstream.str();
        while ((i = filecontent.find(upmsg)) != std::string::npos)
        {
            size_t off = i + upmsg.size();

            score += 5;
            filecontent = filecontent.substr(off, filecontent.size() - off);
        }
    }
    return score;
}

std::map<NeuralNetwork, size_t>::const_iterator TopRank(std::map<NeuralNetwork, size_t> const &points)
{
    std::map<NeuralNetwork, size_t>::const_iterator max = points.end();

    for (std::map<NeuralNetwork, size_t>::const_iterator it = points.begin(), end = points.end(); it != end; ++it)
    {
        if (max == points.end() || max->second < it->second)
        {
            max = it;
        }
    }
    return max;
}

GeneticAlgorithm::Generation    rankPlayers(UnsortMap<size_t , size_t> &points, GeneticAlgorithm::Generation &generation)
{
    GeneticAlgorithm::Generation    ranked;
    size_t currRank = 0;

    while (!points.empty())
    {
        UnsortMap<size_t , size_t>::iterator max, it, end;

        for (it = points.begin(), end = points.end(), max = end; it != end; ++it)
        {
            if (max == end || max->second < it->second)
                max = it;
        }
        ranked[currRank] = generation[max->first];
        points.erase(max);
    }
    return ranked;
}

int     zappyIaGeneration(GeneticAlgorithm::Generation &generation)
{
    std::map<pid_t, size_t >  pids;
    UnsortMap<size_t , size_t> pointsPerNetwork;
    std::map<pid_t, size_t >::const_iterator it;
    size_t rank = 0;

    std::cout << "starting" << std::endl;
    for (std::pair<const size_t, NeuralNetwork> &curr : generation)
    {
        pid_t pid;

        if ((pid = fork()) == -1)
            return 1;
        if (pid == 0)
        {
            //todo implement a system to associate the curr neural network to a iaclient script
            std::string     filename("neural/neural_" + std::to_string(rank) + ".json");
            std::string     output("log/output_" + std::to_string(rank) + ".log");
            std::ofstream   serial(filename);

            std::cout << "\e[32mprocess launched\e[0m" << std::endl;
            if (!serial.is_open())
                exit(-1);
            serial << curr.second;
            serial.close();
            std::cout << "\e[31mlaunched\e[0m" << std::endl;
            if (execl("/bin/bash", "bash", "-c", ("echo " + filename + " | ./zappy_ai -p 4242 -n toto -s ./lua/neuralia.lua > " + output).c_str(), NULL) == -1)
                exit(1);
            exit(0);
        }
        pids[pid] = curr.first;
        ++rank;
    }
    rank = 0;
    it = pids.begin();
    while (!pids.empty())
    {
        if (it == pids.end())
            it = pids.begin();
        int status;
        if (waitpid(it->first, &status, WNOHANG) != 0)
        {
            pointsPerNetwork[it->second] = resolvePoints("log/output_" + std::to_string(it->first) + ".log", rank++);
            it = pids.erase(it);
        }
        else
            ++it;
    }
    generation = rankPlayers(pointsPerNetwork, generation);
    return 0;
}

int main(int ac, char **av)
{
    GeneticAlgorithm    geneticAlgorithm(10, 50, 1, 10, 6, getLayerSchema(ac, av), 6);
    std::ofstream       finalNetwork("final" + std::to_string(time(NULL)) + ".json");

    if (finalNetwork.is_open())
    {
        std::cout << "on passe ici" << std::endl;
        finalNetwork << geneticAlgorithm.Run(zappyIaGeneration);
    }
    else
    {
        std::cerr << "File cannot be open" << std::endl;
        return 1;
    }
    return 0;
}
