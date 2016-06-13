/*
** connect_nbr_event.c for CONNECT NBR in /home/gouet_v/Rendu/semester4/PSU/PSU_2015_zappy/src_server/Trantorien_Event
** 
** Made by Victor Gouet
** Login   <gouet_v@epitech.net>
** 
** Started on  Wed Jun  8 07:55:56 2016 Victor Gouet
** Last update Fri Jun 10 18:25:34 2016 Victor Gouet
*/

#include "../../include_server/trantorien_event.h"

int		connect_nbr_event(t_trantorien *trantorien, t_list *list,
				  t_command_line *command, char **tab)
{
  t_team_name	*team;

  if ((team = get_team(&command->team_list,
		       !trantorien->team ? "" : trantorien->team)))
    {
      sendf_message(&(trantorien->ref->client->sock), "3\n");
    }
  return (0);
}
