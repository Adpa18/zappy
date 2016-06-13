/*
** time_gestion.c for TIME in /home/gouet_v/Rendu/semester4/PSU/PSU_2015_zappy
** 
** Made by Victor Gouet
** Login   <gouet_v@epitech.net>
** 
** Started on  Fri Jun 10 12:00:15 2016 Victor Gouet
** Last update Mon Jun 13 11:40:52 2016 Victor Gouet
*/

#include <sys/time.h>
#include <time.h>
#include <stdio.h>
#include <string.h>
#include "../include_server/time_gestion.h"

static void	init_command_time(int time, t_time_command *time_command)
{
  strcpy(time_command[0].command, "avance");
  time_command[0].timeout = ((double)7 / (time == 0 ? 1 : time) * 1000);
  strcpy(time_command[1].command, "droite");
  time_command[1].timeout = ((double)7 / (time == 0 ? 1 : time) * 1000);
  strcpy(time_command[2].command, "gauche");
  time_command[2].timeout = ((double)7 / (time == 0 ? 1 : time) * 1000);
  strcpy(time_command[3].command, "voir");
  time_command[3].timeout = ((double)7 / (time == 0 ? 1 : time) * 1000);
  strcpy(time_command[4].command, "inventaire");
  time_command[4].timeout = ((double)1 / (time == 0 ? 1 : time) * 1000);
  strcpy(time_command[5].command, "prend");
  time_command[5].timeout = ((double)7 / (time == 0 ? 1 : time) * 1000);
  strcpy(time_command[6].command, "pose");
  time_command[6].timeout = ((double)7 / (time == 0 ? 1 : time) * 1000);
  strcpy(time_command[7].command, "expulse");
  time_command[7].timeout = ((double)7 / (time == 0 ? 1 : time) * 1000);
  strcpy(time_command[8].command, "broadcast");
  time_command[8].timeout = ((double)7 / (time == 0 ? 1 : time) * 1000);
  strcpy(time_command[9].command, "incantation");
  time_command[9].timeout = ((double)300 / (time == 0 ? 1 : time) * 1000);
  strcpy(time_command[10].command, "fork");
  time_command[10].timeout = ((double)42 / (time == 0 ? 1 : time) * 1000);
  strcpy(time_command[11].command, "connect_nbr");
  time_command[11].timeout = 0;
}

long long		getTimeSeconds()
{
  struct timeval	tp;
  long long		mslong;

  gettimeofday(&tp, NULL);
  mslong = (long long)tp.tv_sec * 1000L + tp.tv_usec / 1000;
  return (mslong);
}

bool			is_time_out_in(long long time_ref, long long time)
{
  long long		actual_time;

  actual_time = getTimeSeconds();
  if (time_ref + time >= actual_time)
    {
      return (false);
    }
  return (true);
}

bool			is_time_out_for(char *command, int time,
					long long time_ref)
{
  t_time_command	time_command[TIME_COMMAND_SIZE];
  int			i;

  i = 0;
  init_command_time(time, time_command);
  while (i < TIME_COMMAND_SIZE)
    {
      if (strcmp(time_command[i].command, command) == 0)
	{
	  if (time_ref + time_command[i].timeout <= getTimeSeconds())
	    {
	      return (true);
	    }
	  else
	    return (false);
	}
      ++i;
    }
  return (true);
}
