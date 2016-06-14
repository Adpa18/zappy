/*
** convert_client.c for CONVERT in /home/gouet_v/Rendu/semester4/PSU/PSU_2015_zappy
** 
** Made by Victor Gouet
** Login   <gouet_v@epitech.net>
** 
** Started on  Tue Jun  7 18:01:05 2016 Victor Gouet
** Last update Mon Jun 13 22:31:08 2016 Victor Gouet
*/

#include "../include_server/server.h"

void		convert_to_trantorien(t_ref *ref,
				      t_trantorien *trantorien)
{
  trantorien->ref = ref;
  ref->ref = trantorien;
  trantorien->ref->type = TRANTORIEN;
}

t_trantorien	*transform_to_trantorien(t_ref *ref)
{
  t_trantorien	*trantorien;

  if ((trantorien = malloc(sizeof(*trantorien))) == NULL)
    return (NULL);
  convert_to_trantorien(ref, trantorien);
  trantorien->team = NULL;
  return (trantorien);
}

t_monitor	*transform_to_monitor(t_ref *ref)
{
  t_monitor	*monitor;

  if ((monitor = malloc(sizeof(*monitor))) == NULL)
    return (NULL);
  monitor->ref = ref;
  ref->ref = monitor;
  monitor->ref->type = MONITOR;
  return (monitor);
}
