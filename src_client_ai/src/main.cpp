#include <iomanip>
#include <Socket.hpp>
#include "Core.hpp"

/**
 * TODO:
 *  -   Class de déserialisation du pseudo JSON
 */
int main(int ac, char **av)
{
    Core core;
    int status;

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
#ifdef _WIN32
    Socket::WinSocket(Socket::START);
#endif
    std::cout << "ip : " << core.getIp() << std::endl;
    std::cout << "port : " << core.getPort() << std::endl;
    std::cout << "team name : " << core.getTeamName() << std::endl;
    std::cout << "IA : " << core.getFileIA() << std::endl;
    status = core.run();
#ifdef  _WIN32
    Socket::WinSocket(Socket::STOP);
#endif
    return (status);
}
