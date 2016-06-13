/*
** pose_obj_event.c for POSE OBJ in /home/gouet_v/Rendu/semester4/PSU/PSU_2015_zappy/src_server/Trantorien_Event
**
** Made by Victor Gouet
** Login   <gouet_v@epitech.net>
**
** Started on  Wed Jun  8 07:53:04 2016 Victor Gouet
** Last update Wed Jun  8 11:21:59 2016 Victor Gouet
*/

#include "object.h"

int leaveFood(t_inventories *inventaire, t_inventories *inventaire_ground)
{
    return (leaveObject(&(inventaire->food),
                        &(inventaire_ground->food)));
}

int leaveLinemate(t_inventories *inventaire, t_inventories *inventaire_ground)
{
    return (leaveObject(&(inventaire->linemate),
                        &(inventaire_ground->linemate)));
}

int leaveDeraumere(t_inventories *inventaire, t_inventories *inventaire_ground)
{
    return (leaveObject(&(inventaire->deraumere),
                        &(inventaire_ground->deraumere)));
}

int leaveSibure(t_inventories *inventaire, t_inventories *inventaire_ground)
{
    return (leaveObject(&(inventaire->sibur),
                        &(inventaire_ground->sibur)));
}