/*
** trantorien_connection.c for TRANTORIEN in /home/gouet_v/Rendu/semester4/PSU/PSU_2015_zappy
** 
** Made by Victor Gouet
** Login   <gouet_v@epitech.net>
** 
** Started on  Mon Jun 13 21:37:18 2016 Victor Gouet
** Last update Tue Jun 14 00:25:55 2016 Victor Gouet
*/

#include <stdio.h>
#include <string.h>
#include "../include_server/server.h"
#include "../include_server/time_gestion.h"
#include "../include_server/monitor_event.h"

void	init_trantorien(t_trantorien *trantorien,
			int x, int y)
{
  static int	id = 1;

  bzero(&(trantorien->inventaire), sizeof(t_inventories));
  trantorien->state = PLAYER;
  trantorien->egg_id = 0;
  trantorien->orientation = (rand() % 4) + 1;
  trantorien->inventaire.food = 10;
  trantorien->time_left_food = getTimeSeconds();
  trantorien->elevation = 1;
  trantorien->spawn = getTimeSeconds();
  trantorien->pos.x = x;
  trantorien->pos.y = y;
  trantorien->id = id++;
}

static void	send_corect_event_to_monitor(t_trantorien *trantorien,
					     t_list *list)
{
  if (trantorien->state == GHOST)
    {
      // event qui existe pas encore
    }
  else if (trantorien->state == BABY)
    {
      ebo_event(trantorien, list);
    }
  else if (trantorien->state == PLAYER)
    {
      pnw_event(trantorien, list);
    }
}

int	trantorien_connection(t_ref *ref, t_team_name *team,
			      t_command_line *command, t_list *list)
{
  t_trantorien	*trantorien;
  int		client_left;

  client_left = team->nbr_max - team->nbr_client - 1;
  if (client_left <= -1)
    return (send_message("ko\n", &(ref->client->sock)), -1);
  sendf_message(&(ref->client->sock), "%d\n", client_left);
  sendf_message(&(ref->client->sock), "%d %d\n", command->x, command->y);
  if ((trantorien = get_trantorien_baby_from_team(team))
      || (trantorien = get_trantorien_ghost_from_team(team)))
    {
      trantorien->time_left_food = getTimeSeconds();
      convert_to_trantorien(ref, trantorien);
      send_corect_event_to_monitor(trantorien, list);
      trantorien->state = PLAYER;
      (team->nbr_client)++;
      return (0);
    }
  if ((trantorien = transform_to_trantorien(ref)) == NULL)
    return (-1);
  add_client_to_team(team, trantorien);
  init_trantorien(trantorien, rand() % command->x, rand() % command->y);
  send_corect_event_to_monitor(trantorien, list);
  return (0);
}
