/*
** bind_sockets.c for bind socket listening or writing in /home/gaspar_q/rendu/semestre4/SystemeUnix/PSU_2015_myftp
**
** Made by Quentin Gasparotto
** Login   <gaspar_q@epitech.net>
**
** Started on  Wed May  4 11:31:02 2016 Quentin Gasparotto
** Last update Tue May 10 21:48:19 2016 Quentin Gasparotto
*/

#include <stdio.h>
#include "../include/my_sock.h"

void			*create_socket(const char *protocol,
				       const int domain,
				       int option,
				       size_t size)
{
  t_socket		*sock;
  struct protoent	*proto;

  if (size < sizeof(*sock))
    return (fprintf(stderr, "create socket: socket size is to low\n"), NULL);
  if ((sock = malloc(size)) == NULL ||
      (proto = getprotobyname(protocol)) == NULL ||
      (sock->sock = socket(domain, SOCK_STREAM, proto->p_proto)) == -1 ||
      setsockopt(sock->sock, SOL_SOCKET, (SO_REUSEPORT | SO_REUSEADDR),
		 (char *)&option, sizeof(option)) == -1)
    return (perror("create socket"), NULL);
  return (sock);
}

int	bind_listening_socket(t_socket *socket,
			      const int domain,
			      const int port,
			      const int nbc)
{
  socket->sockaddr.sin_family = domain;
  socket->sockaddr.sin_port = htons(port);
  socket->sockaddr.sin_addr.s_addr = INADDR_ANY;
  if (bind(socket->sock, (const struct sockaddr *)socket,
	   sizeof(socket->sockaddr)) == -1 ||
      listen(socket->sock, nbc) == -1)
    return (perror("create server"), -1);
  socket->mode = LISTENING;
  return (0);
}

int	bind_talking_socket(t_socket *socket,
			    const int domain,
			    const int port,
			    const char *ip)
{
  socket->sockaddr.sin_family = domain;
  socket->sockaddr.sin_port = htons(port);
  socket->sockaddr.sin_addr.s_addr = inet_addr(ip);
  if (connect(socket->sock, (struct sockaddr *)socket,
	      sizeof(socket->sockaddr)) == -1)
    return (-1);
  socket->mode = TALKING;
  return (0);
}
