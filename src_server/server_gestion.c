/*
** server_gestion.c for GESTION DU SERVER in /home/gouet_v/Rendu/semester4/PSU/PSU_2015_zappy
** 
** Made by Victor Gouet
** Login   <gouet_v@epitech.net>
** 
** Started on  Mon Jun  6 22:04:34 2016 Victor Gouet
** Last update Sat Jun 25 18:58:31 2016 Victor Gouet
*/

#include <signal.h>
#include <sys/select.h>
#include <stdio.h>
#include "../include_server/server.h"

static int	on_sigint = false;

void		on_catch_sigint(int signal)
{
  on_sigint = true;
  (void)signal;
}

static int	init_all(t_list *list, t_server **server,
			  t_command_line *command)
{
  signal(SIGINT, on_catch_sigint);
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
  fd_set	fds;
  t_list	list;

  if (init_all(&list, &server, command) == -1)
    return ;
  while (server && !on_sigint)
    {
      if (server_running_event(&list, server, command, &fds) == -1)
	break;
    }
  delete_all(server, command, &list);
}
