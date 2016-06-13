/*
** die_event.c for TRANTORIAN in /home/gouet_v/Rendu/semester4/PSU/PSU_2015_zappy
** 
** Made by Victor Gouet
** Login   <gouet_v@epitech.net>
** 
** Started on  Mon Jun 13 12:06:19 2016 Victor Gouet
** Last update Mon Jun 13 12:09:06 2016 Victor Gouet
*/

#include "../../include_server/trantorien_event.h"

int	die_event(t_trantorien *trantorien)
{
  send_message("mort\n", &(trantorien->ref->client->sock));
  return (0);
}
