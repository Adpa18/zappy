/*
** add_client_to_list.c for CLIENT in /home/gouet_v/Rendu/semester4/PSU/PSU_2015_zappy
**
** Made by Victor Gouet
** Login   <gouet_v@epitech.net>
**
** Started on  Tue Jun  7 14:52:48 2016 Victor Gouet
** Last update Fri Jun 10 16:00:53 2016 Victor Gouet
*/

#include "player.h"

int     count_players(t_list *list)
{
    t_ref   *ref;
    int     nb;

    nb = 0;
    ref = list->begin;
    while (ref)
    {
        if (ref->type == TRANTORIEN)
            ++nb;
        ref = ref->next;
    }
    return (nb);
}

int     count_players_by_pos(t_list *list, t_trantorien *trantorien)
{
    t_trantorien    *drone;
    t_ref   *ref;
    int     nb;

    nb = 0;
    ref = list->begin;
    while (ref)
    {
        drone = ref->ref;
        if (ref->type == TRANTORIEN
            && drone->pos.x == trantorien->pos.x
            && drone->pos.y == trantorien->pos.y
                && drone->elevation == trantorien->elevation)
            ++nb;
        ref = ref->next;
    }
    return (nb);
}