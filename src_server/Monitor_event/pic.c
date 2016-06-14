/*
** pic.c for PIC in /home/gouet_v/Rendu/semester4/PSU/PSU_2015_zappy/src_server/Monitor_event
** 
** Made by Victor Gouet
** Login   <gouet_v@epitech.net>
** 
** Started on  Mon Jun 13 13:38:12 2016 Victor Gouet
** Last update Tue Jun 14 15:20:51 2016 Victor Gouet
*/

#include "../../include_server/monitor_event.h"
#include "../../stringLib/storage.h"

static char	*trantorien_create_msg(t_list *list,
				       t_vector2d pos,
				       int elevation,
				       char *msg)
{
  t_ref		*ref;
  t_trantorien	*trantorien;
  char		*data;

  ref = list->begin;
  while (ref)
    {
      if (ref->type == TRANTORIEN)
	{
	  trantorien = ref->ref;
	  if (trantorien->pos.x == pos.x
	      && trantorien->pos.y == pos.y
	      && trantorien->elevation == elevation)
	    {
	      data = msg;
	      if ((msg = STRING("%s %d", data, trantorien->id)) == NULL)
		return (NULL);
	      free(data);
	    }
	}
      ref = ref->next;
    }
  data = msg;
  msg = STRING("%s\n", data);
  return (free(data), msg);
}

int		pic_event(t_trantorien *trantorien, t_list *list)
{
  char		*msg;
  t_vector2d	pos;

  pos.x = trantorien->pos.x;
  pos.y = trantorien->pos.y;
  msg = STRING("pic %d %d %d", trantorien->pos.x, trantorien->pos.y,
	       trantorien->elevation);
  if (!msg)
    return (0);
  msg = trantorien_create_msg(list, pos, trantorien->elevation, msg);
  if (msg)
    {
      send_msg_to_all_monitor(msg, list);
      free(msg);
    }
  return (0);
}
