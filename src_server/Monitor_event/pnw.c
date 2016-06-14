/*
** pnw.c for PNW in /home/gouet_v/Rendu/semester4/PSU/PSU_2015_zappy/src_server/Monitor_event
** 
** Made by Victor Gouet
** Login   <gouet_v@epitech.net>
** 
** Started on  Mon Jun 13 13:37:58 2016 Victor Gouet
** Last update Tue Jun 14 00:03:55 2016 Victor Gouet
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
