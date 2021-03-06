/*
** plv.c for PLV in /home/gouet_v/Rendu/semester4/PSU/PSU_2015_zappy/src_server/Monitor_event
** 
** Made by Victor Gouet
** Login   <gouet_v@epitech.net>
** 
** Started on  Mon Jun 13 13:40:54 2016 Victor Gouet
** Last update Sat Jun 25 15:48:15 2016 Victor Gouet
*/

#include "../../include_server/monitor_event.h"
#include "../../stringLib/storage.h"

int		plv_event(t_monitor *monitor, t_list *list,
			  t_command_line *command, char **tab)
{
  t_trantorien	*trantorien;

  (void)command;
  if (!tab[1])
    return (sbp_event(monitor));
  if (!(trantorien = get_trantorien_from_id(list, atoi(tab[1]))))
    return (sbp_event(monitor));
  fbufferise(monitor->ref, "plv %d %d\n",
	     trantorien->id, trantorien->elevation);
  return (0);
}

int		plv_event_all_monitor(t_list *list)
{
  char		*msg;
  t_ref		*ref;
  t_trantorien	*trantorien;

  ref = list->begin;
  while (ref)
    {
      if (ref->type == TRANTORIEN)
	{
	  trantorien = ref->ref;
	  msg = STRING("plv %d %d\n", trantorien->id, trantorien->elevation);
	  if (msg)
	    {
	      send_msg_to_all_monitor(msg, list);
	      free(msg);
	    }
	}
      ref = ref->next;
    }
  return (0);
}

int		plv_event_for_one_trantorien(t_list *list,
					     t_trantorien *trantorien)
{
  char		*msg;

  msg = STRING("plv %d %d\n", trantorien->id, trantorien->elevation);
  if (msg)
    {
      send_msg_to_all_monitor(msg, list);
      free(msg);
    }
    return (0);
}
