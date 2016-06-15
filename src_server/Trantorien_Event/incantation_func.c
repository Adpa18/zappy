/*
** incantation_event.c for INCANTATION in /home/gouet_v/Rendu/semester4/PSU/PSU_2015_zappy/src_server/Trantorien_Event
**
** Made by Victor Gouet
** Login   <gouet_v@epitech.net>
**
** Started on  Wed Jun  8 07:54:59 2016 Victor Gouet
** Last update Wed Jun 15 15:02:00 2016 Victor Gouet
*/

#include "player.h"

bool     incantation_one(t_trantorien *trantorien, t_list *list, bool end)
{
  int	x;
  int	y;

  y = trantorien->pos.y;
  x = trantorien->pos.x;
  if (count_players_by_pos_for_elevation(list, trantorien) == 1
      && list->map->map[y][x].linemate == 1)
    {
      if (end)
        {
	  --list->map->map[y][x].linemate;
        }
      return (true);
    }
  return (false);
}

bool     incantation_two(t_trantorien *trantorien, t_list *list, bool end)
{
  int	x;
  int	y;

  y = trantorien->pos.y;
  x = trantorien->pos.x;
  if (count_players_by_pos_for_elevation(list, trantorien) == 2
      && list->map->map[y][x].linemate == 1
      && list->map->map[y][x].deraumere == 1
      && list->map->map[y][x].sibur == 1)
    {
      if (end)
        {
	  list->map->map[y][x].linemate -= 1;
	  list->map->map[y][x].deraumere -= 1;
	  list->map->map[y][x].sibur -= 1;
        }
      return (true);
    }
  return (false);
}

bool     incantation_three(t_trantorien *trantorien, t_list *list, bool end)
{
  int	x;
  int	y;

  y = trantorien->pos.y;
  x = trantorien->pos.x;
  if (count_players_by_pos_for_elevation(list, trantorien) == 2
      && list->map->map[y][x].linemate == 2
      && list->map->map[y][x].sibur == 1
      && list->map->map[y][x].phiras == 2)
    {
      if (end)
        {
	  list->map->map[y][x].linemate -= 2;
	  list->map->map[y][x].sibur -= 1;
	  list->map->map[y][x].phiras -= 2;
        }
      return (true);
    }
  return (false);
}

bool     incantation_four(t_trantorien *trantorien, t_list *list, bool end)
{
  int	x;
  int	y;

  y = trantorien->pos.y;
  x = trantorien->pos.x;
  if (count_players_by_pos_for_elevation(list, trantorien) == 4
      && list->map->map[y][x].linemate == 1
      && list->map->map[y][x].deraumere == 1
      && list->map->map[y][x].sibur == 2
      && list->map->map[y][x].phiras == 1)
    {
      if (end)
        {
	  list->map->map[y][x].linemate -= 1;
	  list->map->map[y][x].deraumere -= 1;
	  list->map->map[y][x].sibur -= 2;
	  list->map->map[y][x].phiras -= 1;
        }
      return (true);
    }
  return (false);
}

bool     incantation_five(t_trantorien *trantorien, t_list *list, bool end)
{
  int	x;
  int	y;

  y = trantorien->pos.y;
  x = trantorien->pos.x;
  if (count_players_by_pos_for_elevation(list, trantorien) == 4
      && list->map->map[y][x].linemate == 1
      && list->map->map[y][x].deraumere == 2
      && list->map->map[y][x].sibur == 1
      && list->map->map[y][x].mendiane == 3)
    {
      if (end)
        {
	  list->map->map[y][x].linemate -= 1;
	  list->map->map[y][x].deraumere -= 2;
	  list->map->map[y][x].sibur -= 1;
	  list->map->map[y][x].mendiane -= 3;
        }
      return (true);
    }
  return (false);
}
