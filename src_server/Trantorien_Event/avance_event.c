/*
** avance_event.c for AVANCE in /home/gouet_v/Rendu/semester4/PSU/PSU_2015_zappy/src_server/Trantorien_Event
** 
** Made by Victor Gouet
** Login   <gouet_v@epitech.net>
** 
** Started on  Wed Jun  8 07:49:13 2016 Victor Gouet
** Last update Wed Jun  8 11:49:53 2016 Victor Gouet
*/

#include "../../include_server/trantorien_event.h"

int	avance_event(t_trantorien *trantorien, t_list *list,
		     t_command_line *command, char **tab)
{
  send_message("ok\n", &(trantorien->ref->client->sock));
  return (0);
}
