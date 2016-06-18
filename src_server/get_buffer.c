/*
** get_buffer.c for BUFFER in /home/gouet_v/Rendu/semester4/PSU/PSU_2015_zappy
** 
** Made by Victor Gouet
** Login   <gouet_v@epitech.net>
** 
** Started on  Thu Jun 16 15:34:36 2016 Victor Gouet
** Last update Thu Jun 16 15:42:20 2016 Victor Gouet
*/

#include "../include_server/server.h"

char		*get_buffer_from_client_without_cammand(t_ref *ref)
{
  t_buffer	*buffer;
  char		*str;

  buffer = ref->begin;
  if (!buffer)
    return (NULL);
  str = buffer->buffer;
  while (str != NULL && *str != '\0' && *str == ' ')
    ++str;
  while (str != NULL && *str != '\0' && *str != ' ')
    ++str;
  while (str != NULL && *str != '\0' && *str == ' ')
    ++str;
  return (str);
}
