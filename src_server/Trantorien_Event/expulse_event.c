/*
** expulse_event.c for EXPULSE in /home/gouet_v/Rendu/semester4/PSU/PSU_2015_zappy/src_server/Trantorien_Event
** 
** Made by Victor Gouet
** Login   <gouet_v@epitech.net>
** 
** Started on  Wed Jun  8 07:53:39 2016 Victor Gouet
** Last update Wed Jun  8 11:21:30 2016 Victor Gouet
*/

#include "../../include_server/trantorien_event.h"
#include "direction.h"

int     expulse_event(t_trantorien *trantorien, t_list *list,
		      t_command_line *command, char **tab)
{
    t_trantorien  *drone;
    t_ref   *ref;
    t_vector2d  dir;

    drone = NULL;
    dir = getVectorDir(trantorien->orientation);
    ref = list->begin;
    while (ref)
    {
        if (ref->type == TRANTORIEN)
        {
            drone = ref->ref;
            move_by_dir(drone, command, dir);
            sendf_message(&(drone->ref->client->sock), "deplacement: %c\n",
                          modulo(trantorien->orientation + 2, 4));
        }
        ref = ref->next;
    }
    if (drone)
        send_message("ok\n", &(trantorien->ref->client->sock));
    else
        send_message("ko\n", &(trantorien->ref->client->sock));
    (void)list;
    (void)tab;
  return (0);
}
