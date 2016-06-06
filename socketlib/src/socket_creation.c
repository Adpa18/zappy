/*
** my_sock.c for my socket c class implementation in /home/gaspar_q/rendu/semestre4/SystemeUnix/PSU_2015_myftp/include/socketlib
**
** Made by Quentin Gasparotto
** Login   <gaspar_q@epitech.net>
**
** Started on  Mon May  2 11:21:19 2016 Quentin Gasparotto
** Last update Wed May  4 13:58:17 2016 Quentin Gasparotto
*/

#include <unistd.h>
#include <stdio.h>
#include <string.h>

#include "../include/my_sock.h"

t_server	*create_server(const int nbc, const char *protocol,
			       const int domain, const int port)
{
  t_server	*serv;

  if ((serv = create_socket(protocol, domain, 1,
			    sizeof(*serv) + nbc * sizeof(t_client))) == NULL)
    return (NULL);
  serv->nbclient = 0;
  while (serv->nbclient < nbc)
    {
      serv->clients[serv->nbclient] = DEF_CLIENT;
      ++serv->nbclient;
    }
  if (bind_listening_socket((t_socket *)serv, domain, port, nbc) == -1)
    return (NULL);
  return (serv);
}

t_client	*create_client(const char *protocol, const int domain,
			       const char *ip, const int port)
{
  t_client	*this;

  if ((this = create_socket(protocol, domain, 1, sizeof(*this))) == NULL ||
      bind_talking_socket((t_socket *)this, domain, port, ip) == -1 ||
      (this->ip = strdup(ip)) == NULL)
    return (NULL);
  this->len = sizeof(this->sock.sockaddr);
  this->pid = -1;
  return (this);
}
