/*
** smg.c for SMG in /home/gouet_v/Rendu/semester4/PSU/PSU_2015_zappy/src_server/Monitor_event
** 
** Made by Victor Gouet
** Login   <gouet_v@epitech.net>
** 
** Started on  Mon Jun 13 13:41:15 2016 Victor Gouet
** Last update Tue Jun 14 01:36:02 2016 Victor Gouet
*/

#include "../../include_server/monitor_event.h"
#include "../../stringLib/storage.h"

int	smg_event(char *msg, t_list *list)
{
  char	*str;

  str = STRING("smg %s\n", msg);
  send_msg_to_all_monitor(str, list);
  return (0);
}
