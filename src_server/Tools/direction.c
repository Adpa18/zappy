/*
** add_client_to_list.c for CLIENT in /home/gouet_v/Rendu/semester4/PSU/PSU_2015_zappy
**
** Made by Victor Gouet
** Login   <gouet_v@epitech.net>
**
** Started on  Tue Jun  7 14:52:48 2016 Victor Gouet
** Last update Wed Jun 15 11:16:31 2016 Victor Gouet
*/

#include "direction.h"

static t_vector2d vectorDir[5] = {
        {0, 0}, {0, -1}, {1, 0}, {0, 1}, {-1, 0}
};

t_vector2d  getVectorDir(t_orientation orientation)
{
    if (orientation >= N && orientation <= O)
        return (vectorDir[orientation]);
    return (vectorDir[0]);
}

inline int     modulo(int nb, int by)
{
    if (nb < 0)
        return (by - 1);
    return (nb % by);
}

void    move_by_dir(t_trantorien *trantorien, t_command_line *command,
                    t_vector2d dir)
{
    trantorien->pos.x += dir.x;
    trantorien->pos.y += dir.y;
    trantorien->pos.x = modulo(trantorien->pos.x, command->x);
    trantorien->pos.y = modulo(trantorien->pos.y, command->y);
}

t_vector2d   calc_pos(t_vector2d pos, t_vector2d dir, int j,
                             t_command_line *cmd)
{
    t_vector2d  cur_pos;

    if (dir.y == 1 || dir.x == -1)
    {
        cur_pos.x = modulo(pos.x - ((dir.y == 0) ? 0 : j), cmd->x);
        cur_pos.y = modulo(pos.y - ((dir.x == 0) ? 0 : j), cmd->y);
    }
    else
    {
        cur_pos.x = modulo(pos.x + ((dir.y == 0) ? 0 : j), cmd->x);
        cur_pos.y = modulo(pos.y + ((dir.x == 0) ? 0 : j), cmd->y);
    }
    return (cur_pos);
}
