//
// Core.hpp for zappy in /home/tavern_d/rendu/semestre4/PSU_2015_zappy/src_client_ai
// 
// Made by Matthieu Tavernier
// Login   <tavern_d@epitech.net>
// 
// Started on  Wed Jun  8 11:32:26 2016 Matthieu Tavernier
// Last update Mon Jun 13 13:44:25 2016 Matthieu Tavernier
//

#ifndef CORE_HPP_
# define CORE_HPP_

# include <iostream>
# include <unistd.h>
# include <cstdlib>
# include <stdexcept>
# include "IAClient.hpp"
# include "ZappyRequest.hpp"

class ParsingError : public std::runtime_error
{
public:
    ParsingError(std::string const &exe = "", std::string const &err = "") :
            std::runtime_error(exe.empty() ? "" : exe + (err.empty() ? "" : ' ' + err))
    {

    }
    virtual ~ParsingError() throw()
    {

    }
    using std::runtime_error::what;
};

class Core
{
public:
    static const std::string usage;

public:
    Core();

    ~Core();

public:
    std::string getIp() const;

    void        setIp(const std::string);

    int         getPort() const;

    void        setPort(const int);

    std::string getTeamName() const;

    void        setTeamName(const std::string);

    std::string getFileIA() const;

    void        setFileIA(const std::string);

public:
    int parseArg(int, char **) throw(std::runtime_error);

    int run(void);

private:
    int isNumber(char *) const;

private:
  std::string ip;
  int         port;
  std::string teamName;
  std::string fileIA;
  IAClient	client;
};

#endif /* !CORE_HPP_ */
