/*
** monitor_event.h for MONITOR in /home/gouet_v/Rendu/semester4/PSU/PSU_2015_zappy
** 
** Made by Victor Gouet
** Login   <gouet_v@epitech.net>
** 
** Started on  Mon Jun 13 13:36:07 2016 Victor Gouet
** Last update Mon Jun 13 14:00:07 2016 Victor Gouet
*/

#ifndef MONITOR_EVENT_H_
# define MONITOR_EVENT_H_

# include "server.h"

int     bct_event(t_monitor *monitor, t_list *list,
		  t_command_line *command, char **tab);
int	ebo_event(t_monitor *monitor, t_list *list,
		  t_command_line *command, char **tab);
int	edi_event(t_monitor *monitor, t_list *list,
		  t_command_line *command, char **tab);
int	eht_event(t_monitor *monitor, t_list *list,
		  t_command_line *command, char **tab);
int	enw_event(t_monitor *monitor, t_list *list,
		  t_command_line *command, char **tab);
int	msz_event(t_monitor *monitor, t_list *list,
		  t_command_line *command, char **tab);
int	pbc_event(t_monitor *monitor, t_list *list,
		  t_command_line *command, char **tab);
int	pdi_event(t_monitor *monitor, t_list *list,
		  t_command_line *command, char **tab);
int	pdr_event(t_monitor *monitor, t_list *list,
		  t_command_line *command, char **tab);
int	pex_event(t_monitor *monitor, t_list *list,
		  t_command_line *command, char **tab);
int	pfk_event(t_monitor *monitor, t_list *list,
		  t_command_line *command, char **tab);
int	pgt_event(t_monitor *monitor, t_list *list,
		  t_command_line *command, char **tab);
int	pic_event(t_monitor *monitor, t_list *list,
		  t_command_line *command, char **tab);
int	pie_event(t_monitor *monitor, t_list *list,
		  t_command_line *command, char **tab);
int	pin_event(t_monitor *monitor, t_list *list,
		  t_command_line *command, char **tab);
int	plv_event(t_monitor *monitor, t_list *list,
		  t_command_line *command, char **tab);
int	pnw_event(t_monitor *monitor, t_list *list,
		  t_command_line *command, char **tab);
int	ppo_event(t_monitor *monitor, t_list *list,
		  t_command_line *command, char **tab);
int	sbp_event(t_monitor *monitor, t_list *list,
		  t_command_line *command, char **tab);
int	seg_event(t_monitor *monitor, t_list *list,
		  t_command_line *command, char **tab);
int	sgt_event(t_monitor *monitor, t_list *list,
		  t_command_line *command, char **tab);
int	smg_event(t_monitor *monitor, t_list *list,
		  t_command_line *command, char **tab);
int	suc_event(t_monitor *monitor, t_list *list,
		  t_command_line *command, char **tab);
int	tna_event(t_monitor *monitor, t_list *list,
		  t_command_line *command, char **tab);

#endif
