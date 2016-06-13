/*
** die_event.c for TRANTORIAN in /home/gouet_v/Rendu/semester4/PSU/PSU_2015_zappy
** 
** Made by Victor Gouet
** Login   <gouet_v@epitech.net>
** 
** Started on  Mon Jun 13 12:06:19 2016 Victor Gouet
** Last update Tue Jun 14 01:03:33 2016 Victor Gouet
*/

#include "../../include_server/trantorien_event.h"
#include "../../include_server/monitor_event.h"

int	die_event(t_trantorien *trantorien, t_list *list)
{
  send_message("mort\n", &(trantorien->ref->client->sock));
  if (trantorien->state == BABY)
    {
      edi_event(trantorien, list);
    }
  else
    {
      pdi_event(trantorien, list);
    }
  return (0);
}
