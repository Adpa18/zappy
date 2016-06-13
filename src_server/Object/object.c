/*
** prend_obj_event.c for PREND OBJ in /home/gouet_v/Rendu/semester4/PSU/PSU_2015_zappy/src_server/Trantorien_Event
**
** Made by Victor Gouet
** Login   <gouet_v@epitech.net>
**
** Started on  Wed Jun  8 07:52:46 2016 Victor Gouet
** Last update Wed Jun  8 11:22:03 2016 Victor Gouet
*/

#include <string.h>
#include "object.h"

static const char *objectsStr[7] = {
        "nourriture", "linemate", "deraumere", "sibur",
        "mendiane", "phiras", "thystame"
};

int leaveObject(int *object_inventaire, int *object_ground)
{
    if (*object_inventaire > 0)
    {
        ++(*object_ground);
        --(*object_inventaire);
        return (0);
    }
    return (1);
}

int takeObject(int *object_inventaire, int *object_ground)
{
    if (*object_ground > 0)
    {
        --(*object_ground);
        ++(*object_inventaire);
        return (0);
    }
    return (1);
}

int     getObject(const char *object_str)
{
    if (!object_str)
        return (-1);
    for (unsigned int i = 0; i < sizeof(objectsStr) / sizeof(char *); ++i)
    {
        if (strcasecmp(object_str, objectsStr[i]) == 0)
            return (i);
    }
    return (-1);
}