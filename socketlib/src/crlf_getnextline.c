/*
** ftp_getnextline.c for get next line for ftp server in /home/gaspar_q/rendu/semestre4/SystemeUnix/PSU_2015_myftp
**
** Made by Quentin Gasparotto
** Login   <gaspar_q@epitech.net>
**
** Started on  Thu May 12 19:21:36 2016 Quentin Gasparotto
** Last update Thu May 19 14:42:10 2016 Quentin Gasparotto
*/

#include <string.h>
#include <stdio.h>
#include "../include/my_sock.h"

static char	*dupconcat(char *f_str, char *s_str)
{
  char		*toreturn;

  if ((toreturn = malloc(strlen(f_str) + strlen(s_str) + 1)) == NULL)
    return (NULL);
  strcpy(toreturn, f_str);
  strcpy(&toreturn[strlen(f_str)], s_str);
  return (toreturn);
}

static int	resolve_buffers(char **buff, char **returnstr, bool freebuff)
{
  char		*newbuff;

  if ((newbuff = dupconcat(*returnstr, *buff)) == NULL)
    return (-1);
  free(*returnstr);
  *returnstr = newbuff;
  if (freebuff)
    {
      free(*buff);
      *buff = NULL;
    }
  return (0);
}

static int	extract_crlf(char **buff, char **returnstr)
{
  char		*crlf_pointer;
  char		*newbuff;
  char		*save;
  int		offset;

  if (((crlf_pointer = index(*buff, '\r')) == NULL ||
      crlf_pointer[1] != '\n') &&
      (crlf_pointer = index(*buff, '\n')) == NULL)
    return (resolve_buffers(buff, returnstr, true));
  offset = 1 + (*crlf_pointer == '\r');
  *crlf_pointer = '\0';
  crlf_pointer += offset;
  save = *buff;
  if ((newbuff = dupconcat(*returnstr, *buff)) == NULL ||
      (*buff = strdup(crlf_pointer)) == NULL)
    return (-1);
  free(*returnstr);
  free(save);
  *returnstr = newbuff;
  if ((*buff)[0] == '\0')
    {
      free(*buff);
      *buff = NULL;
    }
  return (1);
}

char		*get_crlf_next_line(t_client *client)
{
  static char	*tosave = NULL;
  char		*toreturn;
  int		status;

  if ((toreturn = strdup("")) == NULL)
    return (NULL);
  status = 0;
  while (status == 0)
    {
      if ((tosave == NULL &&
	   (tosave = receive_message(&client->sock)) == NULL) ||
	  (status = extract_crlf(&tosave, &toreturn)) == -1)
	return (free(toreturn), NULL);
    }
  return (toreturn);
}

char	*get_crlf_line(t_client *client)
{
  char	*toreturn;
  int   length;
  int	index;
  char	c;

  length = 0;
  toreturn = NULL;
  index = 0;
  while (read(client->sock.sock, &c, 1) > 0)
    {
      if (index == length &&
	  (toreturn = realloc(toreturn, length += BUFSIZ)) == NULL)
	return (NULL);
      toreturn[index] = c;
      if (toreturn[index] == '\n')
	{
	  if (index - 1 >= 0 && toreturn[index - 1] == '\r')
	    toreturn[index - 1] = '\0';
	  return (toreturn[index] = '\0', toreturn);
	}
      ++index;
    }
  if (toreturn)
    toreturn[index] = '\0';
  return (toreturn);
}
