/*
** enw.c for ENW in /home/gouet_v/Rendu/semester4/PSU/PSU_2015_zappy/src_server/Monitor_event
** 
** Made by Victor Gouet
** Login   <gouet_v@epitech.net>
** 
** Started on  Mon Jun 13 13:38:46 2016 Victor Gouet
** Last update Sat Jun 25 15:49:18 2016 Victor Gouet
*/

#include "../../include_server/monitor_event.h"
#include "../../stringLib/storage.h"

int     enw_event(t_trantorien *player, t_trantorien *egg,
		  t_list *list)
{
  char	*msg;

  msg = STRING("enw %d %d %d %d\n", egg->egg_id, player->id,
	       egg->pos.x, egg->pos.y);
  if (msg)
    {
      send_msg_to_all_monitor(msg, list);
      free(msg);
    }
  return (0);
}

static int	enw_msg(t_trantorien *trantorien, t_monitor *monitor)
{
  char		*msg;

  if (trantorien->state == EGG)
    {
      if ((msg = STRING("enw %d %d %d %d\n", trantorien->egg_id,
			trantorien->id_parrent, trantorien->pos.x,
			trantorien->pos.y)) == NULL)
	return (-1);
      bufferise(monitor->ref, msg);
      free(msg);
    }
  return (0);
}

int		enw_event_all_to_monitor(t_monitor *monitor,
					 t_command_line *command)
{
  t_trantorien	*ref;
  t_team_name	*team;

  team = command->team_list.begin;
  while (team)
    {
      ref = team->begin;
      while (ref)
	{
	  enw_msg(ref, monitor);
	  ref = ref->next_on_team;
	}
      team = team->next;
    }
  return (0);
}
