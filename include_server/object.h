/*
** trantorien_event.c for TRANTORIEN EVENT in /home/gouet_v/Rendu/semester4/PSU/PSU_2015_zappy
**
** Made by Victor Gouet
** Login   <gouet_v@epitech.net>
**
** Started on  Wed Jun  8 07:56:42 2016 Victor Gouet
** Last update Wed Jun  8 11:20:17 2016 Victor Gouet
*/

#ifndef ZAPPY_OBJECT_H
# define ZAPPY_OBJECT_H

#include "server.h"

typedef int (*objectPtr)(t_inventories *inventaire,
                         t_inventories *inventaire_ground);

enum ObjectType {
    NOURRITURE = 0,
    LINEMATE,
    DERAUMERE,
    SIBUR,
    MENDIANE,
    PHIRAS,
    THYSTAME
};

int getObject(const char *object_str);
char    *concat(char *tmp_buffer, const char *add);
char    *get_all_objects(t_inventories **map, t_vector2d pos);
int takeObject(int *object_inventaire, int *object_ground);
int leaveObject(int *object_inventaire, int *object_ground);

int takeFood(t_inventories *inventaire, t_inventories *inventaire_ground);
int takeLinemate(t_inventories *inventaire, t_inventories *inventaire_ground);
int takeDeraumere(t_inventories *inventaire, t_inventories *inventaire_ground);
int takeSibure(t_inventories *inventaire, t_inventories *inventaire_ground);
int takeMediane(t_inventories *inventaire, t_inventories *inventaire_ground);
int takePhiras(t_inventories *inventaire, t_inventories *inventaire_ground);
int takeThystame(t_inventories *inventaire, t_inventories *inventaire_ground);

int leaveFood(t_inventories *inventaire, t_inventories *inventaire_ground);
int leaveLinemate(t_inventories *inventaire, t_inventories *inventaire_ground);
int leaveDeraumere(t_inventories *inventaire, t_inventories *inventaire_ground);
int leaveSibure(t_inventories *inventaire, t_inventories *inventaire_ground);
int leaveMediane(t_inventories *inventaire, t_inventories *inventaire_ground);
int leavePhiras(t_inventories *inventaire, t_inventories *inventaire_ground);
int leaveThystame(t_inventories *inventaire, t_inventories *inventaire_ground);

#endif //ZAPPY_OBJECT_H
