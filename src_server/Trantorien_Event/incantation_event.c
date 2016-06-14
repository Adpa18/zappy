/*
** incantation_event.c for INCANTATION in /home/gouet_v/Rendu/semester4/PSU/PSU_2015_zappy/src_server/Trantorien_Event
** 
** Made by Victor Gouet
** Login   <gouet_v@epitech.net>
** 
** Started on  Wed Jun  8 07:54:59 2016 Victor Gouet
** Last update Tue Jun 14 18:37:19 2016 Victor Gouet
*/

#include <stdbool.h>
#include "player.h"
#include "incantation.h"
#include "../../include_server/trantorien_event.h"
#include "../../include_server/monitor_event.h"

static const incantationPtr incantationFunc[] = {
        incantation_one, incantation_two, incantation_three, incantation_four,
        incantation_five, incantation_six, incantation_seven
};

bool     incantation_six(t_trantorien *trantorien, t_list *list, bool end)
{
    if (count_players_by_pos(list, trantorien) >= 6
        && trantorien->inventaire.linemate >= 1
        && trantorien->inventaire.deraumere >= 2
        && trantorien->inventaire.sibur >= 3
        && trantorien->inventaire.phiras >= 1)
    {
        if (end)
        {
            trantorien->inventaire.linemate -= 1;
            trantorien->inventaire.deraumere -= 2;
            trantorien->inventaire.sibur -= 3;
            trantorien->inventaire.phiras -= 1;
        }
        return (true);
    }
    return (false);
}

bool     incantation_seven(t_trantorien *trantorien, t_list *list, bool end)
{
    if (count_players_by_pos(list, trantorien) >= 6
        && trantorien->inventaire.linemate >= 2
        && trantorien->inventaire.deraumere >= 2
        && trantorien->inventaire.sibur >= 2
        && trantorien->inventaire.mendiane >= 2
        && trantorien->inventaire.phiras >= 2
        && trantorien->inventaire.thystame >= 1)
    {
        if (end)
        {
            trantorien->inventaire.linemate -= 2;
            trantorien->inventaire.deraumere -= 2;
            trantorien->inventaire.sibur -= 2;
            trantorien->inventaire.mendiane -= 2;
            trantorien->inventaire.phiras -= 2;
            trantorien->inventaire.thystame -= 1;
        }
        return (true);
    }
    return (false);
}

bool    can_elevate(t_trantorien *trantorien, t_list *list)
{
    return (incantationFunc[trantorien->elevation - 1]
            (trantorien, list, false));
}

int     incantation_event(t_trantorien *trantorien, t_list *list,
			  t_command_line *command, char **tab)
{
  (void)command;
  (void)tab;
  if (incantationFunc[trantorien->elevation - 1]
      (trantorien, list, true))
    {
      pie_event(trantorien, list, 1);
      plv_event_all_monitor(list);
    }
  else
    {
      pie_event(trantorien, list, 1);
      plv_event_all_monitor(list);
    }
}
