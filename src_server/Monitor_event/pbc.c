/*
** pbc.c for PBC in /home/gouet_v/Rendu/semester4/PSU/PSU_2015_zappy/src_server/Monitor_event
** 
** Made by Victor Gouet
** Login   <gouet_v@epitech.net>
** 
** Started on  Mon Jun 13 13:38:38 2016 Victor Gouet
** Last update Tue Jun 14 14:41:28 2016 Victor Gouet
*/

#include "../../include_server/monitor_event.h"
#include "../../stringLib/storage.h"

int     pbc_event(t_trantorien *trantorien, t_list *list, char *msg)
{
  char	*str;

  str = STRING("pbc %d %s\n", trantorien->id, msg);
  if (str)
    {
      send_msg_to_all_monitor(str, list);
      free(str);
    }
  return (0);
}
