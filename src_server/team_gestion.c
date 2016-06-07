/*
** team_gestion.c for TEAM in /home/gouet_v/Rendu/semester4/PSU/PSU_2015_zappy
** 
** Made by Victor Gouet
** Login   <gouet_v@epitech.net>
** 
** Started on  Tue Jun  7 17:50:22 2016 Victor Gouet
** Last update Tue Jun  7 17:56:53 2016 Victor Gouet
*/

#include <stdbool.h>
#include <string.h>
#include "../include_server/command_line_arguments.h"

t_team_name	*get_team(t_team_list *list, char const *name)
{
  t_team_name	*elem;

  elem = list->begin;
  while (elem)
    {
      if (strcmp(elem->name, name) == 0)
	return (elem);
      elem = elem->next;
    }
  return (NULL);
}

bool		is_valid_team_name(t_team_list *list, char *team_name)
{
  t_team_name	*elem;

  elem = list->begin;
  while (elem)
    {
      if (strcmp(elem->name, team_name) == 0)
	{
	  return (true);
	}
      elem = elem->next;
    }
  return (false);
}
