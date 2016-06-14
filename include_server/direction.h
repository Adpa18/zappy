/*
** trantorien_event.c for TRANTORIEN EVENT in /home/gouet_v/Rendu/semester4/PSU/PSU_2015_zappy
**
** Made by Victor Gouet
** Login   <gouet_v@epitech.net>
**
** Started on  Wed Jun  8 07:56:42 2016 Victor Gouet
** Last update Wed Jun  8 11:20:17 2016 Victor Gouet
*/

#ifndef ZAPPY_DIRECTION_H
# define ZAPPY_DIRECTION_H

# include "server.h"

t_vector2d  getVectorDir(t_orientation orientation);
int         modulo(int nb, int by);
void        move_by_dir(t_trantorien *trantorien, t_command_line *command,
                        t_vector2d dir);

#endif //ZAPPY_DIRECTION_H
