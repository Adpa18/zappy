/*
** sbp.c for SBP in /home/gouet_v/Rendu/semester4/PSU/PSU_2015_zappy/src_server/Monitor_event
** 
** Made by Victor Gouet
** Login   <gouet_v@epitech.net>
** 
** Started on  Mon Jun 13 13:37:49 2016 Victor Gouet
** Last update Tue Jun 14 01:28:49 2016 Victor Gouet
*/

#include "../../include_server/monitor_event.h"

int     sbp_event(t_monitor *monitor)
{
  send_message("sbp\n", &(monitor->ref->client->sock));
  return (0);
}
