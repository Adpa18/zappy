#include <iomanip>
#include <Socket.hpp>
#include "Core.hpp"

int main(int ac, char **av)
{
    Core core;

    try
    {
        core.parseArg(ac, av);
    }
    catch (ParsingError &error)
    {
        if (!std::string(error.what()).empty())
            std::cerr << "Zappy AI:" << std::endl << "\t" << error.what() << std::endl;
        return 1;
    }
    std::cout << "ip : " << core.getIp() << std::endl;
    std::cout << "port : " << core.getPort() << std::endl;
    std::cout << "team name : " << core.getTeamName() << std::endl;
    std::cout << "IA : " << core.getFileIA() << std::endl;
    return (core.run());
}
