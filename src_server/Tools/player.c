/*
** add_client_to_list.c for CLIENT in /home/gouet_v/Rendu/semester4/PSU/PSU_2015_zappy
**
** Made by Victor Gouet
** Login   <gouet_v@epitech.net>
**
** Started on  Tue Jun  7 14:52:48 2016 Victor Gouet
** Last update Sat Jun 25 15:47:57 2016 Victor Gouet
*/

#include "../../include_server/player.h"

int     count_players(t_list *list)
{
    t_ref   *ref;
    int     nb;

    nb = 0;
    ref = list->begin;
    while (ref)
    {
        if (ref->type == TRANTORIEN)
            ++nb;
        ref = ref->next;
    }
    return (nb);
}

int     count_players_by_pos_for_elevation(t_list *list,
					   t_trantorien *trantorien)
{
  t_trantorien    *drone;
  t_ref   *ref;
  int     nb;

  nb = 0;
  ref = list->begin;
  while (ref)
    {
      drone = ref->ref;
      if (ref->type == TRANTORIEN
	  && drone->pos.x == trantorien->pos.x
	  && drone->pos.y == trantorien->pos.y)
	{
	  if (drone->elevation != trantorien->elevation)
	    return (0);
	  ++nb;
	}
      ref = ref->next;
    }
  return (nb);
}

int		elevate_players_at_pos(t_list *list, int x, int y)
{
  t_ref		*ref;
  t_trantorien	*trantorien;

  ref = list->begin;
  while (ref)
    {
      if (ref->type == TRANTORIEN)
	{
	  trantorien = ref->ref;
	  if (trantorien->pos.x == x && trantorien->pos.y == y)
	    ++(trantorien->elevation);
	}
      ref = ref->next;
    }
  return (1);
}

int		send_msg_to_begin_elevation(t_list *list, int x, int y)
{
  t_ref		*ref;
  t_trantorien	*trantorien;

  ref = list->begin;
  while (ref)
    {
      if (ref->type == TRANTORIEN)
	{
	  trantorien = ref->ref;
	  if (trantorien->pos.x == x && trantorien->pos.y == y)
	    {
	      bufferise(ref, "elevation en cours\n");
	    }
	}
      ref = ref->next;
    }
  return (1);
}

int		send_msg_to_finish_elevation(t_list *list, int x, int y)
{
  t_ref		*ref;
  t_trantorien	*trantorien;

  ref = list->begin;
  while (ref)
    {
      if (ref->type == TRANTORIEN)
	{
	  trantorien = ref->ref;
	  if (trantorien->pos.x == x && trantorien->pos.y == y)
	    {
	      fbufferise(ref, "niveau actuel : %d\n", trantorien->elevation);
	    }
	}
      ref = ref->next;
    }
  return (1);
}
