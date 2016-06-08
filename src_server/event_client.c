/*
** event_client.c for EVENT in /home/gouet_v/Rendu/semester4/PSU/PSU_2015_zappy
** 
** Made by Victor Gouet
** Login   <gouet_v@epitech.net>
** 
** Started on  Tue Jun  7 15:49:37 2016 Victor Gouet
** Last update Wed Jun  8 08:30:48 2016 Victor Gouet
*/

#include <string.h>
#include <stdio.h>
#include "../include_server/server.h"
#include "../include_server/trantorien_event.h"

t_event		event_player[2] = {
  {
    {"avance",
     "droite",
     "gauche",
     "voir",
     "inventaire",
     "prend",
     "pose",
     "expulse",
     "broadcast",
     "incantation",
     "fork",
     "connect_nbr",
     NULL,
     NULL,
     NULL,
     NULL,
     NULL,
     NULL,
     NULL,
     NULL,
     NULL,
     NULL,
     NULL,
     NULL,
     NULL,
    },
    {
      avance_event,
      droite_event,
      gauche_event,
      voir_event,
      inventaire_event,
      prend_obj_event,
      pose_obj_event,
      expulse_event,
      broadcast_event,
      incantation_event,
      fork_event,
      connect_nbr_event,
      NULL,
      NULL,
      NULL,
      NULL,
      NULL,
      NULL,
      NULL,
      NULL,
      NULL,
      NULL,
      NULL,
      NULL,
      NULL
    }
  },
  {
    {"",
     "",
     "",
     "",
     "",
     "",
     "",
     "",
     "",
     "",
     "",
     "",
     "",
     "",
     "",
     "",
     "",
     "",
     "",
     "",
     "",
     "",
     "",
     "",
     "",
    },
    {
      NULL,
      NULL,
      NULL,
      NULL,
      NULL,
      NULL,
      NULL,
      NULL,
      NULL,
      NULL,
      NULL,
      NULL,
      NULL,
      NULL,
      NULL,
      NULL,
      NULL,
      NULL,
      NULL,
      NULL,
      NULL,
      NULL,
      NULL,
      NULL,
      NULL
    }
  }
};

static int	convert_data_to_command(char *data,
					t_list *list,
					t_ref *ref,
					t_command_line *command)
{
  char	**tab;
  int	idx;
  int	ret_value;

  idx = -1;
  if ((tab = str_to_word_tab(data)) == NULL)
    return (-1);
  if (!tab[0])
    return (delete_command(tab, data), 0);
  if (ref->type == UNKNOWN)
    unknwon_client_event(ref, list, command, tab);
  else
    while (++idx < EVENTSIZE)
      {
	if (event_player[ref->type].event_name[idx]
	    && event_player[ref->type].callBack[idx]
	    && strcmp(event_player[ref->type].event_name[idx], tab[0]) == 0)
	  {
	    ret_value = event_player[ref->type].callBack[idx](ref, list,
							     command, tab);
	    delete_command(tab, data);
	    return (ret_value);
	  }
      }
  return (delete_command(tab, data), 0);
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
