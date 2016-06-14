/*
** comannd_line_opt.c for COMMAND LINE in /home/gouet_v/Rendu/semester4/PSU/PSU_2015_zappy
** 
** Made by Victor Gouet
** Login   <gouet_v@epitech.net>
** 
** Started on  Mon Jun  6 23:02:11 2016 Victor Gouet
** Last update Tue Jun  7 12:27:13 2016 Victor Gouet
*/

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <getopt.h>
#include "../include_server/command_line_arguments.h"

int		on_port(t_command_line *command)
{
  command->port = atoi(optarg);
  return (SUCCESS);
}

int		on_width(t_command_line *command)
{
  command->x = atoi(optarg);
  return (SUCCESS);
}

int		on_height(t_command_line *command)
{
  command->y = atoi(optarg);
  return (SUCCESS);
}

int		on_team_name(t_command_line *command, char **av)
{
  int		i = optind - 1;
  t_team_name	*elem;

  while (av[i] != NULL && av[i][0] != '-')
    {
      if ((elem = add_team_elem(&(command->team_list))) == NULL)
	return (FAILURE);
      if ((elem->name = strdup(av[i])) == NULL)
	return (FAILURE);
      ++i;
    }
  return (SUCCESS);
}
int		on_client_nbr(t_command_line *command)
{
  command->nb_client = atoi(optarg);
  return (SUCCESS);
}
