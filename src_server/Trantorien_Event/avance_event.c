/*
** avance_event.c for AVANCE in /home/gouet_v/Rendu/semester4/PSU/PSU_2015_zappy/src_server/Trantorien_Event
** 
** Made by Victor Gouet
** Login   <gouet_v@epitech.net>
** 
** Started on  Wed Jun  8 07:49:13 2016 Victor Gouet
** Last update Wed Jun  8 11:49:53 2016 Victor Gouet
*/

#include "../../include_server/trantorien_event.h"

static t_vector2d vectorDir[5] = {
        {0, 0}, {1, 0}, {0, -1}, {-1, 0}, {0, 1}
};

static t_vector2d  getVectorDir(t_orientation orientation)
{
    if (orientation >= N && orientation <= O)
        return (vectorDir[orientation]);
    return (vectorDir[0]);
}

int	avance_event(t_trantorien *trantorien, t_list *list,
                    t_command_line *command, char **tab)
{
    t_vector2d  dir;

    dir = getVectorDir(trantorien->orientation);
    trantorien->pos.x += dir.x;
    trantorien->pos.y += dir.y;
    if (trantorien->pos.x <= 0 || trantorien->pos.x > command->x)
        trantorien->pos.x = 0;
    if (trantorien->pos.y <= 0 || trantorien->pos.y > command->y)
        trantorien->pos.y = 0;
    send_message("ok\n", &(trantorien->ref->client->sock));
    (void)list;
    (void)tab;
    return (0);
}
