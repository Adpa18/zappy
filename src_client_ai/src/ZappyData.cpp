//
// ZappyData.cpp for zeppy in /home/tavern_d/rendu/semestre4/PSU_2015_zappy/src_client_ai
// 
// Made by Matthieu Tavernier
// Login   <tavern_d@epitech.net>
// 
// Started on  Wed Jun  8 16:26:56 2016 Matthieu Tavernier
// Last update Wed Jun  8 18:02:04 2016 Matthieu Tavernier
//

#include "ZappyData.hpp"

ZappyData::ZappyData()
{
}

ZappyData::~ZappyData()
{
}

std::vector<std::vector<std::string> >		ZappyData::deserialize(std::string cmd)
{
  std::vector<std::vector<std::string> >	vect;
  std::string					_case;

  for (std::string::iterator it = cmd.begin(); it != cmd.end(); ++it)
    {
      if (*it == '{' || *it == '}')
	{
	  cmd.erase(it);
	  it = cmd.begin();
	}
    }
  std::stringstream ss(cmd);
  while (std::getline(ss, _case, ','))
    {
      std::vector<std::string>	tmp;
      std::stringstream ss2(_case);
      std::string tmp2;
      while (std::getline(ss2, tmp2, ' '))
	{
	  if (tmp2 != "")
	    tmp.push_back(tmp2);
	}
      vect.push_back(tmp);
    }
  return (vect);
}
