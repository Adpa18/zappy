/*
** socket_deletion.c for socket deletion functions in /home/gaspar_q/rendu/semestre4/SystemeUnix/PSU_2015_myftp/include
**
** Made by Quentin Gasparotto
** Login   <gaspar_q@epitech.net>
**
** Started on  Mon May  2 17:11:25 2016 Quentin Gasparotto
** Last update Thu May  5 11:37:25 2016 Quentin Gasparotto
*/

#include <stdio.h>
#include "../include/my_sock.h"

int	delete_socket(t_socket *this)
{
  if (this->sock != -1 && close(this->sock) == -1)
    return (perror("delete socket"), -1);
  return (1);
}

int		delete_server(t_server *this)
{
  t_socket	torm;
  int		i;

  torm = *(t_socket *)this;
  i = 0;
  while (i < this->nbclient)
    {
      if (!is_default_client(&this->clients[i]) &&
	  close(this->clients[i].sock.sock) == -1)
	perror("delete server");
      ++i;
    }
  free(this);
  return (delete_socket(&torm));
}

int		delete_client(t_client *this)
{
  t_socket	torm;

  torm = *(t_socket *)this;
  free(this->ip);
  free(this);
  return (delete_socket(&torm));
}

void	remove_client_from_server(t_server *this, t_client *to_remove)
{
  int	i;

  i = 0;
  while (i < this->nbclient)
    {
      if (&this->clients[i] == to_remove)
	{
	  close(this->clients[i].sock.sock);
	  this->clients[i] = DEF_CLIENT;
	  break;
	}
      ++i;
    }
}
