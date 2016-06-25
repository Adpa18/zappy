/*
** flush_buffer.c for FLUSH in /home/gouet_v/Rendu/semester4/PSU/PSU_2015_zappy
** 
** Made by Victor Gouet
** Login   <gouet_v@epitech.net>
** 
** Started on  Sat Jun 25 10:23:11 2016 Victor Gouet
** Last update Sat Jun 25 11:05:01 2016 Victor Gouet
*/

#include "../include_server/server.h"

int		flush_buffer_clients(t_list *list)
{
  t_ref		*ref;

  ref = list->begin;
  while (ref)
    {
      flush(ref);
      ref = ref->next;
    }
  return (0);
}
