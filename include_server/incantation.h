/*
** pose_obj_event.c for POSE OBJ in /home/gouet_v/Rendu/semester4/PSU/PSU_2015_zappy/src_server/Trantorien_Event
**
** Made by Victor Gouet
** Login   <gouet_v@epitech.net>
**
** Started on  Wed Jun  8 07:53:04 2016 Victor Gouet
** Last update Wed Jun  8 11:21:59 2016 Victor Gouet
*/

#ifndef ZAPPY_INCANTATION_H
# define ZAPPY_INCANTATION_H

#include "server.h"

typedef bool (*incantationPtr)(t_trantorien *trantorien, t_list *list, bool end);

bool     incantation_one(t_trantorien *trantorien, t_list *list, bool end);
bool     incantation_two(t_trantorien *trantorien, t_list *list, bool end);
bool     incantation_three(t_trantorien *trantorien, t_list *list, bool end);
bool     incantation_four(t_trantorien *trantorien, t_list *list, bool end);
bool     incantation_five(t_trantorien *trantorien, t_list *list, bool end);
bool     incantation_six(t_trantorien *trantorien, t_list *list, bool end);
bool     incantation_seven(t_trantorien *trantorien, t_list *list, bool end);

#endif //ZAPPY_INCANTATION_H
