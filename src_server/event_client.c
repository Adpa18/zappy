/*
** event_client.c for EVENT in /home/gouet_v/Rendu/semester4/PSU/PSU_2015_zappy
** 
** Made by Victor Gouet
** Login   <gouet_v@epitech.net>
** 
** Started on  Tue Jun  7 15:49:37 2016 Victor Gouet
** Last update Fri Jun 10 17:24:59 2016 Victor Gouet
*/

#include <string.h>
#include <stdio.h>
#include "../include_server/server.h"
#include "../include_server/trantorien_event.h"
#include "../include_server/time_gestion.h"

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

static int	convert_data_to_command(t_list *list,
					t_ref *ref,
					t_command_line *command)
{
  int		idx;

  idx = -1;
  if (!ref->begin || !ref->begin->tab || !ref->begin->tab[0])
    return (0);
  if (ref->type == UNKNOWN)
    unknwon_client_event(ref, list, command, ref->begin->tab);
  else
    while (++idx < EVENTSIZE)
      {
	if (event_player[ref->type].event_name[idx]
	    && event_player[ref->type].callBack[idx]
	    && strcmp(event_player[ref->type].event_name[idx],
		      ref->begin->tab[0]) == 0)
	  return (event_player[ref->type].callBack[idx](ref->ref, list,
							command,
							ref->begin->tab));
      }
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

static int	event_call(t_list *list, t_command_line *command,
			   t_server *server)
{
  t_ref		*ref;

  ref = list->begin;
  while (ref)
    {
      // TODO set timeout of cmd and execute when timeout <= 0
      /* display_buffer_from_client(ref); */
      if (ref->buffer_size > 0 && ref->time_ref == 0)
	{
	  ref->time_ref = getTimeSeconds();
	}
      if (ref->buffer_size > 0
	  && ref->begin
	  && is_time_out_for(ref->begin->tab[0], command->time, ref->time_ref))
	{
	  convert_data_to_command(list, ref, command);
	  ref->time_ref = 0;
	  buffer_pop_front(ref);
	}
      ref = ref->next;
    }
  return (0);
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
	  if (ref->buffer_size < 10 && data[0])
	    buffer_push_back(ref, data, str_to_word_tab(data));
	}
      ref = ref->next;
    }
  event_call(list, command, server);
  return (0);
}
