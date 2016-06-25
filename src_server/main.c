/*
** main.c for SERVER in /home/gouet_v/Rendu/semester4/PSU/PSU_2015_zappy
** 
** Made by Victor Gouet
** Login   <gouet_v@epitech.net>
** 
** Started on  Mon Jun  6 21:45:10 2016 Victor Gouet
** Last update Sat Jun 25 12:43:37 2016 Victor Gouet
*/

#include <stdio.h>
#include "../include_server/server.h"

static void		display_command(t_command_line *command)
{
  t_team_name		*elem;

  elem = command->team_list.begin;
  printf("Team name:\n");
  while (elem)
    {
      printf("%s\n", elem->name);
      elem = elem->next;
    }
  printf("port: %d\n", command->port);
  printf("width: %d\n", command->x);
  printf("height: %d\n", command->y);
  printf("client\'s number: %d\n", command->nb_client);
  printf("time: %d\n", command->time);
}

int			main(int ac, char **av)
{
  t_command_line	command;

  srand(time(NULL));
  if (on_command_line_server(ac, av, &command) == FAILURE)
    {
      return (1);
    }
  display_command(&command);
  server_run(&command);
  return (0);
}
