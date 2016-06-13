//
// Core.cpp for zappy in /home/tavern_d/rendu/semestre4/PSU_2015_zappy/src_client_ai
// 
// Made by Matthieu Tavernier
// Login   <tavern_d@epitech.net>
// 
// Started on  Wed Jun  8 11:40:42 2016 Matthieu Tavernier
// Last update Mon Jun 13 13:44:39 2016 Matthieu Tavernier
//

#include "Core.hpp"
#include "IAClient.hpp"

const std::string Core::usage = "-n team_name -p port -h hostname [-s script_name]";

Core::Core()
{
    this->teamName = "";
    this->ip       = "";
    this->port     = -1;
    this->fileIA   = IAClient::Default;
#ifdef _WIN32
    Socket::WinSocket(Socket::START);
#endif
}

Core::~Core()
{
#ifdef  _WIN32
    Socket::WinSocket(Socket::STOP);
#endif
}

std::string    Core::getIp() const
{
    return (this->ip);
}

void    Core::setIp(const std::string ip)
{
    this->ip = ip;
}

int    Core::getPort() const
{
    return (this->port);
}

void    Core::setPort(const int port)
{
    this->port = port;
}

std::string    Core::getTeamName() const
{
    return (this->teamName);
}

void    Core::setTeamName(const std::string teamName)
{
    this->teamName = teamName;
}

std::string    Core::getFileIA() const
{
    return (this->fileIA);
}

void    Core::setFileIA(const std::string fileIA)
{
    this->fileIA = fileIA;
}

int    Core::isNumber(char *str) const
{
    int i;

    i = 0;
    while (str[i] != '\0')
    {
        if (str[i] < '0' || str[i] > '9')
            return (-1);
        ++i;
    }
    return (0);
}

int    Core::parseArg(int ac, char **av) throw(ParsingError)
{
    int  c;
    char opt[] = "n:p:h:s:";

    while ((c = getopt(ac, av, opt)) != -1)
    {
        switch (c)
        {
            case 'n':
                this->setTeamName(std::string(optarg));
                break;
            case 'p':
                if (this->isNumber(optarg) == 0)
                    this->setPort(atoi(optarg));
                else
                    throw ParsingError(av[0], "-p argument has to be numeric");
                break;
            case 'h':
                this->setIp(std::string(optarg));
                break;
            case 's':
                this->setFileIA(std::string(optarg));
                break;
            default:
                throw ParsingError();
        }
    }
    if (this->teamName == "" || this->ip == "" || this->port == -1)
        throw ParsingError(av[0], usage);
    this->client.Connect(this->ip, this->port, this->teamName);
    return (0);
}

int Core::run(void)
{
  while (this->client.IsDead() != true)
  {
      if (this->client.Update() != 0)
          return 1;
  }
  return 0;
}
