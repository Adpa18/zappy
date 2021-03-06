/*
** add_client_to_team.c for TEAM in /home/gouet_v/Rendu/semester4/PSU/PSU_2015_zappy
** 
** Made by Victor Gouet
** Login   <gouet_v@epitech.net>
** 
** Started on  Tue Jun  7 17:35:38 2016 Victor Gouet
** Last update Fri Jun 10 17:59:45 2016 Victor Gouet
*/

#include <string.h>
#include "../include_server/server.h"

int	add_client_to_team(t_team_name *team, t_trantorien *trantorien)
{
  trantorien->next_on_team = NULL;
  if ((trantorien->team = strdup(!team->name ? "" : team->name)) == NULL)
    return (-1);
  ++(team->nbr_client);
  if (team->begin == NULL && team->end == NULL)
    {
      team->begin = trantorien;
    }
  else
    {
      ((t_trantorien *)team->end)->next_on_team = (void *)trantorien;
    }
  team->end = trantorien;
  return (0);
}
