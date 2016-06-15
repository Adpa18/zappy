/*
** expulse_event.c for EXPULSE in /home/gouet_v/Rendu/semester4/PSU/PSU_2015_zappy/src_server/Trantorien_Event
** 
** Made by Victor Gouet
** Login   <gouet_v@epitech.net>
** 
** Started on  Wed Jun  8 07:53:39 2016 Victor Gouet
** Last update Tue Jun 14 17:10:56 2016 Victor Gouet
*/

#include "../../include_server/trantorien_event.h"
#include "direction.h"
#include "../../include_server/monitor_event.h"

int     expulse_event(t_trantorien *trantorien, t_list *list,
                      t_command_line *command, char **tab)
{
    t_trantorien  *drone;
    t_ref   *ref;
    t_orientation   inv_dir;

    inv_dir = trantorien->orientation + 2;
    if (inv_dir > 4)
        inv_dir %= 4;
    drone = NULL;
    ref = list->begin;
    pex_event(trantorien, list);
    while (ref)
    {
        if (ref->type == TRANTORIEN && (drone = ref->ref)
            && drone->id != trantorien->id && drone->pos.x == trantorien->pos.x
            && drone->pos.y == trantorien->pos.y)
        {
            move_by_dir(drone, command, getVectorDir(trantorien->orientation));
            sendf_message(&(drone->ref->client->sock), "deplacement: %c\n",
                          (char)(inv_dir + 48));
            ppo_event_to_all_monitor(drone, list);
        }
        ref = ref->next;
    }
    sendf_message(&(trantorien->ref->client->sock), "%s\n", drone ? "ok" : "ko");
    return ((void)tab, 0);
}
