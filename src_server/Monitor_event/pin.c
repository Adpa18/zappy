/*
** pin.c for PIN in /home/gouet_v/Rendu/semester4/PSU/PSU_2015_zappy/src_server/Monitor_event
** 
** Made by Victor Gouet
** Login   <gouet_v@epitech.net>
** 
** Started on  Mon Jun 13 13:38:05 2016 Victor Gouet
** Last update Sat Jun 25 10:08:47 2016 Victor Gouet
*/

#include "../../include_server/monitor_event.h"
#include "../../stringLib/storage.h"

int		pin_event(t_monitor *monitor, t_list *list,
			  t_command_line *command, char **tab)
{
  t_trantorien	*trantorien;

  (void)command;
  if (!tab[1])
    return (sbp_event(monitor));
  if (!(trantorien = get_trantorien_from_id(list, atoi(tab[1]))))
    return (sbp_event(monitor));
  /* sendf_message(&(monitor->ref->client->sock), */
  /* 		"pin %d %d %d %d %d %d %d %d %d %d\n", */
  /* 		trantorien->id, */
  /* 		trantorien->pos.x, trantorien->pos.y, */
  /* 	        trantorien->inventaire.food, */
  /* 		trantorien->inventaire.linemate, */
  /* 	        trantorien->inventaire.deraumere, */
  /* 	        trantorien->inventaire.sibur, */
  /* 	        trantorien->inventaire.mendiane, */
  /* 	        trantorien->inventaire.phiras, */
  /* 	        trantorien->inventaire.thystame); */
  fbufferise(monitor->ref,
	     "pin %d %d %d %d %d %d %d %d %d %d\n",
	     trantorien->id,
	     trantorien->pos.x, trantorien->pos.y,
	     trantorien->inventaire.food,
	     trantorien->inventaire.linemate,
	     trantorien->inventaire.deraumere,
	     trantorien->inventaire.sibur,
	     trantorien->inventaire.mendiane,
	     trantorien->inventaire.phiras,
	     trantorien->inventaire.thystame);
  return (0);
}

int     pin_event_to_all_monitor(t_list *list, t_trantorien *trantorien)
{
  char	*msg;

  msg = STRING("pin %d %d %d %d %d %d %d %d %d %d\n",
	       trantorien->id,
	       trantorien->pos.x, trantorien->pos.y,
	       trantorien->inventaire.food,
	       trantorien->inventaire.linemate,
	       trantorien->inventaire.deraumere,
	       trantorien->inventaire.sibur,
	       trantorien->inventaire.mendiane,
	       trantorien->inventaire.phiras,
	       trantorien->inventaire.thystame);
  if (msg)
    {
      send_msg_to_all_monitor(msg, list);
      free(msg);
    }
  return (0);
}
