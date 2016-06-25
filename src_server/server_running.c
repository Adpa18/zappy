/*
** server_running.c for SERVER in /home/gouet_v/Rendu/semester4/PSU/PSU_2015_zappy
** 
** Made by Victor Gouet
** Login   <gouet_v@epitech.net>
** 
** Started on  Sat Jun 25 18:44:02 2016 Victor Gouet
** Last update Sat Jun 25 18:49:18 2016 Victor Gouet
*/

#include <stdio.h>
#include <sys/select.h>
#include "../include_server/server.h"

static int		init_select(fd_set *fds,
				    int const server,
				    t_list *list)
{
  t_ref			*elem;
  struct timeval	timeout;

  FD_ZERO(fds);
  timeout.tv_sec = 0;
  timeout.tv_usec = 1000;
  FD_SET(server, fds);
  elem = list->begin;
  while (elem)
    {
      FD_SET(elem->client->sock.sock, fds);
      elem = elem->next;
    }
  if (select(list->max_fd + 1, fds, NULL, NULL, &timeout) == -1)
    {
      return (-1);
    }
  return (0);
}

int		server_running_event(t_list *list, t_server *server,
				       t_command_line *command,
				       fd_set *fds)
{
t_client	*client;
t_ref		*ref;

  if (init_select(fds, server->socket.sock, list) == -1)
    return (-1);
  if (FD_ISSET(server->socket.sock, fds))
    {
      if ((client = get_client_connection(server)) == NULL ||
	  ((ref = add_client_to_list(list, UNKNOWN, client)) == NULL))
	return (-1);
      bufferise(ref, BIENVENUE);
      ressources_generation(list, list->map, 3, 6);
    }
  else
    if (event_client(list, command, fds, server) == 2)
      return (flush_buffer_clients(list), -1);
  flush_buffer_clients(list);
  return (0);
}
