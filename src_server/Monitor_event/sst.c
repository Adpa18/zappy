/*
** sst.c for SST in /home/gouet_v/Rendu/semester4/PSU/PSU_2015_zappy
** 
** Made by Victor Gouet
** Login   <gouet_v@epitech.net>
** 
** Started on  Mon Jun 13 21:16:27 2016 Victor Gouet
** Last update Mon Jun 13 21:21:18 2016 Victor Gouet
*/

#include "../../stringLib/storage.h"
#include "../../include_server/monitor_event.h"

int     sst_event(t_monitor *monitor, t_list *list,
		  t_command_line *command, char **tab)
{
  if (!tab[1])
    return (sbp_event(monitor, list, command, tab));
  command->time = atoi(tab[1]);
  sgt_event(monitor, list, command, tab);
  return (0);
}
