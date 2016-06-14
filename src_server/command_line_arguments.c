/*
** command_line_arguments.c for COMMAND LINE in /home/gouet_v/Rendu/semester4/PSU/PSU_2015_zappy
** 
** Made by Victor Gouet
** Login   <gouet_v@epitech.net>
** 
** Started on  Mon Jun  6 22:40:39 2016 Victor Gouet
** Last update Mon Jun 13 22:51:13 2016 Victor Gouet
*/

#include <stdlib.h>
#include <stdio.h>
#include <getopt.h>
#include "../include_server/command_line_arguments.h"

static t_opt_gestion	opt_gestion[OPTION_NBR] = {
  {
    &on_port,
    'p'
  },
  {
    &on_width,
    'x'
  },
  {
    &on_height,
    'y'
  },
  {
    &on_team_name,
    'n'
  },
  {
    &on_client_nbr,
    'c'
  },
  {
    &on_time,
    't'
  },
};

t_team_name	*add_team_elem(t_team_list *list)
{
  t_team_name	*elem;

  if ((elem = malloc(sizeof(*elem))) == NULL)
    return (NULL);
  elem->next = NULL;
  elem->begin = NULL;
  elem->end = NULL;
  elem->nbr_client = 0;
  elem->nbr_max = 0;
  if (list->begin == NULL && list->end == NULL)
    {
      list->begin = elem;
    }
  else
    {
      list->end->next = elem;
    }
  list->end = elem;
  return (elem);
}

int		on_time(t_command_line *command)
{
  command->time = atoi(optarg);
  return (SUCCESS);
}

static void     constructor_command_line(t_command_line *command)
{
  command->nb_client = -1;
  command->port = -1;
  command->team_list.begin = NULL;
  command->team_list.end = NULL;
  command->time = DEFAULTTIME;
  command->x = -1;
  command->y = -1;
}

static int     is_command_line_valid(t_command_line *command)
{
  t_team_name	*team;

  if (command->nb_client == -1
      || command->port == -1
      || command->team_list.begin == NULL
      || command->x == -1
      || command->y == -1)
    {
      fprintf(stderr, "Usage: -p port -x width -y height -n name_of_team");
      fprintf(stderr, " -c client\'s number [-t] time delay\n");
      return (FAILURE);
    }
  team = command->team_list.begin;
  while (team)
    {
      team->nbr_max = command->nb_client;
      team = team->next;
    }
  return (SUCCESS);
}

int	on_command_line_server(int ac, char **av,
			       t_command_line *command)
{
  int	option;
  int	idx;

  constructor_command_line(command);
  while ((option = getopt(ac, av, "p:x:y:n:c:t:")) != -1)
    {
      idx = 0;
      while (idx < OPTION_NBR)
	{
	  if (opt_gestion[idx].opt == option)
	    {
	      if (opt_gestion[idx].fptr(command, av) == FAILURE)
		return (FAILURE);
	      break;
	    }
	  ++idx;
	}
      if (idx == OPTION_NBR)
	{
	  fprintf(stderr, "Usage: -p port -x width -y height -n name_of_team");
	  fprintf(stderr, " -c client\'s number [-t] time delay\n");
	  return (FAILURE);
	}
    }
  return (is_command_line_valid(command));
}
