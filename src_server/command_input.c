/*
** command_input.c for COMMAND in /home/gouet_v/Rendu/semester4/PSU/PSU_2015_zappy
** 
** Made by Victor Gouet
** Login   <gouet_v@epitech.net>
** 
** Started on  Fri Jun 24 14:56:15 2016 Victor Gouet
** Last update Sat Jun 25 15:46:03 2016 Victor Gouet
*/

#include <string.h>
#include "../include_server/server.h"
#include "../include_server/incantation.h"
#include "../include_server/monitor_event.h"

int	command_input_for(t_ref *ref, t_list *list)
{
  char	**tab;

  if (ref->buffer_size == 0 || !ref->begin
      || ref->begin->first_time == false)
    return (0);
  tab = ref->begin->tab;
  ref->begin->first_time = false;
  if (tab && tab[0] && strcmp("incantation", tab[0]) == 0
      && ref->type == TRANTORIEN && !can_elevate(ref->ref, list))
    {
      bufferise(ref, "ko\n");
      ref->time_ref = 0;
      buffer_pop_front(ref);
    }
  else if (tab && tab[0] && strcmp("incantation", tab[0]) == 0
	   && ref->type == TRANTORIEN && can_elevate(ref->ref, list))
    {
      bufferise(ref, "elevation en cours\n");
      pic_event(ref->ref, list);
    }
  else if (tab && tab[0] && strcmp("fork", tab[0]) == 0)
    {
      pfk_event(ref->ref, list);
    }
  return (0);
}
