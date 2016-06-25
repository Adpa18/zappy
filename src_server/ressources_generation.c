/*
** ressources_generation.c for RESSOURCES in /home/gouet_v/Rendu/semester4/PSU/PSU_2015_zappy
** 
** Made by Victor Gouet
** Login   <gouet_v@epitech.net>
** 
** Started on  Thu Jun 23 17:05:18 2016 Victor Gouet
** Last update Sat Jun 25 16:59:10 2016 Victor Gouet
*/

#include "../include_server/server.h"
#include "../include_server/player.h"
#include "../include_server/trantorien_event.h"
#include "../include_server/monitor_event.h"

int		ressources_generation(t_list *list, t_map *map,
				      int proba, int proba_food)
{
  int		x;
  int		y;

  y = 0;
  while (y < map->height)
    {
      x = 0;
      while (x < map->width && rand() % proba == 0)
	{
	  /* if (rand() % proba == 0) */
	  /*   { */
	      map->map[y][x].food += rand() % proba_food;
	      map->map[y][x].linemate += rand() % 2;
	      map->map[y][x].deraumere += rand() % 2;
	      map->map[y][x].sibur += rand() % 2;
	      map->map[y][x].mendiane += rand() % 2;
	      map->map[y][x].phiras += rand() % 2;
	      map->map[y][x].thystame += rand() % 2;
	      bct_event_to_all_monitor(list, x, y);
	    /* } */
	  ++x;
	}
      ++y;
    }
  return (0);
}
