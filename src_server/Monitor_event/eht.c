/*
** eht.c for EHT in /home/gouet_v/Rendu/semester4/PSU/PSU_2015_zappy/src_server/Monitor_event
** 
** Made by Victor Gouet
** Login   <gouet_v@epitech.net>
** 
** Started on  Mon Jun 13 13:39:21 2016 Victor Gouet
** Last update Tue Jun 14 00:57:20 2016 Victor Gouet
*/

#include "../../include_server/monitor_event.h"
#include "../../stringLib/storage.h"

int     eht_event(t_trantorien *egg,
		  t_list *list)
{
  char	*msg;

  msg = STRING("eht %d\n", egg->egg_id);
  if (msg)
    {
      send_msg_to_all_monitor(msg, list);
      free(msg);
    }
  return (0);
}
