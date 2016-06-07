/*
** remove_client_to_list.c for GESTION in /home/gouet_v/Rendu/semester4/PSU/PSU_2015_zappy
** 
** Made by Victor Gouet
** Login   <gouet_v@epitech.net>
** 
** Started on  Tue Jun  7 16:01:02 2016 Victor Gouet
** Last update Tue Jun  7 17:45:30 2016 Victor Gouet
*/

#include "../include_server/server.h"

t_ref	*remove_client_to_list(t_list *list, t_ref *ref)
{
  t_ref	*elem;

  elem = list->begin;
  if (elem == ref)
    elem = NULL;
  while (elem)
    {
      if (elem->next == ref)
	break;
      elem = elem->next;
    }
  if (elem)
    elem->next = ref->next;
  if (list->begin == ref)
    list->begin = ((t_ref *)list->begin)->next;
  if (list->end == ref)
    list->end = elem;
  --(list->nbr_client);
  free(ref);
  return (elem != NULL ? elem->next : NULL);
}
