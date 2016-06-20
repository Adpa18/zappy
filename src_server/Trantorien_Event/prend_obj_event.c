/*
** prend_obj_event.c for PREND OBJ in /home/gouet_v/Rendu/semester4/PSU/PSU_2015_zappy/src_server/Trantorien_Event
** 
** Made by Victor Gouet
** Login   <gouet_v@epitech.net>
** 
** Started on  Wed Jun  8 07:52:46 2016 Victor Gouet
** Last update Tue Jun 14 16:56:47 2016 Victor Gouet
*/

#include "object.h"
#include "../../include_server/trantorien_event.h"
#include "../../include_server/monitor_event.h"

static const objectPtr takeObjectFunc[] = {
        takeFood, takeLinemate, takeDeraumere, takeSibure,
        takeMediane, takePhiras, takeThystame
};

int     prend_obj_event(t_trantorien *trantorien, t_list *list,
			t_command_line *command, char **tab)
{
    int     ret;
    int     object_type;

    ret = 1;
    if ((object_type = getObject(tab[1])) != -1)
        ret = takeObjectFunc[object_type](&(trantorien->inventaire),
                                          &(list->map->map[trantorien->pos.y]
                                          [trantorien->pos.x]));
    if (ret == 0)
      {
        send_message("ok\n", &(trantorien->ref->client->sock));
	pgt_event(trantorien, list, object_type);
	pin_event_to_all_monitor(list, trantorien);
	bct_event_to_all_monitor(list, trantorien->pos.x, trantorien->pos.y);
      }
    else
        send_message("ko\n", &(trantorien->ref->client->sock));
    (void)command;
  return (ret);
}