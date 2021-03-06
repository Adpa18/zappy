/*
** pfk.c for PFK in /home/gouet_v/Rendu/semester4/PSU/PSU_2015_zappy/src_server/Monitor_event
** 
** Made by Victor Gouet
** Login   <gouet_v@epitech.net>
** 
** Started on  Mon Jun 13 13:38:21 2016 Victor Gouet
** Last update Tue Jun 14 00:39:48 2016 Victor Gouet
*/

#include "../../stringLib/storage.h"
#include "../../include_server/monitor_event.h"

int	pfk_event(t_trantorien *trantorien, t_list *list)
{
  char	*msg;

  msg = STRING("pfk %d\n", trantorien->id);
  if (msg)
    {
      send_msg_to_all_monitor(msg, list);
      free(msg);
    }
  return (0);
}
