/*
** ring_buffer.c for BUFFER in /home/gouet_v/Rendu/semester4/PSU/PSU_2015_myirc
** 
** Made by Victor Gouet
** Login   <gouet_v@epitech.net>
** 
** Started on  Fri Jun  3 09:49:21 2016 Victor Gouet
** Last update Sat Jun 25 08:58:56 2016 Victor Gouet
*/

#include <strings.h>
#include "../include_server/ring_buffer.h"
#include "../include_server/server.h"

void	reset(t_ring_buffer *ring)
{
  ring->begin = 0;
  ring->end = 0;
  bzero(ring->buffer, sizeof(ring->buffer));
}

void	flush(t_ref *client)
{
  send_message(client->ring.buffer, &(client->client->sock));
  reset(&(client->ring));
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
