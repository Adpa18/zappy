/*
** egg_gestion.c for EGG in /home/gouet_v/Rendu/semester4/PSU/PSU_2015_zappy
** 
** Made by Victor Gouet
** Login   <gouet_v@epitech.net>
** 
** Started on  Mon Jun 13 23:09:39 2016 Victor Gouet
** Last update Tue Jun 14 12:09:59 2016 Victor Gouet
*/

#include "../include_server/server.h"
#include "../include_server/time_gestion.h"
#include "../include_server/monitor_event.h"

void		on_gestion_egg(t_command_line *command, t_list *list)
{
  t_trantorien	*trantorien;
  t_team_name	*team;
  long long	time_left;
  
  time_left = ((double)600 / (command->time == 0 ? 1 : command->time)) * 1000;
  team = command->team_list.begin;
  while (team)
    {
      trantorien = team->begin;
      while (trantorien)
	{
	  if (trantorien->state == EGG)
	    {
	      if (is_time_out_in(trantorien->spawn, time_left))
		{
		  trantorien->state = BABY;
		  eht_event(trantorien, list);
		  ++(team->nbr_max);
		}
	    }
	  trantorien = trantorien->next_on_team;
	}
      team = team->next;
    }
}

int		create_egg_on_team_from_trantorien(t_vector2d pos,
						   t_team_name *team,
						   t_trantorien *player,
						   t_list *list)
{
  t_trantorien	*trantorien;
  static int	egg_id = 1;

  if ((trantorien = malloc(sizeof(*trantorien))) == NULL)
    return (-1);
  add_client_to_team(team, trantorien);
  (team->nbr_client)--;
  init_trantorien(trantorien, pos.x, pos.y);
  trantorien->state = EGG;
  trantorien->id_parrent = player->id;
  trantorien->egg_id = egg_id++;
  enw_event(player, trantorien, list);
  return (0);
}
