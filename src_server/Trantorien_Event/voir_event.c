/*
** voir_event.c for VOIR in /home/gouet_v/Rendu/semester4/PSU/PSU_2015_zappy/src_server/Trantorien_Event
** 
** Made by Victor Gouet
** Login   <gouet_v@epitech.net>
** 
** Started on  Wed Jun  8 07:52:03 2016 Victor Gouet
** Last update Wed Jun  8 11:22:08 2016 Victor Gouet
*/

#include "../../include_server/trantorien_event.h"
#include "direction.h"
#include <stdio.h>
#include "storage.h"

static const char	*objectsStr[7] = {
        "nourriture", "linemate", "deraumere", "sibur",
        "mendiane", "phiras", "thystame"
};

int     modulo(int nb, int by)
{
    if (nb < 0)
        return (by - 1);
    return (nb % by);
}

char    *get_all_objects(t_inventories **map, t_vector2d pos)
{
    int     i;
    int     j;
    char    *buffer;
    char    *tmp_buffer;
    void    *object;

    buffer = "";
    object = &map[pos.y][pos.x];
    printf("pos = [%d][%d]\n", pos.y, pos.x);
    i = 0;
    while (++i < 7)
    {
        tmp_buffer = buffer;
        printf("\t%d => %d\n", i, *(int*)object);
        for (j = 0; j < *(int*)object; ++j)
        {
            buffer = STRING("%s %s", tmp_buffer, objectsStr[i]);
        }
        object += sizeof(int);
    }
    printf("buffer = %s\n", buffer);
    return (buffer);
}

int     voir_event(t_trantorien *trantorien, t_list *list,
                   t_command_line *command, char **tab)
{
    int     i;
    int     j;
    char    *buffer;
    char    *tmp;
    char    *tmp_buffer;
    t_vector2d  dir;
    t_vector2d  pos;
    t_vector2d  cur_pos;

    buffer = "";
    pos = trantorien->pos;
    dir = getVectorDir(trantorien->orientation);
    for (i = 1; i <= trantorien->elevation; ++i)
    {
        pos.x += dir.x;
        pos.y += dir.y;
        for (j = -i; j <= i; ++j)
        {
            cur_pos = pos;
            cur_pos.x = modulo(cur_pos.x + (dir.x == 0) ? j : 0, command->x);
            cur_pos.y = modulo(cur_pos.y + (dir.y == 0) ? j : 0, command->y);
            tmp = get_all_objects(list->map->map, cur_pos);
            tmp_buffer = buffer;
            buffer = STRING("%s,%s", tmp_buffer, tmp);
            free(tmp_buffer);
            free(tmp);
        }
    }
    sendf_message(&(trantorien->ref->client->sock), "{%s}", buffer);
    (void)list;
    (void)tab;
    return (0);
}
