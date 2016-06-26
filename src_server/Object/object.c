/*
** prend_obj_event.c for PREND OBJ in /home/gouet_v/Rendu/semester4/PSU/PSU_2015_zappy/src_server/Trantorien_Event
**
** Made by Victor Gouet
** Login   <gouet_v@epitech.net>
**
** Started on  Wed Jun  8 07:52:46 2016 Victor Gouet
** Last update Sun Jun 26 13:43:07 2016 Victor Gouet
*/

#include <string.h>
#include "storage.h"
#include "object.h"

static const char	objectsStr[7][20] = {
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

int		getObject(const char *object_str)
{
  unsigned int	i;

    if (!object_str)
        return (-1);
    for (i = 0; i < sizeof(objectsStr) / sizeof(char *); ++i)
    {
        if (strcasecmp(object_str, objectsStr[i]) == 0)
            return (i);
    }
    return (-1);
}

char    *concat_object(char *tmp_buffer, const char *add)
{
    char    *buffer;

    if (!add)
        return (tmp_buffer);
    if (tmp_buffer)
    {
        buffer = STRING("%s %s", tmp_buffer, add);
        free(tmp_buffer);
    }
    else
        buffer = strdup(add);
    return (buffer);
}

char    *get_all_objects(t_inventories **map, t_vector2d pos)
{
    int     i;
    int     j;
    char    *buffer;
    void    *object;

    buffer = NULL;
    object = &map[pos.y][pos.x];
    for (i = 0; i < 7; ++i)
    {
        for (j = 0; j < *(int*)object; ++j)
        {
            buffer = concat_object(buffer, objectsStr[i]);
        }
        object += sizeof(int);
    }
    return (buffer);
}
