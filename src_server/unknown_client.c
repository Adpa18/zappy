/*
** unknown_client.c for UNKNOWN CLINET in /home/gouet_v/Rendu/semester4/PSU/PSU_2015_zappy
** 
** Made by Victor Gouet
** Login   <gouet_v@epitech.net>
** 
** Started on  Tue Jun  7 16:47:38 2016 Victor Gouet
** Last update Tue Jun  7 18:32:03 2016 Victor Gouet
*/

#include <stdio.h>
#include <string.h>
#include "../include_server/server.h"

int		unknwon_client_event(t_ref *ref, t_list *list,
				     t_command_line *command,
				     char **tab)
{
  t_team_name	*team;
  t_trantorien	*trantorien;
  t_monitor	*monitor;

  if (strcmp(tab[0], GRAPHIC) == 0)
    {
      monitor = transform_to_monitor(ref);
      monitor->data = 0;
    }
  if ((team = get_team(&(command->team_list), tab[0])))
    {
      trantorien = transform_to_trantorien(ref);
      add_client_to_team(team, trantorien);
      trantorien->koala = 10;
    }
  return (0);
}

