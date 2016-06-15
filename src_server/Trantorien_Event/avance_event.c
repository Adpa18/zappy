/*
** avance_event.c for AVANCE in /home/gouet_v/Rendu/semester4/PSU/PSU_2015_zappy/src_server/Trantorien_Event
** 
** Made by Victor Gouet
** Login   <gouet_v@epitech.net>
** 
** Started on  Wed Jun  8 07:49:13 2016 Victor Gouet
** Last update Wed Jun 15 10:53:51 2016 Victor Gouet
*/

#include "../../include_server/trantorien_event.h"
#include "../../include_server/monitor_event.h"
#include "direction.h"

int	avance_event(t_trantorien *trantorien, t_list *list,
                    t_command_line *command, char **tab)
{
  printf("trantorien avance: %d\n", trantorien->id);
  printf("prev:\nx:%d\ny:%d\n, orientation:%d\n",
	 trantorien->pos.x, trantorien->pos.y, trantorien->orientation);
    move_by_dir(trantorien, command, getVectorDir(trantorien->orientation));
    send_message("ok\n", &(trantorien->ref->client->sock));
    ppo_event_to_all_monitor(trantorien, list);
  printf("trantorien avance: %d\n", trantorien->id);
  printf("prev:\nx:%d\ny:%d\n, orientation:%d\n",
	 trantorien->pos.x, trantorien->pos.y, trantorien->orientation);
    (void)list;
    (void)tab;
    return (0);
}
