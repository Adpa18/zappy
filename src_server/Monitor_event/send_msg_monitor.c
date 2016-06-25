/*
** send_msg_monitor.c for MONITOR in /home/gouet_v/Rendu/semester4/PSU/PSU_2015_zappy
** 
** Made by Victor Gouet
** Login   <gouet_v@epitech.net>
** 
** Started on  Mon Jun 13 23:57:37 2016 Victor Gouet
** Last update Sat Jun 25 15:49:54 2016 Victor Gouet
*/

#include "../../stringLib/storage.h"
#include "../../include_server/monitor_event.h"

void	send_msg_to_all_monitor(char const *msg, t_list *list)
{
  t_ref	*ref;
  char	*tmp;

  if ((tmp = STRING("%s", msg)) == NULL)
    return ;
  ref = list->begin;
  while (ref)
    {
      if (ref->type == MONITOR)
	{
	  bufferise(ref, tmp);
	}
      ref = ref->next;
    }
  free(tmp);
}
