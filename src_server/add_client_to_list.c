/*
** add_client_to_list.c for CLIENT in /home/gouet_v/Rendu/semester4/PSU/PSU_2015_zappy
** 
** Made by Victor Gouet
** Login   <gouet_v@epitech.net>
** 
** Started on  Tue Jun  7 14:52:48 2016 Victor Gouet
** Last update Sun Jun 26 15:17:56 2016 Victor Gouet
*/

#include <stdlib.h>
#include "../include_server/server.h"
#include "../include_server/time_gestion.h"

static int	struct_size[3] = {
  sizeof(t_trantorien) + sizeof(t_ref),
  sizeof(t_monitor) + sizeof(t_ref),
  sizeof(t_ref)
};

void	list_constructor(t_list *list, int fd)
{
  list->begin = NULL;
  list->end = NULL;
  list->max_fd = fd;
  list->nbr_client = 0;
}

void	*add_client_to_list(t_list *list, t_type type,
			    t_client *client)
{
  t_ref	*ref;

  if ((ref = malloc(struct_size[type])) == NULL)
    return (NULL);
  ++(list->nbr_client);
  ref->time_ref = 0;
  ref->ref = NULL;
  ref->next = NULL;
  ref->type = type;
  ref->begin = NULL;
  ref->end = NULL;
  ref->buffer_size = 0;
  ref->client = client;
  reset(&ref->ring);
  if (client->sock.sock > list->max_fd)
    list->max_fd = client->sock.sock;
  if (list->begin == NULL && list->end == NULL)
    list->begin = ref;
  else
      ((t_ref *)list->end)->next = ref;
  list->end = ref;
  return (ref);
}
