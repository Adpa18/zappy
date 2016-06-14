/*
** remove_client_to_team.c for REMOVE TEAM in /home/gouet_v/Rendu/semester4/PSU/PSU_2015_zappy
** 
** Made by Victor Gouet
** Login   <gouet_v@epitech.net>
** 
** Started on  Tue Jun  7 17:41:28 2016 Victor Gouet
** Last update Tue Jun  7 20:14:34 2016 Victor Gouet
*/

#include "../include_server/server.h"

t_trantorien	*remove_client_to_team(t_team_name *list,
				       t_trantorien *ref)
{
  t_trantorien	*elem;

  elem = list->begin;
  if (elem == ref)
    elem = NULL;
  while (elem)
    {
      if (elem->next_on_team == ref)
	break;
      elem = elem->next_on_team;
    }
  if (elem)
    elem->next_on_team = ref->next_on_team;
  if (list->begin == ref)
    list->begin = ((t_trantorien *)list->begin)->next_on_team;
  if (list->end == ref)
    list->end = elem;
  --(list->nbr_client);
  return (elem != NULL ? elem->next_on_team : NULL);
}

t_trantorien		*remove_client_to_unknown_team(t_team_list *list,
						       t_trantorien *ref)
{
  t_team_name	*team;
  t_trantorien	*elem;

  team = list->begin;
  while (team)
    {
      elem = team->begin;
      while (elem)
	{
	  if (ref == elem)
	    return (remove_client_to_team(team, ref));
	  elem = elem->next_on_team;
	}
      team = team->next;
    }
  return (NULL);
}
