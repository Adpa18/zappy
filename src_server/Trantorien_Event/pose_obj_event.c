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
#include "../../include_server/trantorien_event.h"

static const objectPtr leaveObjectFunc[] = {
        leaveFood, leaveLinemate, leaveDeraumere, leaveSibure,
        leaveMediane, leavePhiras, leaveThystame
};

int     pose_obj_event(t_trantorien *trantorien, t_list *list,
		       t_command_line *command, char **tab)
{
    int     ret;
    int     object_type;

    ret = 1;
    if ((object_type = getObject(tab[1])) != -1)
        ret = leaveObjectFunc[object_type](&(trantorien->inventaire),
                                           &(list->map->map[trantorien->pos.y]
                                           [trantorien->pos.x]));
    if (ret == 0)
        send_message("ok\n", &(trantorien->ref->client->sock));
    else
        send_message("ko\n", &(trantorien->ref->client->sock));
    (void)command;
    return (ret);
}
