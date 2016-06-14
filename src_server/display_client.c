/*
** display_client.c for DISPLAY in /home/gouet_v/Rendu/semester4/PSU/PSU_2015_zappy
** 
** Made by Victor Gouet
** Login   <gouet_v@epitech.net>
** 
** Started on  Tue Jun  7 15:09:09 2016 Victor Gouet
** Last update Wed Jun  8 11:43:12 2016 Victor Gouet
*/

#include <stdio.h>
#include "../include_server/server.h"

static void	display_monitor(t_monitor *monitor)
{
  printf("\t-- monitor -- {\n");
  printf("\tdata: %d\n", monitor->data);
  printf("\t}\n");
}

static void	display_trantorien(t_trantorien *trantorien)
{
  char		*tab[4];

  tab[0] = "Nord";
  tab[1] = "EST";
  tab[2] = "SUD";
  tab[3] = "OUEST";
  printf("\t-- trantorien -- {\n");
  display_inventories(&(trantorien->inventaire));
  printf("\televation: %d\n", trantorien->elevation);
  printf("\tx: %d y: %d\n", trantorien->pos.x, trantorien->pos.y);
  printf("\torientation: %s\n", tab[trantorien->orientation - 1]);
  printf("\t}\n");
}

static void	display_unknown(t_ref *unknwon)
{
  printf("\tŧ-- unknwon -- {\n");
  printf("\t%p\n", unknwon);
  printf("\tsocket: %d\n", unknwon->client->sock.sock);
  printf("\tip: %s\n", unknwon->client->ip);
  printf("\t}\n");
}

void	display_client_in_list(t_list *list)
{
  t_ref	*elem;

  printf("SERVER INFO {\n");
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
  printf("}\n");
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
      printf("team: %s {\n", elem->name);
      printf("nbr: %d\n", elem->nbr_client);
      while (ref)
	{
	  display_trantorien(ref);
	  ref = ref->next_on_team;
	}
      printf("}\n");
      elem = elem->next;
    }
}
