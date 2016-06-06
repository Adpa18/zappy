/*
** connections.c for connections of clients and server functions in /home/gaspar_q/rendu/semestre4/SystemeUnix/PSU_2015_myftp
**
** Made by Quentin Gasparotto
** Login   <gaspar_q@epitech.net>
**
** Started on  Mon May  2 18:29:54 2016 Quentin Gasparotto
** Last update Wed May 18 17:15:04 2016 Quentin Gasparotto
*/

#include <stdio.h>
#include <string.h>
#include <sys/wait.h>
#include "../include/my_sock.h"

bool	is_default_client(const t_client *tocmp)
{
  if (tocmp->sock.sock == DEF_CLIENT.sock.sock &&
      tocmp->pid == DEF_CLIENT.pid &&
      tocmp->len == DEF_CLIENT.len &&
      tocmp->ip == DEF_CLIENT.ip)
    return (true);
  return (false);
}

t_client	*get_client_connection(t_server *this)
{
  int		i;

  i = 0;
  while (i < this->nbclient && !is_default_client(&this->clients[i]))
    ++i;
  if (i == this->nbclient ||
      (this->clients[i].sock.sock = accept(this->socket.sock,
					   (struct sockaddr *)&this->clients[i],
					   &this->clients[i].len)) == -1 ||
      (this->clients[i].ip =
       inet_ntoa(this->clients[i].sock.sockaddr.sin_addr)) == NULL ||
      getsockname(this->clients[i].sock.sock,
		  (struct sockaddr *)&this->clients[i].sock.sockaddr,
		  &this->clients[i].len) == -1)
    return (perror("client connection"), NULL);
  return (&this->clients[i]);
}

t_socket	*get_socket_connection(t_socket *this)
{
  t_socket	*sock;
  socklen_t	len;

  if ((sock = malloc(sizeof(*sock))) == NULL)
    return (perror("socket connection"), NULL);
  len = sizeof(sock->sockaddr);
  *sock = DEF_SOCKET;
  sock->mode = TALKING;
  if ((sock->sock = accept(this->sock,
			   (struct sockaddr *)&sock->sockaddr, &len)) == -1)
    return (free(sock), perror("socket connection"), NULL);
  return (sock);
}

void	update_client_states(t_server *this)
{
  int	i;

  i = 0;
  while (i < this->nbclient)
    {
      if (this->clients[i].pid != -1 &&
	  waitpid(this->clients[i].pid, NULL, WNOHANG) == 0)
	{
	  remove_client_from_server(this, &this->clients[i]);
	}
      ++i;
    }
}
