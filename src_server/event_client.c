/*
** event_client.c for EVENT in /home/gouet_v/Rendu/semester4/PSU/PSU_2015_zappy
** 
** Made by Victor Gouet
** Login   <gouet_v@epitech.net>
** 
** Started on  Tue Jun  7 15:49:37 2016 Victor Gouet
** Last update Fri Jun 24 15:26:17 2016 Victor Gouet
*/

#include <string.h>
#include <stdio.h>
#include "../include_server/server.h"
#include "../include_server/trantorien_event.h"
#include "../include_server/time_gestion.h"
#include "../include_server/monitor_event.h"
#include "../include_server/incantation.h"

static const t_event		event_player[2] = {
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
    {"bct",
     "sst",
     "time",
     NULL,
     NULL,
     "msz",
     NULL,
     NULL,
     NULL,
     NULL,
     NULL,
     NULL,
     NULL,
     NULL,
     "pin",
     "plv",
     NULL,
     "ppo",
     NULL,
     NULL,
     "sgt",
     NULL,
     NULL,
     "tna",
     "mct",
    },
    {
      bct_event,
      sst_event,
      time_event,
      NULL,
      NULL,
      msz_event,
      NULL,
      NULL,
      NULL,
      NULL,
      NULL,
      NULL,
      NULL,
      NULL,
      pin_event,
      plv_event,
      NULL,
      ppo_event,
      NULL,
      NULL,
      sgt_event,
      NULL,
      NULL,
      tna_event,
      mct_event
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
    return (unknwon_client_event(ref, list, command, ref->begin->tab));
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
  if (ref->type == MONITOR)
    suc_event(ref->ref);
  return (0);
}

static int	event_call(t_list *list, t_command_line *command,
			   t_server *server)
{
  t_ref		*ref;

  ref = list->begin;
  while (ref)
    {
      if (ref->buffer_size > 0 && ref->time_ref == 0)
	ref->time_ref = getTimeSeconds();
      if (ref->buffer_size > 0 && ref->begin && ref->begin->first_time)
	command_input_for(ref, list);
      else if (ref->buffer_size > 0
	       && ref->begin
	       && is_time_out_for(ref->begin->tab[0],
				  command->time, ref->time_ref))
	{
	  if (convert_data_to_command(list, ref, command) == -1)
	    {
	      ref = delete_all_in_client(list, command, server, ref);
	      continue;
	    }
	  ref->time_ref = 0;
	  buffer_pop_front(ref);
	}
      ref = ref->next;
    }
  return (0);
}

static int	event_gestion(t_list *list, t_command_line *command,
			      t_server *server)
{
  t_trantorien	*trantorien;

  event_call(list, command, server);
  food_gestion_for_trantorien(list, command, server);
  on_gestion_egg(command, list);
  if ((trantorien = get_trantorien_with_max_elevation(list)))
    {
      if (trantorien->elevation == 8)
	seg_event(trantorien, list);
    }
  return (0);
}

static void	push_to_buffer(t_ref *ref, char *data)
{
  char		**tab;

  if (ref->buffer_size < 10 && data[0])
    {
      tab = str_to_word_tab(data);
      /* if (tab && tab[0] && strcmp("incantation", tab[0]) == 0 */
      /* 	  && ref->type == TRANTORIEN && !can_elevate(ref->ref, list)) */
      /* 	{ */
      /* 	  send_message("ko\n", &(ref->client->sock)); */
      /* 	  return ; */
      /* 	} */
      /* else if (tab && tab[0] && strcmp("incantation", tab[0]) == 0 */
      /* 	       && ref->type == TRANTORIEN && can_elevate(ref->ref, list)) */
      /* 	{ */
      /* 	  send_message("elevation en cours\n", &(ref->client->sock)); */
      /* 	  pic_event(ref->ref, list); */
      /* 	} */
      /* else if (tab && tab[0] && strcmp("fork", tab[0]) == 0) */
      /* 	{ */
      /* 	  pfk_event(ref->ref, list); */
      /* 	} */
      buffer_push_back(ref, data, tab);
    }
}

int	event_client(t_list *list, t_command_line *command,
		     fd_set *fds, t_server *server)
{
  t_ref	*ref;
  char	*data;

  ref = list->begin;
  while (ref)
    {
      ref->client->sock.is_writable = FD_ISSET(ref->client->sock.sock,
					       &(list->fds_wri));
      if (FD_ISSET(ref->client->sock.sock, fds))
	{
	  if ((data = get_crlf_line(ref->client)) == NULL)
	    {
	      ref = remove_client_if_trantorien_change_state(list, command,
							     server, ref);
	      continue;
	    }	  
	  push_to_buffer(ref, data);
	}
      ref = ref->next;
    }
  event_gestion(list, command, server);
  return (0);
}
