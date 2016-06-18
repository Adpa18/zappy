/*
** ncurses_gestion.c for NCURSES in /home/gouet_v/Rendu/semester4/PSU/PSU_2015_zappy
** 
** Made by Victor Gouet
** Login   <gouet_v@epitech.net>
** 
** Started on  Fri Jun 17 12:09:53 2016 Victor Gouet
** Last update Fri Jun 17 12:12:49 2016 Victor Gouet
*/

#include <stdio.h>
#include "../include_server/server.h"

int		init_ncurses()
{
  return (0);
}

int		ncurses_gestion(t_list *list, t_command_line *command)
{
#ifndef GRAPHIC_SERVER
  printf("NO GRAPHICAL");
  return (0);
#endif
  printf("GRAPHIC_SERVER");
  (void)list;
  (void)command;
  return (0);
}
