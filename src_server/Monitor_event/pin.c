/*
** pin.c for PIN in /home/gouet_v/Rendu/semester4/PSU/PSU_2015_zappy/src_server/Monitor_event
** 
** Made by Victor Gouet
** Login   <gouet_v@epitech.net>
** 
** Started on  Mon Jun 13 13:38:05 2016 Victor Gouet
** Last update Mon Jun 13 21:16:44 2016 Victor Gouet
*/

#include "../../include_server/monitor_event.h"

int			pin_event(t_monitor *monitor, t_list *list,
				  t_command_line *command, char **tab)
{
    t_trantorien	*trantorien;

  if (!tab[1])
    return (sbp_event(monitor, list, command, tab));
  if (!(trantorien = get_trantorien_from_id(list, atoi(tab[1]))))
    return (sbp_event(monitor, list, command, tab));
  sendf_message(&(monitor->ref->client->sock),
		"pin %d %d %d %d %d %d %d %d %d\n",
		trantorien->pos.x, trantorien->pos.y,
	        trantorien->inventaire.food,
		trantorien->inventaire.linemate,
	        trantorien->inventaire.deraumere,
	        trantorien->inventaire.sibur,
	        trantorien->inventaire.mendiane,
	        trantorien->inventaire.phiras,
	        trantorien->inventaire.thystame);
  return (0);
}
