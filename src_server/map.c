/*
** map.c for MAP in /home/gouet_v/Rendu/semester4/PSU/PSU_2015_zappy
** 
** Made by Victor Gouet
** Login   <gouet_v@epitech.net>
** 
** Started on  Wed Jun  8 09:46:02 2016 Victor Gouet
** Last update Tue Jun 21 10:07:34 2016 Victor Gouet
*/

#include <stdio.h>
#include <strings.h>
#include <stdlib.h>
#include "../include_server/server.h"

static t_inventories	*create_ground(int width)
{
  t_inventories		*ground;

  if ((ground = malloc(sizeof(t_inventories) * width)) == NULL)
    return (NULL);
  bzero(ground, sizeof(t_inventories) * width);
  return (ground);
}

void			display_inventories(t_inventories *inventories)
{
  printf("food: %d\n", inventories->food);
  printf("linamte: %d\n", inventories->linemate);
  printf("deraumere: %d\n", inventories->deraumere);
  printf("sibur: %d\n", inventories->sibur);
  printf("mendiane: %d\n", inventories->mendiane);
  printf("phiras: %d\n", inventories->phiras);
  printf("thystame: %d\n", inventories->thystame);
}

void			generate_random_ressources(t_map *map)
{
  int			x;
  int			y;

  y = 0;
  while (y < map->height)
    {
      x = 0;
      while (x < map->width)
	{
	  map->map[y][x].food += rand() % 10;
	  map->map[y][x].linemate += rand() % 2;
	  map->map[y][x].deraumere += rand() % 2;
	  map->map[y][x].sibur += rand() % 2;
	  map->map[y][x].mendiane += rand() % 2;
	  map->map[y][x].phiras += rand() % 2;
	  map->map[y][x].thystame += rand() % 2;
	  ++x;
	}
      ++y;
    }
}

t_map			*create_map(int width, int height)
{
  t_map			*map_all;
  int			y;

  if (width < 0 || height < 0)
    return (NULL);
  if ((map_all = malloc(sizeof(t_map))) == NULL)
    return (NULL);
  if ((map_all->map = malloc(sizeof(t_inventories *) * height)) == NULL)
    return (NULL);
  y = 0;
  while (y < height)
    {
      map_all->map[y] = create_ground(width);
      ++y;
    }
  map_all->height = height;
  map_all->width = width;
  return (map_all);
}

void			display_map(t_map *map)
{
  int			x;
  int			y;

  y = 0;
  while (y < map->height)
    {
      x = 0;
      while (x < map->width)
	{
	  printf("{ y: %d, x: %d}\n", y, x);
	  display_inventories(&(map->map[y][x]));
	  ++x;
	}
      ++y;
    }
}
