/*
** incantation_event.c for INCANTATION in /home/gouet_v/Rendu/semester4/PSU/PSU_2015_zappy/src_server/Trantorien_Event
** 
** Made by Victor Gouet
** Login   <gouet_v@epitech.net>
** 
** Started on  Wed Jun  8 07:54:59 2016 Victor Gouet
** Last update Sun Jun 26 15:57:22 2016 Victor Gouet
*/

#include <stdbool.h>
#include "../../include_server/player.h"
#include "incantation.h"
#include "../../include_server/trantorien_event.h"
#include "../../include_server/monitor_event.h"

static const incantationPtr incantationFunc[7] = {
        incantation_one, incantation_two, incantation_three, incantation_four,
        incantation_five, incantation_six, incantation_seven
};

bool     incantation_six(t_trantorien *trantorien, t_list *list, bool end)
{
  int	x;
  int	y;

  y = trantorien->pos.y;
  x = trantorien->pos.x;
  if (count_players_by_pos_for_elevation(list, trantorien) == 6
      && list->map->map[y][x].linemate == 1
      && list->map->map[y][x].deraumere == 2
      && list->map->map[y][x].sibur == 3
      && list->map->map[y][x].phiras == 1)
    {
      if (end)
        {
	  list->map->map[y][x].linemate -= 1;
	  list->map->map[y][x].deraumere -= 2;
	  list->map->map[y][x].sibur -= 3;
	  list->map->map[y][x].phiras -= 1;
        }
      return (true);
    }
  return (false);
}

bool     incantation_seven(t_trantorien *trantorien, t_list *list, bool end)
{
  int	x;
  int	y;

  y = trantorien->pos.y;
  x = trantorien->pos.x;
  if (count_players_by_pos_for_elevation(list, trantorien) == 6
      && list->map->map[y][x].linemate == 2
      && list->map->map[y][x].deraumere == 2
      && list->map->map[y][x].sibur == 2
      && list->map->map[y][x].mendiane == 2
      && list->map->map[y][x].phiras == 2
      && list->map->map[y][x].thystame == 1)
    {
      if (end)
        {
	  list->map->map[y][x].linemate -= 2;
	  list->map->map[y][x].deraumere -= 2;
	  list->map->map[y][x].sibur -= 2;
	  list->map->map[y][x].mendiane -= 2;
	  list->map->map[y][x].phiras -= 2;
	  list->map->map[y][x].thystame -= 1;
        }
      return (true);
    }
  return (false);
}

bool    can_elevate(t_trantorien *trantorien, t_list *list)
{
  if (trantorien->elevation - 1 < 7)
    return (incantationFunc[trantorien->elevation - 1]
            (trantorien, list, false));
  return (false);
}

int	incantation_event(t_trantorien *trantorien, t_list *list,
			  t_command_line *command, char **tab)
{
  (void)command;
  (void)tab;
  if (trantorien->elevation - 1 < 7 &&
      incantationFunc[trantorien->elevation - 1]
      (trantorien, list, true))
    {
      elevate_players_at_pos(list, trantorien->pos.x, trantorien->pos.y);
      pie_event(trantorien, list, 1);
      plv_event_all_monitor(list);
      mct_to_all_monitor(list);
      send_msg_to_finish_elevation(list, trantorien->pos.x,
				   trantorien->pos.y);
      ressources_generation(list, list->map, 5, 10);
    }
  else
    {
      bufferise(trantorien->ref, "ko\n");
      pie_event(trantorien, list, 0);
      plv_event_all_monitor(list);
    }
  return (0);
}
