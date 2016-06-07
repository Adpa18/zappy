/*
** get_data.c for GESTION in /home/gouet_v/Rendu/semester4/PSU/PSU_2015_myftp
** 
** Made by Victor Gouet
** Login   <gouet_v@epitech.net>
** 
** Started on  Mon May  2 18:48:58 2016 Victor Gouet
** Last update Tue Jun  7 19:15:44 2016 Victor Gouet
*/

#include <strings.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include_server/server.h"

static char		*acr_if_white_space(char *buffer, int *x,
					    size_t *y, char **tab)
{
  while ((*buffer == ' ' || *buffer == '\t') && *buffer != 0)
    {
      if (*x != 0)
	tab[(*y)++][*x] = 0;
      *x = 0;
      ++buffer;
    }
  if (*buffer == 0 || *buffer == '\r' || *buffer == '\n')
    {
      *x = 0;
      return (NULL);
    }
  return (buffer);
}

char		**str_to_word_tab(char *buffer)
{
  char			**tab;
  size_t		y;
  int			x;
  char			*ref;

  ref = buffer;
  if ((tab = malloc((strlen(buffer) + 1) * sizeof(char *))) == NULL)
    return (NULL);
  y = 0;
  x = 0;
  while (*buffer != 0 && *buffer != '\r' && *buffer != '\n')
    {
      if ((buffer = acr_if_white_space(buffer, &x, &y, tab)) == NULL)
	break;
      if (x == 0 && (tab[y] = malloc(strlen(buffer) + 1)) == NULL)
	return (NULL);
      tab[y][x++] = *buffer;
      ++buffer;
    }
  if (x != 0)
    tab[y++][x] = 0;
  while (y < strlen(ref) + 1)
    tab[y++] = NULL;
  return (tab);
}

char		**split(char *str, char carac)
{
  char		**tab;
  int		x;
  int		y;

  x = 0;
  if (y = 0, (tab = malloc((strlen(str) + 1) * sizeof(char *))) == NULL)
    return (NULL);
  while (*str != 0)
    {
      if (x == 0)
	if ((tab[y] = malloc((strlen(str) + 1))) == NULL)
	  return (NULL);
      if (*str == carac)
	{
	  tab[y++][x] = '\0';
	  x = 0;
	}
      else
	tab[y][x++] = *str;
      ++str;
    }
  if (x != 0)
    tab[y++][x] = '\0';
  tab[y] = NULL;
  return (tab);
}

void		delete_command(char **command, char *buffer)
{
  int		i;
  int		size;

  i = 0;
  size = (int)strlen(buffer);
  while (i < size)
    {
      if (command[i])
	free(command[i]);
      ++i;
    }
  free(command);
  free(buffer);
}

int		contain_string(char const *s1, char const *s2)
{
  int		i;
  int		size;

  i = 0;
  size = strlen(s2);
  while (s1[i])
    {
      if (strncmp(&s1[i], s2, size) == 0)
	{
	  return (0);
	}
      ++i;
    }
  return (-1);
}
