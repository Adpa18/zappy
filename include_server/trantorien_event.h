/*
** trantorien_event.c for TRANTORIEN EVENT in /home/gouet_v/Rendu/semester4/PSU/PSU_2015_zappy
** 
** Made by Victor Gouet
** Login   <gouet_v@epitech.net>
** 
** Started on  Wed Jun  8 07:56:42 2016 Victor Gouet
** Last update Wed Jun  8 11:20:17 2016 Victor Gouet
*/

#ifndef TRANTORIEN_EVENT_H_
# define TRANTORIEN_EVENT_H_

# include "server.h"

#define START_INVETAIRE "{nourriture %d, linemate %d, deraumere %d, "
#define END_INVENTAIRE  "sibur %d, mendiane %d, phiras %d, thystame %d}"

int	avance_event(t_trantorien *trantorien, t_list *list,
		     t_command_line *command, char **tab);
int     broadcast_event(t_trantorien *trantorien, t_list *list,
			t_command_line *command, char **tab);
int     connect_nbr_event(t_trantorien *trantorien, t_list *list,
			  t_command_line *command, char **tab);
int	droite_event(t_trantorien *trantorien, t_list *list,
		     t_command_line *command, char **tab);
int     expulse_event(t_trantorien *trantorien, t_list *list,
		      t_command_line *command, char **tab);
int     fork_event(t_trantorien *trantorien, t_list *list,
		   t_command_line *command, char **tab);
int     gauche_event(t_trantorien *trantorien, t_list *list,
		     t_command_line *command, char **tab);
int     incantation_event(t_trantorien *trantorien, t_list *list,
			  t_command_line *command, char **tab);
int     inventaire_event(t_trantorien *trantorien, t_list *list,
			 t_command_line *command, char **tab);
int     pose_obj_event(t_trantorien *trantorien, t_list *list,
		       t_command_line *command, char **tab);
int     prend_obj_event(t_trantorien *trantorien, t_list *list,
			t_command_line *command, char **tab);
int     voir_event(t_trantorien *trantorien, t_list *list,
		   t_command_line *command, char **tab);

#endif
