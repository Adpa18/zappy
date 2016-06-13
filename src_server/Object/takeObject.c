/*
** prend_obj_event.c for PREND OBJ in /home/gouet_v/Rendu/semester4/PSU/PSU_2015_zappy/src_server/Trantorien_Event
**
** Made by Victor Gouet
** Login   <gouet_v@epitech.net>
**
** Started on  Wed Jun  8 07:52:46 2016 Victor Gouet
** Last update Wed Jun  8 11:22:03 2016 Victor Gouet
*/

#include "object.h"

int takeFood(t_inventories *inventaire, t_inventories *inventaire_ground)
{
    return (takeObject(&(inventaire->food),
                       &(inventaire_ground->food)));
}

int takeLinemate(t_inventories *inventaire, t_inventories *inventaire_ground)
{
    return (takeObject(&(inventaire->linemate),
                       &(inventaire_ground->linemate)));
}

int takeDeraumere(t_inventories *inventaire, t_inventories *inventaire_ground)
{
    return (takeObject(&(inventaire->deraumere),
                       &(inventaire_ground->deraumere)));
}

int takeSibure(t_inventories *inventaire, t_inventories *inventaire_ground)
{
    return (takeObject(&(inventaire->sibur),
                       &(inventaire_ground->sibur)));
}