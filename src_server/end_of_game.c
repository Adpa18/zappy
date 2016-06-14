/*
** end_of_game.c for GAME in /home/gouet_v/Rendu/semester4/PSU/PSU_2015_zappy
** 
** Made by Victor Gouet
** Login   <gouet_v@epitech.net>
** 
** Started on  Tue Jun 14 01:18:39 2016 Victor Gouet
** Last update Tue Jun 14 01:25:31 2016 Victor Gouet
*/

#include "../include_server/server.h"

t_trantorien	*get_trantorien_with_max_elevation(t_list *list)
{
  t_ref		*ref;
  t_trantorien	*trantorien;
  t_trantorien	*save;

  save = NULL;
  ref = list->begin;
  while (ref)
    {
      if (ref->type == TRANTORIEN)
	{
	  trantorien = ref->ref;
	  if (!save || save->elevation < trantorien->elevation)
	    {
	      save = trantorien;
	    }
	}
      ref = ref->next;
    }
  return (save);
}
