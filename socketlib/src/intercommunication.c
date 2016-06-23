/*
** intercommunication.c for intercommunication implementation functions in /home/gaspar_q/rendu/semestre4/SystemeUnix/PSU_2015_myftp/include/socketlib
**
** Made by Quentin Gasparotto
** Login   <gaspar_q@epitech.net>
**
** Started on  Mon May  2 12:44:39 2016 Quentin Gasparotto
** Last update Thu Jun 23 16:38:08 2016 Victor Gouet
*/

#include <stdarg.h>
#include <string.h>
#include <stdio.h>

#include "../include/my_sock.h"

int	get_ip_and_port(char *toparse, char *ip, int *port)
{
  char	splitted[6][500];
  int	i;
  int	j;
  int	save;

  i = -1;
  j = 0;
  save = 0;
  while (toparse[++i] != '\0')
    {
      if (j < 4)
	ip[i] = (toparse[i] == ',' ? '.' * (j != 3) : toparse[i]);
      if (toparse[i] == ',')
	{
	  toparse[i] = '\0';
	  strcpy(splitted[j++], &toparse[save]);
	  save = i + 1;
	}
    }
  if (j < 5)
    return (-1);
  strcpy(splitted[j], &toparse[save]);
  *port = atoi(splitted[4]) * 256 + atoi(splitted[5]);
  return (0);
}

int	send_binary(const char *data, t_socket *interlocutor)
{
  return (write(interlocutor->sock, data, strlen(data)));
}

int	send_message(const char *message, t_socket *interlocutor)
{
  int	i;
  int	len;
  int	stat;

  i = 0;
  printf("- send : - %s\n", message);
  if (interlocutor->is_writable == false)
    {
      printf("send ko. false\n");
      return (0);
    }
  len = strlen(message);
  while (i < len)
    {
      if ((stat = send(interlocutor->sock, &message[i],
		       strlen(&message[i]), MSG_NOSIGNAL)) == -1)
	{
	  printf("send ko.\n");
	  return (-1);
	}
      i += stat;
    }
  printf("send ok.\n");
  return (0);
}

int		sendf_message(t_socket *interlocutor, const char *format, ...)
{
  va_list	list;
  char		tosend[BUFSIZ];

  va_start(list, format);
  if (vsnprintf(tosend, BUFSIZ, format, list) == -1 ||
      send_message(tosend, interlocutor) == -1)
    return (-1);
  va_end(list);
  return (0);
}

char		*receive_message(t_socket *interlocutor)
{
  char		*message;
  size_t	torealloc;
  ssize_t	readret;
  bool		filled;

  filled = false;
  torealloc = BUFSIZ + 1;
  if ((message = malloc(torealloc)) == NULL)
    return (NULL);
  while ((readret = read(interlocutor->sock,
			 &message[torealloc - BUFSIZ - 1],
			 BUFSIZ)) == BUFSIZ)
    {
      filled = true;
      torealloc += readret;
      if ((message = realloc(message, torealloc)) == NULL)
	return (NULL);
    }
  message[torealloc - BUFSIZ - 1 + readret] = '\0';
  if (!filled && readret == 0)
    return (free(message), NULL);
  return (message);
}
