/*
** get_trantorien.c for TRANTORIEN in /home/gouet_v/Rendu/semester4/PSU/PSU_2015_zappy
** 
** Made by Victor Gouet
** Login   <gouet_v@epitech.net>
** 
** Started on  Mon Jun 13 20:56:58 2016 Victor Gouet
** Last update Tue Jun 14 01:10:33 2016 Victor Gouet
*/

#include "../include_server/server.h"

t_trantorien	*get_trantorien_egg_from_team(t_team_name *team)
{
  t_trantorien	*elem;

  elem = team->begin;
  while (elem)
    {
      if (elem->state == EGG)
	return (elem);
      elem = elem->next_on_team;
    }
  return (NULL);
}

t_trantorien	*get_trantorien_baby_from_team(t_team_name *team)
{
  t_trantorien	*elem;

  elem = team->begin;
  while (elem)
    {
      if (elem->state == BABY)
	return (elem);
      elem = elem->next_on_team;
    }
  return (NULL);
}

t_trantorien	*get_trantorien_ghost_from_team(t_team_name *team)
{
  t_trantorien	*elem;

  elem = team->begin;
  while (elem)
    {
      if (elem->state == GHOST)
	return (elem);
      elem = elem->next_on_team;
    }
  return (NULL);
}

t_trantorien	*get_trantorien_from_id(t_list *list, int id)
{
  t_ref		*ref;

  ref = list->begin;
  while (ref)
    {
      if (ref->type == TRANTORIEN)
	{
	  if (((t_trantorien *)ref->ref)->id == id)
	    {
	      return (ref->ref);
	    }
	}
      ref = ref->next;
    }
  return (NULL);
}
