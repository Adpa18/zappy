/*
** pex.c for PEX in /home/gouet_v/Rendu/semester4/PSU/PSU_2015_zappy/src_server/Monitor_event
** 
** Made by Victor Gouet
** Login   <gouet_v@epitech.net>
** 
** Started on  Mon Jun 13 13:40:33 2016 Victor Gouet
** Last update Tue Jun 14 12:59:17 2016 Victor Gouet
*/

#include "../../include_server/monitor_event.h"
#include "../../stringLib/storage.h"

int     pex_event(t_trantorien *trantorien, t_list *list)
{
  char	*msg;

  msg = STRING("pex %d\n", trantorien->id);
  if (msg)
    {
      send_msg_to_all_monitor(msg, list);
      free(msg);
    }
  return (0);
}
