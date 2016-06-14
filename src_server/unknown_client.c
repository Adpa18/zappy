/*
** unknown_client.c for UNKNOWN CLINET in /home/gouet_v/Rendu/semester4/PSU/PSU_2015_zappy
** 
** Made by Victor Gouet
** Login   <gouet_v@epitech.net>
** 
** Started on  Tue Jun  7 16:47:38 2016 Victor Gouet
** Last update Tue Jun 14 11:04:02 2016 Victor Gouet
*/

#include <stdio.h>
#include <string.h>
#include "../include_server/server.h"
#include "../include_server/time_gestion.h"

int		unknwon_client_event(t_ref *ref, t_list *list,
				     t_command_line *command,
				     char **tab)
{
  t_team_name	*team;

  (void)list;
  if (strcmp(tab[0], GRAPHIC) == 0)
    {
      return (monitor_connection(ref, list, command));
    }
  else if ((team = get_team(&(command->team_list), tab[0])))
    {
      return (trantorien_connection(ref, team, command, list));
    }
  else
    {
      send_message("ko\n", &(ref->client->sock));
      return (-1);
    }
  return (0);
}

