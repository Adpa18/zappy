/*
** plv.c for PLV in /home/gouet_v/Rendu/semester4/PSU/PSU_2015_zappy/src_server/Monitor_event
** 
** Made by Victor Gouet
** Login   <gouet_v@epitech.net>
** 
** Started on  Mon Jun 13 13:40:54 2016 Victor Gouet
** Last update Tue Jun 14 01:30:29 2016 Victor Gouet
*/

#include "../../include_server/monitor_event.h"

int		plv_event(t_monitor *monitor, t_list *list,
			  t_command_line *command, char **tab)
{
  t_trantorien	*trantorien;

  if (!tab[1])
    return (sbp_event(monitor));
  if (!(trantorien = get_trantorien_from_id(list, atoi(tab[1]))))
    return (sbp_event(monitor));
  sendf_message(&(monitor->ref->client->sock),
		"plv %d %d\n", trantorien->id, trantorien->elevation);
  return (0);
}
