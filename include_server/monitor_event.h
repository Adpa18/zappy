/*
** monitor_event.h for MONITOR in /home/gouet_v/Rendu/semester4/PSU/PSU_2015_zappy
** 
** Made by Victor Gouet
** Login   <gouet_v@epitech.net>
** 
** Started on  Mon Jun 13 13:36:07 2016 Victor Gouet
** Last update Wed Jun 22 13:56:39 2016 Victor Gouet
*/

#ifndef MONITOR_EVENT_H_
# define MONITOR_EVENT_H_

# include "server.h"

int	time_event(t_monitor *monitor, t_list *list,
		   t_command_line *command, char **tab);
int	mct_to_all_monitor(t_list *list);
int	plv_event_for_one_trantorien(t_list *list,
				     t_trantorien *trantorien);
int	plv_event_all_monitor(t_list *list);
int     pin_event_to_all_monitor(t_list *list, t_trantorien *trantorien);
int	bct_event_to_all_monitor(t_list *list, int x, int y);
int	ppo_event_to_all_monitor(t_trantorien *trantorien,
				 t_list *list);
int	pnw_event_all_to_monitor(t_monitor *monitor,
				 t_command_line *command);
int	enw_event_all_to_monitor(t_monitor *monitor, t_command_line *);
void	send_msg_to_all_monitor(char const *msg, t_list *);
int     sst_event(t_monitor *monitor, t_list *list,
		  t_command_line *command, char **tab);
int     bct_event(t_monitor *monitor, t_list *list,
		  t_command_line *command, char **tab);
int	ebo_event(t_trantorien *trantorien, t_list *list);
int     edi_event(t_trantorien *egg,
		  t_list *list);
int     eht_event(t_trantorien *egg, t_list *list);
int	enw_event(t_trantorien *player, t_trantorien *egg,
		  t_list *list);
int	msz_event(t_monitor *monitor, t_list *list,
		  t_command_line *command, char **tab);
int     pbc_event(t_trantorien *trantorien, t_list *list, char *);
int     pdi_event(t_trantorien *trantorien, t_list *list);
int	pdr_event(t_trantorien *trantorien, t_list *list,
		  int id_ressource);
int	pex_event(t_trantorien *trantorien, t_list *list);
int	pfk_event(t_trantorien *trantorien, t_list *list);
int     pgt_event(t_trantorien *trantorien, t_list *list,
		  int id_ressource);
int	pic_event(t_trantorien *trantorien, t_list *list);
int	pie_event(t_trantorien *trantorien, t_list *list,
		  int succes);
int	pin_event(t_monitor *monitor, t_list *list,
		  t_command_line *command, char **tab);
int	plv_event(t_monitor *monitor, t_list *list,
		  t_command_line *command, char **tab);
int	pnw_event(t_trantorien *, t_list *);
int	ppo_event(t_monitor *monitor, t_list *list,
		  t_command_line *command, char **tab);
int	sbp_event(t_monitor *monitor);
int	seg_event(t_trantorien *trantorien, t_list *list);
int	sgt_event(t_monitor *monitor, t_list *list,
		  t_command_line *command, char **tab);
int	smg_event(char *msg, t_list *list);
int	suc_event(t_monitor *monitor);
int	tna_event(t_monitor *monitor, t_list *list,
		  t_command_line *command, char **tab);
int     mct_event(t_monitor *monitor, t_list *list,
		  t_command_line *command, char **tab);

#endif
