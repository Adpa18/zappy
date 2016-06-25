/*
** ppo.c for PPO in /home/gouet_v/Rendu/semester4/PSU/PSU_2015_zappy/src_server/Monitor_event
** 
** Made by Victor Gouet
** Login   <gouet_v@epitech.net>
** 
** Started on  Mon Jun 13 13:41:02 2016 Victor Gouet
** Last update Sat Jun 25 15:49:03 2016 Victor Gouet
*/

#include <stdlib.h>
#include "../../include_server/monitor_event.h"
#include "../../stringLib/storage.h"

int		ppo_event(t_monitor *monitor, t_list *list,
			  t_command_line *command, char **tab)
{
  t_trantorien	*trantorien;

  (void)command;
  if (!tab[1])
    return (sbp_event(monitor));
  if (!(trantorien = get_trantorien_from_id(list, atoi(tab[1]))))
    return (sbp_event(monitor));
  fbufferise(monitor->ref,
	     "ppo %d %d %d %d\n", trantorien->id, trantorien->pos.x,
	     trantorien->pos.y, trantorien->orientation);
  return (0);
}

int		ppo_event_to_all_monitor(t_trantorien *trantorien,
					 t_list *list)
{
  char		*msg;

  msg = STRING("ppo %d %d %d %d\n",
	       trantorien->id, trantorien->pos.x,
	       trantorien->pos.y, trantorien->orientation);
  if (msg)
    {
      send_msg_to_all_monitor(msg, list);
      free(msg);
    }
  return (0);
}
