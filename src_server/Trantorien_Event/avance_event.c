/*
** avance_event.c for AVANCE in /home/gouet_v/Rendu/semester4/PSU/PSU_2015_zappy/src_server/Trantorien_Event
** 
** Made by Victor Gouet
** Login   <gouet_v@epitech.net>
** 
** Started on  Wed Jun  8 07:49:13 2016 Victor Gouet
** Last update Sat Jun 25 15:52:10 2016 Victor Gouet
*/

#include "../../include_server/trantorien_event.h"
#include "../../include_server/monitor_event.h"
#include "direction.h"

int	avance_event(t_trantorien *trantorien, t_list *list,
                    t_command_line *command, char **tab)
{
  move_by_dir(trantorien, command, getVectorDir(trantorien->orientation));
  bufferise(trantorien->ref, "ok\n");
  ppo_event_to_all_monitor(trantorien, list);
  (void)tab;
  return (0);
}
