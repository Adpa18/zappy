/*
** add_client_to_list.c for CLIENT in /home/gouet_v/Rendu/semester4/PSU/PSU_2015_zappy
**
** Made by Victor Gouet
** Login   <gouet_v@epitech.net>
**
** Started on  Tue Jun  7 14:52:48 2016 Victor Gouet
** Last update Fri Jun 10 16:00:53 2016 Victor Gouet
*/

#ifndef ZAPPY_PLAYER_H
# define ZAPPY_PLAYER_H

# include "server.h"

int count_players(t_list *list);
int count_players_by_pos(t_list *list, t_trantorien *trantorien);

#endif //ZAPPY_PLAYER_H
