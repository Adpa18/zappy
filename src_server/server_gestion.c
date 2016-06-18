/*
** server_gestion.c for GESTION DU SERVER in /home/gouet_v/Rendu/semester4/PSU/PSU_2015_zappy
** 
** Made by Victor Gouet
** Login   <gouet_v@epitech.net>
** 
** Started on  Mon Jun  6 22:04:34 2016 Victor Gouet
** Last update Fri Jun 17 12:15:03 2016 Victor Gouet
*/

#include <signal.h>
#include <sys/select.h>
#include <stdio.h>
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

static int	init_all(t_list *list, t_server **server,
			  t_command_line *command)
{
  if ((*server = create_server(100, TCP, AF_INET, command->port)) == NULL)
    return (-1);
  list_constructor(list, (*server)->socket.sock);
  if ((list->map = create_map(command->x, command->y)) == NULL)
    {
      delete_server(*server);
      return (-1);
    }
  generate_random_ressources(list->map);
  return (0);
}

void		on_catch_sigint(int signal)
{
  (void)signal;
}

static void	delete_all(t_server *server,
			   t_command_line *command,
			   t_list *list)
{
  remove_all_team(&(command->team_list));
  remove_map(list->map);
  remove_all_list(list);
  delete_server(server);
}

void		server_run(t_command_line *command)
{
  t_server	*server;
  t_client	*client;
  fd_set	fds;
  t_list	list;

  signal(SIGINT, on_catch_sigint);
  if (init_all(&list, &server, command) == -1)
    return ;
  while (server)
    {
      if (init_select(&fds, server->socket.sock, &list) == -1)
        break;
      if (FD_ISSET(server->socket.sock, &fds))
	{
	  if ((client = get_client_connection(server)) == NULL)
	    break;
	  if (add_client_to_list(&list, UNKNOWN, client) == NULL)
	    break;
	  send_message(BIENVENUE, &(client->sock));
	}
      else
	event_client(&list, command, &fds, server);
    }
  delete_all(server, command, &list);
}
