/*
** bct.c for BCT in /home/gouet_v/Rendu/semester4/PSU/PSU_2015_zappy/src_server/Monitor_event
** 
** Made by Victor Gouet
** Login   <gouet_v@epitech.net>
** 
** Started on  Mon Jun 13 13:38:59 2016 Victor Gouet
** Last update Mon Jun 13 15:00:36 2016 Victor Gouet
*/

#include "../../include_server/monitor_event.h"

int	bct_event(t_monitor *monitor, t_list *list,
		  t_command_line *command, char **tab)
{
  int	x;
  int	y;

  if (!tab[1] || !tab[2])
    return (sbp_event(monitor, list, command, tab));
  x = atoi(tab[1]);
  y = atoi(tab[2]);
  if (x >= command->x || y >= command->y || x < 0 || y < 0)
    return (sbp_event(monitor, list, command, tab));
  sendf_message(&(monitor->ref->client->sock),
		"bct %d %d %d %d %d %d %d %d %d\n",
		x, y,
		list->map->map[y][x].food,
		list->map->map[y][x].linemate,
		list->map->map[y][x].deraumere,
		list->map->map[y][x].sibur,
		list->map->map[y][x].mendiane,
		list->map->map[y][x].phiras,
		list->map->map[y][x].thystame);
  return (0);
}
