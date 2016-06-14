/*
** enw.c for ENW in /home/gouet_v/Rendu/semester4/PSU/PSU_2015_zappy/src_server/Monitor_event
** 
** Made by Victor Gouet
** Login   <gouet_v@epitech.net>
** 
** Started on  Mon Jun 13 13:38:46 2016 Victor Gouet
** Last update Tue Jun 14 10:39:34 2016 Victor Gouet
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
