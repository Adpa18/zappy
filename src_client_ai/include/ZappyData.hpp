//
// ZappyData.hpp for zappy in /home/tavern_d/rendu/semestre4/PSU_2015_zappy/src_client_ai
// 
// Made by Matthieu Tavernier
// Login   <tavern_d@epitech.net>
// 
// Started on  Wed Jun  8 16:19:23 2016 Matthieu Tavernier
// Last update Wed Jun  8 18:01:46 2016 Matthieu Tavernier
//

#ifndef ZAPPYDATA_HPP_
# define ZAPPYDATA_HPP_

# include <vector>
# include <sstream>
# include <iostream>

class						ZappyData
{
public:
  ZappyData();
  ~ZappyData();
  static std::vector<std::vector<std::string> >	deserialize(std::string);
};

#endif /* !ZAPPYDATA_HPP_ */
