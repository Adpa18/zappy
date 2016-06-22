/*
** broadcast_event.c for BROADCAST in /home/gouet_v/Rendu/semester4/PSU/PSU_2015_zappy/src_server/Trantorien_Event
**
** Made by Victor Gouet
** Login   <gouet_v@epitech.net>
**
** Started on  Wed Jun  8 07:54:05 2016 Victor Gouet
** Last update Wed Jun  8 11:21:13 2016 Victor Gouet
*/

#include "monitor_event.h"

static double      get_fast_pt(int from, int to, int length)
{
    if (from > to && abs(from - to) > abs(length - from + to))
    {
        return (length + to);
    }
    else if (abs(from - to) > abs(length - to + from))
    {
        return (to - length);
    }
    return (to);
}

t_vector2f  get_fast_way(t_vector2d from, t_vector2d to, t_command_line *command)
{
    t_vector2f  pt;

    pt.x = get_fast_pt(from.x, to.x, command->x);
    pt.y = get_fast_pt(from.y, to.y, command->y);
    return (pt);
}
