/*
** food_gestion.c for SERVER in /home/gouet_v/Rendu/semester4/PSU/PSU_2015_zappy
** 
** Made by Victor Gouet
** Login   <gouet_v@epitech.net>
** 
** Started on  Mon Jun 13 10:45:15 2016 Victor Gouet
** Last update Mon Jun 13 12:14:55 2016 Victor Gouet
*/

#include <stdio.h>
#include "../include_server/server.h"
#include "../include_server/time_gestion.h"
#include "../include_server/trantorien_event.h"

static int	trantorien_eat(t_trantorien *trantorien,
			       t_command_line *command)
{
  long long	time_left;

  time_left = UNITEDLIFE * ((double)1 /
			    (command->time == 0 ? 1 : command->time)
			    * 1000);
  if (is_time_out_in(trantorien->time_left_food, time_left))
    {
      trantorien->time_left_food = getTimeSeconds();
      --(trantorien->inventaire.food);
      if (trantorien->inventaire.food == 0)
	return (-1);
    }
  return (0);
}

int	        food_gestion_for_trantorien(t_list *list,
					    t_command_line *command,
					    t_server *server)
{
  t_ref		*ref;

  ref = list->begin;
  while (ref)
    {
      if (ref->type == TRANTORIEN)
	{
	  if (trantorien_eat(ref->ref, command) == -1)
	    {
	      die_event(ref->ref);
	      ref = delete_all_in_client(list, command, server, ref);
	      continue;
	    }
	}
      ref = ref->next;
    }
  return (0);
}
