/*
** pnw.c for PNW in /home/gouet_v/Rendu/semester4/PSU/PSU_2015_zappy/src_server/Monitor_event
** 
** Made by Victor Gouet
** Login   <gouet_v@epitech.net>
** 
** Started on  Mon Jun 13 13:37:58 2016 Victor Gouet
** Last update Sat Jun 25 15:59:56 2016 Victor Gouet
*/

#include "../../stringLib/storage.h"
#include "../../include_server/monitor_event.h"

int	pnw_event(t_trantorien *trantorien, t_list *list)
{
  char	*msg;

  msg = STRING("pnw %d %d %d %d %d %s\n", trantorien->id,
	       trantorien->pos.x, trantorien->pos.y,
	       trantorien->orientation, trantorien->elevation,
	       trantorien->team);
  if (msg)
    {
      send_msg_to_all_monitor(msg, list);
      free(msg);
    }
  return (0);
}

static int      pnw_msg(t_trantorien *trantorien, t_monitor *monitor)
{
  char		*msg;

  if (trantorien->state == PLAYER)
    {
      if ((msg = STRING("pnw %d %d %d %d %d %s\n", trantorien->id,
			trantorien->pos.x, trantorien->pos.y,
			trantorien->orientation, trantorien->elevation,
			trantorien->team)) == NULL)
	return (-1);
      bufferise(monitor->ref, msg);
      free(msg);
    }
  return (0);
}

int	        pnw_event_all_to_monitor(t_monitor *monitor,
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
	  pnw_msg(ref, monitor);
	  ref = ref->next_on_team;
	}
      team = team->next;
    }
  return (0);
}
