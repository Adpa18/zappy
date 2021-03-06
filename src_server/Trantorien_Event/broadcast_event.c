/*
** broadcast_event.c for BROADCAST in /home/gouet_v/Rendu/semester4/PSU/PSU_2015_zappy/src_server/Trantorien_Event
** 
** Made by Victor Gouet
** Login   <gouet_v@epitech.net>
** 
** Started on  Wed Jun  8 07:54:05 2016 Victor Gouet
** Last update Sat Jun 25 15:53:04 2016 Victor Gouet
*/

#include <math.h>
#include <stdio.h>
#include "monitor_event.h"
#include "direction.h"
#include "../../include_server/trantorien_event.h"

static const t_vector2d dir_pos[4][8] = {
        {
                {0, -1}, {-1, -1}, {-1, 0}, {-1, 1},
                {0, 1}, {1, 1}, {1, 0}, {1, -1}
        },
        {
                {1, 0}, {1, -1}, {0, -1}, {-1, -1},
                {-1, 0}, {-1, 1}, {0, 1}, {1, 1}
        },
        {
                {0, 1}, {1, 1}, {1, 0}, {1, -1},
                {0, -1}, {-1, -1}, {-1, 0}, {-1, 1}
        },
        {
                {-1, 0}, {-1, 1}, {0, 1}, {1, 1},
                {1, 0}, {1, -1}, {0, -1}, {-1, -1}
        }
};

static t_vector2f  get_closest_point(t_vector2f from, t_vector2f x1,
                                     t_vector2f x2)
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

static t_vector2f  calc_case(t_vector2f from, t_vector2f to)
{
    double  mb[2];
    double  a[4];
    t_vector2f  x1;
    t_vector2f  x2;

    mb[0] = (from.y - to.y) / (from.x - to.x);
    mb[1] = from.y - mb[0] * from.x;
    a[0] = 1 + mb[0] * mb[0];
    a[1] = -2.0 * to.x + 2.0 * mb[1] * mb[0] - 2.0 * mb[0] * to.y;
    a[2] = to.x * to.x - 2.0 * mb[1] * to.y + mb[1] * mb[1] + to.y * to.y - 1.0;
    a[3] = a[1] * a[1] - 4.0 * a[0] * a[2];
    x1.x = (-a[1] - sqrt(a[3])) / (2.0 * a[0]);
    x2.x = (-a[1] + sqrt(a[3])) / (2.0 * a[0]);
    x1.y = mb[0] * x1.x + mb[1];
    x2.y = mb[0] * x2.x + mb[1];
    return (get_closest_point(from, x1, x2));
}

static t_vector2d  get_case(t_vector2f from, t_vector2f to,
                            t_command_line *command)
{
  t_vector2f  xy;
  t_vector2d  xy_d;

  xy.x = to.x;
  xy.y = to.y;
  if (from.x == to.x)
    xy.y += (from.y > to.y) ? 1 : -1;
  else if (from.y == to.y)
    xy.x += (from.x > to.x) ? 1 : -1;
  else
    xy = calc_case(from, to);
  xy_d.x = modulo((int)round(xy.x), command->x);
  xy_d.y = modulo((int)round(xy.y), command->y);
  return (xy_d);
}

static int  broadcast(t_trantorien *trantorien, t_vector2d from, t_vector2d to,
		      t_command_line *command)
{
  t_vector2d  xy;
  t_vector2d  dir;
  t_vector2d  pos;
  int         i;

  if (from.x == to.x && from.y == to.y)
    return (0);
  xy = get_case(vec_int_to_double(from), vec_int_to_double(to), command);
  dir = getVectorDir(trantorien->orientation);
  dir.x = (dir.x == 0) ? 1 : dir.x;
  dir.y = (dir.y == 0) ? 1 : dir.y;
  for (i = 0; i < 8; ++i)
    {
      pos.x = trantorien->pos.x + dir_pos[trantorien->orientation - 1][i].x;
      pos.y = trantorien->pos.y + dir_pos[trantorien->orientation - 1][i].y;
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
	  fbufferise(drone->ref, "message %d, %s\n",
		     case_dir, text);
        }
      ref = ref->next;
    }
  pbc_event(trantorien, list, text);
  bufferise(trantorien->ref, "ok\n");
  (void)tab;
  return (0);
}
