/*
** event_client.c for EVENT in /home/gouet_v/Rendu/semester4/PSU/PSU_2015_zappy
** 
** Made by Victor Gouet
** Login   <gouet_v@epitech.net>
** 
** Started on  Tue Jun  7 15:49:37 2016 Victor Gouet
** Last update Tue Jun  7 20:15:24 2016 Victor Gouet
*/

#include <stdio.h>
#include "../include_server/server.h"

static int	convert_data_to_command(char *data,
					t_list *list,
					t_ref *ref,
					t_command_line *command)
{
  char	**tab;

  if ((tab = str_to_word_tab(data)) == NULL)
    return (-1);
  if (!tab[0])
    return (delete_command(tab, data), 0);
  if (ref->type == UNKNOWN)
    {
      unknwon_client_event(ref, list, command, tab);
    }
  delete_command(tab, data);
  return (0);
}

static t_ref	*delete_all_in_client(t_list *list,
				      t_command_line *command,
				      t_server *server,
				      t_ref *ref)
{
  remove_client_from_server(server, ref->client);
  if (ref->type == TRANTORIEN)
    {
      remove_client_to_unknown_team(&(command->team_list), ref->ref);
    }
  ref = remove_client_to_list(list, ref);
  return (ref);
}

int	event_client(t_list *list, t_command_line *command,
		     fd_set *fds, t_server *server)
{
  t_ref	*ref;
  char	*data;

  ref = list->begin;
  while (ref)
    {
      if (FD_ISSET(ref->client->sock.sock, fds))
	{
	  if ((data = get_crlf_line(ref->client)) == NULL)
	    {
	      ref = delete_all_in_client(list, command, server, ref);
	      continue;
	    }
	  printf("%s\n", data);
	  convert_data_to_command(data, list, ref, command);
	}
      ref = ref->next;
    }
  return (0);
}
