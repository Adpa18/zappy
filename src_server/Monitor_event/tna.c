/*
** tna.c for TNA in /home/gouet_v/Rendu/semester4/PSU/PSU_2015_zappy/src_server/Monitor_event
** 
** Made by Victor Gouet
** Login   <gouet_v@epitech.net>
** 
** Started on  Mon Jun 13 13:32:18 2016 Victor Gouet
** Last update Sat Jun 25 10:09:23 2016 Victor Gouet
*/

#include "../../include_server/monitor_event.h"

int		tna_event(t_monitor *monitor, t_list *list,
			  t_command_line *command, char **tab)
{
  t_team_name	*team;

  (void)list;
  (void)tab;
  team = command->team_list.begin;
  while (team)
    {
      /* sendf_message(&(monitor->ref->client->sock), "tna %s\n", team->name); */
      fbufferise(monitor->ref, "tna %s\n", team->name);
      team = team->next;
    }
  return (0);
}
