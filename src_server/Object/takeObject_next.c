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

int takeMediane(t_inventories *inventaire, t_inventories *inventaire_ground)
{
    return (takeObject(&(inventaire->mendiane),
                       &(inventaire_ground->mendiane)));
}

int takePhiras(t_inventories *inventaire, t_inventories *inventaire_ground)
{
    return (takeObject(&(inventaire->phiras),
                       &(inventaire_ground->phiras)));
}

int takeThystame(t_inventories *inventaire, t_inventories *inventaire_ground)
{
    return (takeObject(&(inventaire->thystame),
                       &(inventaire_ground->thystame)));
}