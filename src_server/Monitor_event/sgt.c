/*
** sgt.c for SGT in /home/gouet_v/Rendu/semester4/PSU/PSU_2015_zappy/src_server/Monitor_event
** 
** Made by Victor Gouet
** Login   <gouet_v@epitech.net>
** 
** Started on  Mon Jun 13 13:37:39 2016 Victor Gouet
** Last update Sat Jun 25 15:48:56 2016 Victor Gouet
*/

#include "../../include_server/monitor_event.h"

int	sgt_event(t_monitor *monitor, t_list *list,
		  t_command_line *command, char **tab)
{
  (void)tab;
  (void)list;
  fbufferise(monitor->ref, "sgt %d\n", command->time);
  return (0);
}
