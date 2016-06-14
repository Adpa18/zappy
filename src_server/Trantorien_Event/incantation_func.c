/*
** incantation_event.c for INCANTATION in /home/gouet_v/Rendu/semester4/PSU/PSU_2015_zappy/src_server/Trantorien_Event
**
** Made by Victor Gouet
** Login   <gouet_v@epitech.net>
**
** Started on  Wed Jun  8 07:54:59 2016 Victor Gouet
** Last update Wed Jun  8 11:21:50 2016 Victor Gouet
*/

#include "player.h"

bool     incantation_one(t_trantorien *trantorien, t_list *list, bool end)
{
    if (count_players_by_pos(list, trantorien) >= 1
        && trantorien->inventaire.linemate >= 1)
    {
        if (end)
        {
            --trantorien->inventaire.linemate;
        }
        return (true);
    }
    return (false);
}

bool     incantation_two(t_trantorien *trantorien, t_list *list, bool end)
{
    if (count_players_by_pos(list, trantorien) >= 2
        && trantorien->inventaire.linemate >= 1
        && trantorien->inventaire.deraumere >= 1
        && trantorien->inventaire.sibur >= 1)
    {
        if (end)
        {
            trantorien->inventaire.linemate -= 1;
            trantorien->inventaire.deraumere -= 1;
            trantorien->inventaire.sibur -= 1;
        }
        return (true);
    }
    return (false);
}

bool     incantation_three(t_trantorien *trantorien, t_list *list, bool end)
{
    if (count_players_by_pos(list, trantorien) >= 2
        && trantorien->inventaire.linemate >= 2
        && trantorien->inventaire.sibur >= 1
        && trantorien->inventaire.phiras >= 2)
    {
        if (end)
        {
            trantorien->inventaire.linemate -= 2;
            trantorien->inventaire.sibur -= 1;
            trantorien->inventaire.phiras -= 2;
        }
        return (true);
    }
    return (false);
}

bool     incantation_four(t_trantorien *trantorien, t_list *list, bool end)
{
    if (count_players_by_pos(list, trantorien) >= 4
        && trantorien->inventaire.linemate >= 1
        && trantorien->inventaire.deraumere >= 1
        && trantorien->inventaire.sibur >= 2
        && trantorien->inventaire.phiras >= 1)
    {
        if (end)
        {
            trantorien->inventaire.linemate -= 1;
            trantorien->inventaire.deraumere -= 1;
            trantorien->inventaire.sibur -= 2;
            trantorien->inventaire.phiras -= 1;
        }
        return (true);
    }
    return (false);
}

bool     incantation_five(t_trantorien *trantorien, t_list *list, bool end)
{
    if (count_players_by_pos(list, trantorien) >= 4
        && trantorien->inventaire.linemate >= 1
        && trantorien->inventaire.deraumere >= 2
        && trantorien->inventaire.sibur >= 1
        && trantorien->inventaire.mendiane >= 3)
    {
        if (end)
        {
            trantorien->inventaire.linemate -= 1;
            trantorien->inventaire.deraumere -= 2;
            trantorien->inventaire.sibur -= 1;
            trantorien->inventaire.mendiane -= 3;
        }
        return (true);
    }
    return (false);
}