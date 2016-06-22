/*
** broadcast_event.c for BROADCAST in /home/gouet_v/Rendu/semester4/PSU/PSU_2015_zappy/src_server/Trantorien_Event
**
** Made by Victor Gouet
** Login   <gouet_v@epitech.net>
**
** Started on  Wed Jun  8 07:54:05 2016 Victor Gouet
** Last update Wed Jun  8 11:21:13 2016 Victor Gouet
*/

#ifndef ZAPPY_BROADCAST_H
# define ZAPPY_BROADCAST_H

# include "monitor_event.h"

t_vector2f  get_fast_way(t_vector2d from, t_vector2d to,
                         t_command_line *command);

#endif //ZAPPY_BROADCAST_H
