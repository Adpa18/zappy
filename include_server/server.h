/*
** server.h for SERVER in /home/gouet_v/Rendu/semester4/PSU/PSU_2015_zappy
** 
** Made by Victor Gouet
** Login   <gouet_v@epitech.net>
** 
** Started on  Tue Jun  7 14:29:57 2016 Victor Gouet
** Last update Tue Jun  7 20:00:26 2016 Victor Gouet
*/

#ifndef SERVER_H_
# define SERVER_H_

# include "command_line_arguments.h"
# include "../socketlib/include/my_sock.h"

# define GRAPHIC	"GRAPHIC"

typedef enum
  {
    TRANTORIEN,
    MONITOR,
    UNKNOWN
  }		t_type;

typedef struct	s_ref
{
  t_type	type;
  t_client	*client;
  struct s_ref	*next;
  void		*ref;
}		t_ref;

typedef struct	s_trantorien
{
  t_ref		*ref;
  double	koala;
  struct s_trantorien	*next_on_team;
}		t_trantorien;

typedef struct	s_monitor
{
  t_ref		*ref;
  int		data;
}		t_monitor;

typedef struct	s_list
{
  void		*begin;
  void		*end;
  int		max_fd;
  int		nbr_client;
}		t_list;

/*
**	convert_client.c
*/

t_monitor	*transform_to_monitor(t_ref *ref);
t_trantorien	*transform_to_trantorien(t_ref *ref);

/*
**	team_gestion.c
*/

t_team_name	*get_team(t_team_list *list, char const *name);

/*
**	remove_client_to_team.c
*/

t_trantorien	*remove_client_to_team(t_team_name *list,
				       t_trantorien *ref);
t_trantorien	*remove_client_to_unknown_team(t_team_list *list,
					       t_trantorien *ref);

/*
**	add_client_to_team.c
*/

int	add_client_to_team(t_team_name *team, t_trantorien *trantorien);

/*
**	unknown_client.c
*/

int		unknwon_client_event(t_ref *ref, t_list *list,
				     t_command_line *command,
				     char **tab);

/*
**	get_data.c
*/

char            **str_to_word_tab(char *buffer);
char            **split(char *str, char carac);
int             contain_string(char const *s1, char const *s2);
void		delete_command(char **command, char *buffer);

/*
**	remove_client_to_list.c
*/

t_ref	*remove_client_to_list(t_list *list, t_ref *ref);

/*
**	event_client.c
*/

int	event_client(t_list *list, t_command_line *command, fd_set *fds,
		     t_server *server);

void		server_run(t_command_line *);
void		*add_client_to_list(t_list *list,
				    t_type type,
				    t_client *client);
void		list_constructor(t_list *list, int fd);

/*
**	display_client.c
*/

void	display_team(t_team_list *list);
void    display_client_in_list(t_list *list);

#endif
