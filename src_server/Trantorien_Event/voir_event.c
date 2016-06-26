/*
** voir_event.c for VOIR in /home/gouet_v/Rendu/semester4/PSU/PSU_2015_zappy/src_server/Trantorien_Event
** 
** Made by Victor Gouet
** Login   <gouet_v@epitech.net>
** 
** Started on  Wed Jun  8 07:52:03 2016 Victor Gouet
** Last update Sun Jun 26 13:42:50 2016 Victor Gouet
*/

#include <string.h>
#include "trantorien_event.h"
#include "direction.h"
#include "storage.h"
#include "object.h"

static const char   state_str[4][20] = {
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
                buffer = concat_object(buffer, state_str[drone->state]);
            }
            drone = drone->next_on_team;
        }
        team = team->next;
    }
    return (buffer);
}

char    *get_all(t_inventories **map, t_team_list *team_list,
                 t_vector2d pos, int id)
{
    char    *objects;
    char    *tmp_objects;
    char    *tmp_players;

    tmp_objects = get_all_objects(map, pos);
    tmp_players = get_all_players(team_list, pos, id);
    objects = concat_object(tmp_objects, tmp_players);
    if (tmp_players)
        free(tmp_players);
    return (objects);
}

static char     *do_voir(char *buffer, char *objects)
{
    char    *ret;

    if (objects)
    {
        ret = STRING("%s,%s", buffer, objects);
        free(objects);
    }
    else
    {
        ret = STRING("%s,", buffer);
    }
    free(buffer);
    return (ret);
}

static char    *init_voir(char *objects)
{
    char    *buffer;

    if (objects)
    {
        buffer = STRING("{%s", objects);
        free(objects);
    }
    else
        buffer = strdup("{");
    return (buffer);
}

int     voir_event(t_trantorien *trantorien, t_list *list,
                   t_command_line *cmd, char UNUSED**tab)
{
    int     i;
    int     j;
    char    *buffer;
    t_vector2d  dir;
    t_vector2d  pos;

    pos = trantorien->pos;
    buffer = init_voir(get_all(list->map->map, &(cmd->team_list), pos,
                               trantorien->id));
    dir = getVectorDir(trantorien->orientation);
    for (i = 1; i <= trantorien->elevation; ++i)
    {
        pos.x += dir.x;
        pos.y += dir.y;
        for (j = -i; j <= i; ++j)
        {

            buffer = do_voir(buffer, get_all(list->map->map, &(cmd->team_list),
                                            calc_pos(pos, dir, j, cmd),
                                             trantorien->id));
        }
    }
    fbufferise(trantorien->ref, "%s}\n", buffer);
    return (0);
}
