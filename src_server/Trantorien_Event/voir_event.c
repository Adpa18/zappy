/*
** voir_event.c for VOIR in /home/gouet_v/Rendu/semester4/PSU/PSU_2015_zappy/src_server/Trantorien_Event
** 
** Made by Victor Gouet
** Login   <gouet_v@epitech.net>
** 
** Started on  Wed Jun  8 07:52:03 2016 Victor Gouet
** Last update Wed Jun  8 11:22:08 2016 Victor Gouet
*/

#include <string.h>
#include "trantorien_event.h"
#include "direction.h"
#include "storage.h"
#include "object.h"

static const char   *state_str[] = {
        "oeuf", "baby", "ghost", "joueur"
};

char    *get_all_players(t_team_list *team_list, t_vector2d pos, int id)
{
    t_team_name     *team;
    t_trantorien    *drone;
    char            *buffer;

    buffer = NULL;
    team = team_list->begin;
    while (team)
    {
        drone = team->begin;
        while (drone)
        {
            if (drone->id != id && drone->pos.x == pos.x
                && drone->pos.y == pos.y)
            {
                concat(buffer, state_str[drone->state]);
            }
            drone = drone->next_on_team;
        }
        team = team->next;
    }
    return (buffer);
}

static char     *do_voir(t_inventories **map, t_vector2d pos, char *buffer)
{
    char    *tmp;
    char    *ret;

    tmp = get_all_objects(map, pos);
    if (tmp)
    {
        ret = STRING("%s,%s", buffer, tmp);
        free(tmp);
    }
    else
    {
        ret = STRING("%s,", buffer);
    }
    free(buffer);
    return (ret);
}

static char    *init_voir(t_inventories **map, t_vector2d pos)
{
    char    *buffer;
    char    *tmp;

    tmp = get_all_objects(map, pos);
    if (tmp)
        buffer = STRING("{%s", tmp);
    else
        buffer = strdup("{");
    return (buffer);
}

int     voir_event(t_trantorien *trantorien, t_list *list,
                   t_command_line *command, char **tab)
{
    int     i;
    int     j;
    char    *buffer;
    t_vector2d  dir;
    t_vector2d  pos;
    t_vector2d  cur_pos;

    pos = trantorien->pos;
    buffer = init_voir(list->map->map, pos);
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
            buffer = do_voir(list->map->map, cur_pos, buffer);
        }
    }
    // TODO maybe add players
    sendf_message(&(trantorien->ref->client->sock), "%s}\n", buffer);
    (void)tab;
    return (0);
}
