/*
** add_client_to_list.c for CLIENT in /home/gouet_v/Rendu/semester4/PSU/PSU_2015_zappy
**
** Made by Victor Gouet
** Login   <gouet_v@epitech.net>
**
** Started on  Tue Jun  7 14:52:48 2016 Victor Gouet
** Last update Wed Jun 15 14:37:27 2016 Victor Gouet
*/

#ifndef ZAPPY_PLAYER_H
# define ZAPPY_PLAYER_H

# include "server.h"

int	count_players(t_list *list);
int     count_players_by_pos_for_elevation(t_list *list,
					   t_trantorien *trantorien);
int	elevate_players_at_pos(t_list *list, int x, int y);
int	send_msg_to_finish_elevation(t_list *list, int x, int y);
int	send_msg_to_begin_elevation(t_list *list, int x, int y);

#endif //ZAPPY_PLAYER_H
