/*
** remove_map.c for MAP in /home/gouet_v/Rendu/semester4/PSU/PSU_2015_zappy
** 
** Made by Victor Gouet
** Login   <gouet_v@epitech.net>
** 
** Started on  Fri Jun 17 10:48:56 2016 Victor Gouet
** Last update Fri Jun 17 10:54:24 2016 Victor Gouet
*/

#include "../include_server/server.h"

void		remove_map(t_map *map)
{
  int		y;

  y = 0;
  while (y < map->height)
    {
      if (map->map[y])
	free(map->map[y]);
      ++y;
    }
  free(map->map);
  free(map);
}
