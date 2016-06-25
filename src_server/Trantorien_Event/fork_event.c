/*
** fork_event.c for FORK in /home/gouet_v/Rendu/semester4/PSU/PSU_2015_zappy/src_server/Trantorien_Event
** 
** Made by Victor Gouet
** Login   <gouet_v@epitech.net>
** 
** Started on  Wed Jun  8 07:55:28 2016 Victor Gouet
** Last update Sat Jun 25 15:51:43 2016 Victor Gouet
*/

#include "../../include_server/trantorien_event.h"
#include "../../include_server/monitor_event.h"

int		fork_event(t_trantorien *trantorien, t_list *list,
			   t_command_line *command, char **tab)
{
  t_team_name	*team;
  t_vector2d	pos;

  if (!(team = get_team(&command->team_list, trantorien->team)))
    return (0);
  pos.x = trantorien->pos.x;
  pos.y = trantorien->pos.y;
  create_egg_on_team_from_trantorien(pos, team, trantorien, list);
  bufferise(trantorien->ref, "ok\n");
  (void)tab;
  return (0);
}
