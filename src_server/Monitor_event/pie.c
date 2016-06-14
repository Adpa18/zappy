/*
** pie.c for PIE in /home/gouet_v/Rendu/semester4/PSU/PSU_2015_zappy/src_server/Monitor_event
** 
** Made by Victor Gouet
** Login   <gouet_v@epitech.net>
** 
** Started on  Mon Jun 13 13:40:47 2016 Victor Gouet
** Last update Tue Jun 14 15:45:43 2016 Victor Gouet
*/

#include "../../include_server/monitor_event.h"
#include "../../stringLib/storage.h"

int		pie_event(t_trantorien *trantorien, t_list *list,
			  int succes)
{
  char		*msg;
  t_vector2d	pos;

  pos.x = trantorien->pos.x;
  pos.y = trantorien->pos.y;
  msg = STRING("pie %d %d %d\n", trantorien->pos.x, trantorien->pos.y,
	       succes);
  if (msg)
    {
      send_msg_to_all_monitor(msg, list);
      free(msg);
    }
  return (0);
}
