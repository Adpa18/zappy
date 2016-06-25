/*
** inventaire_event.c for INVENTAIRE in /home/gouet_v/Rendu/semester4/PSU/PSU_2015_zappy/src_server/Trantorien_Event
** 
** Made by Victor Gouet
** Login   <gouet_v@epitech.net>
** 
** Started on  Wed Jun  8 07:52:19 2016 Victor Gouet
** Last update Sat Jun 25 15:51:24 2016 Victor Gouet
*/

#include "../../include_server/trantorien_event.h"

int     inventaire_event(t_trantorien *trantorien, t_list *list,
			 t_command_line *command, char **tab)
{
  fbufferise(trantorien->ref,
		START_INVETAIRE END_INVENTAIRE,
		trantorien->inventaire.food, trantorien->inventaire.linemate,
		trantorien->inventaire.deraumere, trantorien->inventaire.sibur,
		trantorien->inventaire.mendiane, trantorien->inventaire.phiras,
		trantorien->inventaire.thystame);
  (void)list;
  (void)command;
  (void)tab;
  return (0);
}
