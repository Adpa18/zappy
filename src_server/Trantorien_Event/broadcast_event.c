/*
** broadcast_event.c for BROADCAST in /home/gouet_v/Rendu/semester4/PSU/PSU_2015_zappy/src_server/Trantorien_Event
** 
** Made by Victor Gouet
** Login   <gouet_v@epitech.net>
** 
** Started on  Wed Jun  8 07:54:05 2016 Victor Gouet
** Last update Wed Jun  8 11:21:13 2016 Victor Gouet
*/

#include <math.h>
#include "monitor_event.h"
#include "direction.h"
#include "../../include_server/trantorien_event.h"

t_vector2f  get_closest_point(t_vector2f from, t_vector2f x1, t_vector2f x2)
{
    t_vector2f  dir_x1;
    t_vector2f  dir_x2;

    dir_x1.x = from.x - x1.x;
    dir_x1.y = from.y - x1.y;
    dir_x2.x = from.x - x2.x;
    dir_x2.y = from.y - x2.y;

    if (sqrt(dir_x1.x * dir_x1.x + dir_x1.y * dir_x1.y) <
            sqrt(dir_x2.x * dir_x2.x + dir_x2.y * dir_x2.y))
        return (x1);
    return (x2);
}

t_vector2d  get_case(t_vector2f from, t_vector2f to)
{
    double  m;
    double  b;
    double  a[4];
    t_vector2f  x1;
    t_vector2f  x2;
    t_vector2f  xy;
    t_vector2d  xy_d;

    m = (from.y - to.y) / (from.x - to.x);
    b = from.y - m * from.x;
    a[0] = 1 + m * m;
    a[1] = -2.0 * to.x + 2.0 * b * m - 2.0 * m * to.y;
    a[2] = to.x * to.x - 2.0 * b * to.y + b * b + to.y * to.y - 1.0;
    a[3] = a[1] * a[1] - 4.0 * a[0] * a[2];
    x1.x = (-a[1] - sqrt(a[3])) / (2.0 * a[0]);
    x2.x = (-a[1] + sqrt(a[3])) / (2.0 * a[0]);
    x1.y = m * x1.x + b;
    x2.y = m * x2.x + b;
    xy = get_closest_point(from, x1, x2);
    xy_d.x = (int)round(xy.x);
    xy_d.y = (int)round(xy.y);
    return (xy_d);
}

t_vector2f  vec_int_to_double(t_vector2d vec_d)
{
    t_vector2f  vec_f;

    vec_f.x = vec_d.x;
    vec_f.y = vec_d.y;
    return (vec_f);
}

int broadcast(t_trantorien *trantorien, t_vector2d from, t_vector2d to,
              t_command_line *command)
{
    t_vector2d  xy;
    t_vector2d  dir;
    t_vector2d  pos;
    int         i;
    static const t_vector2d dir_pos[8] = {
            {0, 1}, {1, 1}, {1, 0}, {1, -1},
            {0, -1}, {-1, -1}, {-1, 0}, {-1, 1}
    };

    if (from.x == to.x && from.y == to.y)
        return (0);
    xy = get_case(vec_int_to_double(from), vec_int_to_double(to));
    dir = getVectorDir(trantorien->orientation);
    dir.x = (dir.x == 0) ? 1 : dir.x;
    dir.y = (dir.y == 0) ? 1 : dir.y;
    for (i = 0; i < 8; ++i)
    {
        pos.x = trantorien->pos.x + dir.x * dir_pos[i].y;
        pos.y = trantorien->pos.y + dir.y * dir_pos[i].x;
        pos.x = modulo(pos.x, command->x);
        pos.y = modulo(pos.y, command->y);
        if (xy.x == pos.x && xy.y == pos.y)
            return (++i);
    }
    return (-1);
}

int     broadcast_event(t_trantorien *trantorien, t_list *list,
			t_command_line *command, char **tab)
{
    t_trantorien    *drone;
    char            *text;
    int             case_dir;
    t_ref           *ref;

    if ((text = get_buffer_from_client_without_cammand(trantorien->ref)) == NULL)
        return (1);
    ref = list->begin;
    while (ref)
    {
        if (ref->type == TRANTORIEN && (drone = ref->ref)
            && drone->id != trantorien->id)
        {
            case_dir = broadcast(drone, trantorien->pos, drone->pos, command);
            sendf_message(&(drone->ref->client->sock), "message %d, %s\n",
                          case_dir, text);
        }
        ref = ref->next;
    }
    pbc_event(trantorien, list, text);
    send_message("ok\n", &(trantorien->ref->client->sock));
    (void)tab;
  return (0);
}
