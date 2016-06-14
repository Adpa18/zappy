/*
** add_client_to_list.c for CLIENT in /home/gouet_v/Rendu/semester4/PSU/PSU_2015_zappy
**
** Made by Victor Gouet
** Login   <gouet_v@epitech.net>
**
** Started on  Tue Jun  7 14:52:48 2016 Victor Gouet
** Last update Fri Jun 10 16:00:53 2016 Victor Gouet
*/

#include "direction.h"

static t_vector2d vectorDir[5] = {
        {0, 0}, {1, 0}, {0, -1}, {-1, 0}, {0, 1}
};

t_vector2d  getVectorDir(t_orientation orientation)
{
    if (orientation >= N && orientation <= O)
        return (vectorDir[orientation]);
    return (vectorDir[0]);
}