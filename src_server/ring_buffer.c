/*
** ring_buffer.c for BUFFER in /home/gouet_v/Rendu/semester4/PSU/PSU_2015_myirc
** 
** Made by Victor Gouet
** Login   <gouet_v@epitech.net>
** 
** Started on  Fri Jun  3 09:49:21 2016 Victor Gouet
** Last update Sun Jun 26 19:53:17 2016 Victor Gouet
*/

#include "../include_server/ring_buffer.h"
#include "../include_server/server.h"
#include <poll.h>

void	reset(t_ring_buffer *ring)
{
  ring->begin = 0;
  ring->end = 0;
  bzero(ring->buffer, sizeof(ring->buffer));
}

<<<<<<< HEAD
/* static int		init_select_for_fd(fd_set *fds, int fd) */
/* { */
/*   struct timeval	timeout; */

/*  FD_ZERO(fds);
  timeout.tv_sec = 0;
  timeout.tv_usec = 0;
  if (fd < 0)
      return (-1);
  FD_SET(fd, fds);
  if (select(fd + 1, NULL, fds, NULL, &timeout) == -1)
    {
      return (-1);
    }
  return (0);
}*/
/*   FD_ZERO(fds); */
/*   timeout.tv_sec = 0; */
/*   timeout.tv_usec = 0; */
/*   FD_SET(fd, fds); */
/*   if (select(fd + 1, NULL, fds, NULL, &timeout) == -1) */
/*     { */
/*       return (-1); */
/*     } */
/*   return (0); */
/* } */

=======
>>>>>>> bb899acd5eb3a555d8517e36e7328c5cf35219b0
void		flush(t_ref *client)
{
  struct pollfd	fds;
  int		rc;

  printf("client = %p\n", client);
  printf("client->client = %p\n", client->client);
  printf("client->client->sock = %p\n", &(client->client->sock));
  printf("fd = %d\t%d\n", client->client->sock.sock, FD_SETSIZE);
  if (client->ring.buffer[0] == 0 || client->client->sock.sock < 0)
    {
      reset(&(client->ring));
      return ;
    }
  fds.fd = client->client->sock.sock;
  fds.events = POLLOUT;
  if ((rc = poll(&fds, 1, 0)) == -1)
    {
      reset(&(client->ring));
      return ;
    }
  if (rc == 1)
    {
      send_message(client->ring.buffer, &(client->client->sock));
      reset(&(client->ring));
    }
}

void	bufferise(t_ref *client, char *data)
{
  int	i;

  i = 0;
  while (data[i] != '\0')
    {
      client->ring.buffer[(client->ring.end)++] = data[i];
      if (client->ring.end >= (int)(sizeof(client->ring.buffer) - 1))
      	{
      	  client->ring.buffer[client->ring.end] = '\0';
      	  flush(client);
      	}
      ++i;
    }
}

void		fbufferise(t_ref *client, char *format, ...)
{
  va_list	list;
  char		*tosend;

  va_start(list, format);
  if (vasprintf(&tosend, format, list) != -1)
    {
      bufferise(client, tosend);
      free(tosend);
    }
  va_end(list);
}
