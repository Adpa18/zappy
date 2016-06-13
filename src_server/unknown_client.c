/*
** unknown_client.c for UNKNOWN CLINET in /home/gouet_v/Rendu/semester4/PSU/PSU_2015_zappy
** 
** Made by Victor Gouet
** Login   <gouet_v@epitech.net>
** 
** Started on  Tue Jun  7 16:47:38 2016 Victor Gouet
** Last update Mon Jun 13 11:36:35 2016 Victor Gouet
*/

#include <stdio.h>
#include <string.h>
#include "../include_server/server.h"
#include "../include_server/time_gestion.h"

static int	trantorien_connection(t_ref *ref, t_team_name *team,
				      t_command_line *command)
{
  t_trantorien	*trantorien;
  int		client_left;

  client_left = command->nb_client - team->nbr_client - 1;
  if (client_left == -1)
    {
      send_message("ko\n", &(ref->client->sock));
      return (-1);
    }
  sendf_message(&(ref->client->sock), "%d\n", client_left);
  sendf_message(&(ref->client->sock), "%d %d\n", command->x, command->y);
  trantorien = transform_to_trantorien(ref);
  add_client_to_team(team, trantorien);
  bzero(&(trantorien->inventaire), sizeof(t_inventories));
  trantorien->orientation = (rand() % 4) + 1;
  trantorien->inventaire.food = 10;
  trantorien->time_left_food = getTimeSeconds();
  trantorien->elevation = 1;
  trantorien->pos.x = rand() % command->x;
  trantorien->pos.y = rand() % command->y;
  return (0);
}

int		unknwon_client_event(t_ref *ref, t_list *list,
				     t_command_line *command,
				     char **tab)
{
  t_team_name	*team;
  t_monitor	*monitor;

  (void)list;
  if (strcmp(tab[0], GRAPHIC) == 0)
    {
      monitor = transform_to_monitor(ref);
      monitor->data = 0;
    }
  else if ((team = get_team(&(command->team_list), tab[0])))
    {
      return (trantorien_connection(ref, team, command));
    }
  else
    {
      send_message("ko\n", &(ref->client->sock));
      return (-1);
    }
  return (0);
}

