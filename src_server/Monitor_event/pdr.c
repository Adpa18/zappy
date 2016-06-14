/*
** pdr.c for PDR in /home/gouet_v/Rendu/semester4/PSU/PSU_2015_zappy/src_server/Monitor_event
** 
** Made by Victor Gouet
** Login   <gouet_v@epitech.net>
** 
** Started on  Mon Jun 13 13:38:29 2016 Victor Gouet
** Last update Tue Jun 14 00:39:24 2016 Victor Gouet
*/

#include "../../include_server/monitor_event.h"
#include "../../stringLib/storage.h"

int	pdr_event(t_trantorien *trantorien, t_list *list,
		  int id_ressource)
{
  char	*msg;

  msg = STRING("pdr %d %d\n", trantorien->id, id_ressource);
  if (msg)
    {
      send_msg_to_all_monitor(msg, list);
      free(msg);
    }
  return (0);
}
