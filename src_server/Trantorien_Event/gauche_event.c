/*
** gauche_event.c for GAUCHE in /home/gouet_v/Rendu/semester4/PSU/PSU_2015_zappy/src_server/Trantorien_Event
** 
** Made by Victor Gouet
** Login   <gouet_v@epitech.net>
** 
** Started on  Wed Jun  8 07:51:49 2016 Victor Gouet
** Last update Wed Jun  8 11:21:45 2016 Victor Gouet
*/

#include "../../include_server/trantorien_event.h"

int     gauche_event(t_trantorien *trantorien, t_list *list,
                     t_command_line *command, char **tab)
{
    if (trantorien->orientation == 1)
        trantorien->orientation = 4;
    else
        --trantorien->orientation;
    send_message("ok\n", &(trantorien->ref->client->sock));
    (void)list;
    (void)command;
    (void)tab;
    return (0);
}
