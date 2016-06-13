/*
** time_gestion.h for TIME in /home/gouet_v/Rendu/semester4/PSU/PSU_2015_zappy
** 
** Made by Victor Gouet
** Login   <gouet_v@epitech.net>
** 
** Started on  Fri Jun 10 12:12:27 2016 Victor Gouet
** Last update Fri Jun 10 17:13:42 2016 Victor Gouet
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

#endif
