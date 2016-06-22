/*
** time_event.c for TIME in /home/gouet_v/Rendu/semester4/PSU/PSU_2015_zappy
** 
** Made by Victor Gouet
** Login   <gouet_v@epitech.net>
** 
** Started on  Wed Jun 22 13:54:15 2016 Victor Gouet
** Last update Wed Jun 22 14:44:58 2016 Victor Gouet
*/

#include "../../include_server/monitor_event.h"
#include "../../stringLib/storage.h"

int	time_event(t_monitor *monitor, t_list *list,
		  t_command_line *command, char **tab)
{
  (void)list;
  (void)tab;
  sendf_message(&(monitor->ref->client->sock), "time %ld\n",
	        (long)command->time_launch);
  return (0);
}
