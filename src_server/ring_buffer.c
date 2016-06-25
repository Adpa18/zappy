/*
** ring_buffer.c for BUFFER in /home/gouet_v/Rendu/semester4/PSU/PSU_2015_myirc
** 
** Made by Victor Gouet
** Login   <gouet_v@epitech.net>
** 
** Started on  Fri Jun  3 09:49:21 2016 Victor Gouet
** Last update Sat Jun 25 10:57:17 2016 Victor Gouet
*/

#include <stdio.h>
#include <stdarg.h>
#include <strings.h>
#include "../include_server/ring_buffer.h"
#include "../include_server/server.h"

void	reset(t_ring_buffer *ring)
{
  ring->begin = 0;
  ring->end = 0;
  bzero(ring->buffer, sizeof(ring->buffer));
}

static int		init_select_for_fd(fd_set *fds, int fd)
{
  struct timeval	timeout;

  FD_ZERO(fds);
  timeout.tv_sec = 0;
  timeout.tv_usec = 0;
  FD_SET(fd, fds);
  if (select(fd + 1, NULL, fds, NULL, &timeout) == -1)
    {
      return (-1);
    }
  return (0);
}

void		flush(t_ref *client)
{
  fd_set	fds;

  if (client->ring.buffer[0] == 0)
    {
      reset(&(client->ring));
      return ;
    }
  init_select_for_fd(&fds, client->client->sock.sock);
  if (FD_ISSET(client->client->sock.sock, &fds))
    {
      send_message(client->ring.buffer, &(client->client->sock));
      reset(&(client->ring));
    }
}

void	bufferise(t_ref *client, char *data)
{
  while (*data != '\0')
    {
      client->ring.buffer[(client->ring.end)++] = *data;
      if (client->ring.end >= (int)(sizeof(client->ring.buffer) - 1))
	{
	  client->ring.buffer[client->ring.end] = '\0';
	  flush(client);
	}
      ++data;
    }
}

void		fbufferise(t_ref *client, char *format, ...)
{
  va_list	list;
  char		tosend[BUFSIZ];

  va_start(list, format);
  if (vsnprintf(tosend, BUFSIZ - 1, format, list) != -1)
    bufferise(client, tosend);
  va_end(list);
}
