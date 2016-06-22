#include <iomanip>
#include <Socket.hpp>
#include <stdexcept>
#include "Core.hpp"

int main(int ac, char **av)
{
#ifdef _WIN32
    Socket::WinSocket(Socket::START);
#endif
    Core core;

    try
    {
        core.parseArg(ac, av);
    }
    catch (std::exception &error)
    {
        if (!std::string(error.what()).empty())
            std::cerr << "Zappy AI:" << std::endl << "\t" << error.what() << std::endl;
        return 1;
    }
    std::cout << "ip : " << core.getIp() << std::endl;
    std::cout << "port : " << core.getPort() << std::endl;
    std::cout << "team name : " << core.getTeamName() << std::endl;
    std::cout << "IA : " << core.getFileIA() << std::endl;
    int status = core.run();
#ifdef  _WIN32
    Socket::WinSocket(Socket::STOP);
#endif
    return (status);
}
