/*
** monitor_connection.c for MONITOR in /home/gouet_v/Rendu/semester4/PSU/PSU_2015_zappy
** 
** Made by Victor Gouet
** Login   <gouet_v@epitech.net>
** 
** Started on  Tue Jun 14 11:00:34 2016 Victor Gouet
** Last update Tue Jun 14 12:28:15 2016 Victor Gouet
*/

#include "../include_server/monitor_event.h"

int		monitor_connection(t_ref *ref, t_list *list,
				   t_command_line *command)
{
  t_monitor	*monitor;

  if ((monitor = transform_to_monitor(ref)) == NULL)
    return (-1);
  msz_event(monitor, list, command, NULL);
  sgt_event(monitor, list, command, NULL);
  mct_event(monitor, list, command, NULL);
  tna_event(monitor, list, command, NULL);
  pnw_event_all_to_monitor(monitor, command);
  enw_event_all_to_monitor(monitor, command);
  monitor->data = 0;
  return (0);
}
