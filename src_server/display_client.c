/*
** display_client.c for DISPLAY in /home/gouet_v/Rendu/semester4/PSU/PSU_2015_zappy
** 
** Made by Victor Gouet
** Login   <gouet_v@epitech.net>
** 
** Started on  Tue Jun  7 15:09:09 2016 Victor Gouet
** Last update Tue Jun  7 18:58:27 2016 Victor Gouet
*/

#include <stdio.h>
#include "../include_server/server.h"

static void	display_monitor(t_monitor *monitor)
{
  printf("-- monitor --\n");
  printf("data: %d\n", monitor->data);
  printf("--END--\n");
}

static void	display_trantorien(t_trantorien *trantorien)
{
  printf("-- trantorien --\n");
  printf("koala: %f\n", trantorien->koala);
  printf("--END--\n");
}

static void	display_unknown(t_ref *unknwon)
{
  printf("-- unknwon --\n");
  printf("%p\n", unknwon);
  printf("socket: %d\n", unknwon->client->sock.sock);
  printf("ip: %s\n", unknwon->client->ip);
  printf("--END--\n");
}

void	display_client_in_list(t_list *list)
{
  t_ref	*elem;

  printf("\n\n --- begin ---\n");
  printf("max fd: %d\n", list->max_fd);
  printf("nbr_client: %d\n", list->nbr_client);
  elem = list->begin;
  while (elem)
    {
      if (elem->type == TRANTORIEN && elem->ref)
	{
	  display_trantorien(elem->ref);
	}
      else if (elem->type == MONITOR && elem->ref)
	{
	  display_monitor(elem->ref);
	}
      else
	{
	  display_unknown(elem);
	}
      elem = elem->next;
    }
  printf("--- end ---\n");
}

void		display_team(t_team_list *list)
{
  t_team_name	*elem;
  t_trantorien	*ref;

  printf("DISPLAY TEAM\n");
  elem = list->begin;
  while (elem)
    {
      ref = elem->begin;
      printf("team: %s\n", elem->name);
      while (ref)
	{
	  display_trantorien(ref);
	  ref = ref->next_on_team;
	}
      elem = elem->next;
    }
}
