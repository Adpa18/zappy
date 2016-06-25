/*
** msz.c for MSZ in /home/gouet_v/Rendu/semester4/PSU/PSU_2015_zappy/src_server/Monitor_event
** 
** Made by Victor Gouet
** Login   <gouet_v@epitech.net>
** 
** Started on  Mon Jun 13 13:40:15 2016 Victor Gouet
** Last update Sat Jun 25 15:49:13 2016 Victor Gouet
*/

#include "../../include_server/monitor_event.h"

int	msz_event(t_monitor *monitor, t_list *list,
		  t_command_line *command, char **tab)
{
  (void)list;
  (void)tab;
  fbufferise(monitor->ref, "msz %d %d\n",
	     command->x, command->y);
  return (0);
}
