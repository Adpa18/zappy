#include "Core.hpp"

/**
 * TODO:
 *  -   Class de déserialisation du pseudo JSON
 */
int main(int ac, char **av)
{
    Core core;

    if (core.parseArg(ac, av) != 0)
        return (1);
    std::cout << "ip : " << core.getIp() << std::endl;
    std::cout << "port : " << core.getPort() << std::endl;
    std::cout << "team name : " << core.getTeamName() << std::endl;
    std::cout << "IA : " << core.getFileIA() << std::endl;
    return (core.run());
}
