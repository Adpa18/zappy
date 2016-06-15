/*
** mct.c for MCT in /home/gouet_v/Rendu/semester4/PSU/PSU_2015_zappy
** 
** Made by Victor Gouet
** Login   <gouet_v@epitech.net>
** 
** Started on  Mon Jun 13 15:07:34 2016 Victor Gouet
** Last update Wed Jun 15 15:23:01 2016 Victor Gouet
*/

#include <strings.h>
#include "../../include_server/monitor_event.h"
#include "../../stringLib/storage.h"

int	mct_event(t_monitor *monitor, t_list *list,
		  t_command_line *command, char **tab)
{
  int	x;
  char	*data[3];
  int	y;

  y = 0;
  (void)tab;
  while (y < command->y)
    {
      x = 0;
      while (x < command->x)
	{
	  data[0] = NULL;
	  data[1] = STRING("%d", x);
	  data[2] = STRING("%d", y);
	  bct_event(monitor, list, command, data);
	  if (data[1])
	    free(data[1]);
	  if (data[2])
	    free(data[2]);
	  ++x;
	}
      ++y;
    }
  return (0);
}

int	mct_to_all_monitor(t_list *list)
{
  int	x;
  int	y;

  y = 0;
  while (y < list->map->height)
    {
      x = 0;
      while (x < list->map->width)
	{
	  bct_event_to_all_monitor(list, x, y);
	  ++x;
	}
      ++y;
    }
  return (0);
}
