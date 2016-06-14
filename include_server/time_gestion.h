/*
** time_gestion.h for TIME in /home/gouet_v/Rendu/semester4/PSU/PSU_2015_zappy
** 
** Made by Victor Gouet
** Login   <gouet_v@epitech.net>
** 
** Started on  Fri Jun 10 12:12:27 2016 Victor Gouet
** Last update Mon Jun 13 11:40:36 2016 Victor Gouet
*/

#ifndef TIME_GESTION_H_
# define TIME_GESTION_H_

# include <stdbool.h>

# define TIME_COMMAND_SIZE	12

typedef struct	s_time_command
{
  char		command[20];
  long long	timeout;
}		t_time_command;

long long		getTimeSeconds();
bool			is_time_out_for(char *command, int time,
					  long long time_ref);
bool			is_time_out_in(long long time_ref, long long time);

#endif
