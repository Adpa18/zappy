//
// Core.hpp for zappy in /home/tavern_d/rendu/semestre4/PSU_2015_zappy/src_client_ai
// 
// Made by Matthieu Tavernier
// Login   <tavern_d@epitech.net>
// 
// Started on  Wed Jun  8 11:32:26 2016 Matthieu Tavernier
// Last update Wed Jun  8 14:59:02 2016 Matthieu Tavernier
//

#ifndef CORE_HPP_
# define CORE_HPP_

# include <iostream>
# include <unistd.h>
# include <cstdlib>

class		Core
{
public:
  Core();
  ~Core();
public:
  std::string	getIp() const;
  void		setIp(const std::string);
  int		getPort() const;
  void		setPort(const int);
  std::string	getTeamName() const;
  void		setTeamName(const std::string);
  std::string	getFileIA() const;
  void		setFileIA(const std::string);
public:
  int		parseArg(int, char **);
    int    run(void);
private:
  int		isNumber(char *) const;
private:
  std::string	ip;
  int		port;
  std::string	teamName;
  std::string	fileIA;
};

#endif /* !CORE_HPP_ */
