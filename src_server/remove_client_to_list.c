/*
** remove_client_to_list.c for GESTION in /home/gouet_v/Rendu/semester4/PSU/PSU_2015_zappy
** 
** Made by Victor Gouet
** Login   <gouet_v@epitech.net>
** 
** Started on  Tue Jun  7 16:01:02 2016 Victor Gouet
** Last update Sun Jun 26 11:04:19 2016 Victor Gouet
*/

#include "../include_server/server.h"

static void	free_client_on_list(t_ref *ref)
{
  if (ref->type == MONITOR)
    {
      free(ref->ref);
    }
}

t_ref	*remove_client_to_list(t_list *list, t_ref *ref)
{
  t_ref	*elem;

  elem = list->begin;
  if (elem == ref)
    elem = NULL;
  while (elem)
    {
      if (elem->next == ref)
	break;
      elem = elem->next;
    }
  if (elem)
    elem->next = ref->next;
  if (list->begin == ref)
    list->begin = ((t_ref *)list->begin)->next;
  if (list->end == ref)
    list->end = elem;
  --(list->nbr_client);
  free_client_on_list(ref);
  free(ref);
  return (elem != NULL ? elem->next : NULL);
}

t_ref	*delete_all_in_client(t_list *list,
			      t_command_line *command,
			      t_server *server,
			      t_ref *ref)
{
  flush(ref);
  remove_client_from_server(server, ref->client);
  if (ref->type == TRANTORIEN)
    {
      remove_client_to_unknown_team(&(command->team_list), ref->ref);
    }
  ref = remove_client_to_list(list, ref);
  return (ref);
}

t_ref	*remove_client_if_trantorien_change_state(t_list *list,
						  t_command_line *command,
						  t_server *server,
						  t_ref *ref)
{
  t_trantorien	*trantorien;
  t_team_name	*team;

  remove_client_from_server(server, ref->client);
  if (ref->type == TRANTORIEN)
    {
      trantorien = ref->ref;
      trantorien->state = GHOST;
      if ((team = get_team(&command->team_list, trantorien->team)))
	{
	  --(team->nbr_client);
	}
    }
  ref = remove_client_to_list(list, ref);
  return (ref);
}

void    remove_all_list(t_list *list)
{
  t_ref	*ref;

  ref = list->begin;
  while (ref)
    {
      ref = remove_client_to_list(list, ref);
    }
}
