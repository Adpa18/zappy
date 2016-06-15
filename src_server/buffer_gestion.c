/*
** buffer_gestion.c for BUFFER in /home/gouet_v/Rendu/semester4/PSU/PSU_2015_zappy
** 
** Made by Victor Gouet
** Login   <gouet_v@epitech.net>
** 
** Started on  Wed Jun  8 14:14:09 2016 Victor Gouet
** Last update Wed Jun 15 17:39:33 2016 Victor Gouet
*/

#include <stdio.h>
#include "../include_server/server.h"

void		buffer_push_back(t_ref *ref, char *buffer,
				 char **tab)
{
  t_buffer	*elem;

  if ((elem = malloc(sizeof(t_buffer))) == NULL)
    return ;
  elem->tab = tab;
  elem->next = NULL;
  ++(ref->buffer_size);
  elem->buffer = buffer;
  printf("data receive: %s\n", buffer);
  if (ref->begin == NULL && ref->end == NULL)
    {
      ref->begin = elem;
    }
  else
    {
      ref->end->next = elem;
    }
  ref->end = elem;
}

void		buffer_pop_front(t_ref *ref)
{
  t_buffer	*elem;

  elem = ref->begin;
  if (!elem)
    return ;
  if (ref->end == ref->begin)
    ref->end = NULL;
  ref->begin = ref->begin->next;
  delete_command(elem->tab, elem->buffer);
  free(elem);
  --(ref->buffer_size);
}

void		display_buffer_from_client(t_ref *ref)
{
  t_buffer	*elem;

  elem = ref->begin;
  printf("display buffer =>\n");
  while (elem)
    {
      printf("%s%s", elem->buffer, elem->next ? "" : "\n");
      elem = elem->next;
    }
}
