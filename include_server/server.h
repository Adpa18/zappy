/*
** server.h for SERVER in /home/gouet_v/Rendu/semester4/PSU/PSU_2015_zappy
** 
** Made by Victor Gouet
** Login   <gouet_v@epitech.net>
** 
** Started on  Tue Jun  7 14:29:57 2016 Victor Gouet
** Last update Tue Jun 14 01:22:56 2016 Victor Gouet
*/

#ifndef SERVER_H_
# define SERVER_H_

# include <stdbool.h>
# include "command_line_arguments.h"
# include "../socketlib/include/my_sock.h"

# define EVENTSIZE	25
# define GRAPHIC	"GRAPHIC"
# define BIENVENUE	"BIENVENUE\n"
# define UNITEDLIFE	126

typedef enum
  {
    TRANTORIEN,
    MONITOR,
    UNKNOWN
  }		t_type;

typedef enum
  {
    N = 1,
    E = 2,
    S = 3,
    O = 4
  }		t_orientation;

typedef struct	s_inventories
{
  int		food;
  int		linemate;
  int		deraumere;
  int		sibur;
  int		mendiane;
  int		phiras;
  int		thystame;
}		t_inventories;

typedef struct	s_map
{
  t_inventories	**map;
  int		width;
  int		height;
}		t_map;

typedef struct	s_event
{
  char		*event_name[EVENTSIZE];
  int		(*callBack[EVENTSIZE])();
}		t_event;

typedef struct	s_buffer
{
  char		*buffer;
  char		**tab;
  struct s_buffer	*next;
}		t_buffer;

typedef struct	s_ref
{
  t_type	type;
  t_client	*client;
  struct s_ref	*next;
  t_buffer	*begin;
  t_buffer	*end;
  long long	time_ref;
  int		buffer_size;
  void		*ref;
}		t_ref;

typedef struct	s_vector2d
{
  int		x;
  int		y;
}		t_vector2d;

typedef enum	s_trantorien_state
  {
    EGG,
    BABY,
    GHOST,
    PLAYER
  }		t_trantorien_state;

typedef struct	s_trantorien
{
  t_ref		*ref;
  char		*team;
  int		elevation;
  t_inventories	inventaire;
  long long	time_left_food;
  t_orientation	orientation;
  t_vector2d	pos;
  int		id;
  t_trantorien_state	state;
  long long	spawn;
  int		egg_id;
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
  t_map		*map;
}		t_list;

/*
**	end_of_game.c
*/

t_trantorien	*get_trantorien_with_max_elevation(t_list *list);

/*
**	egg_gestion.c
*/

void		on_gestion_egg(t_command_line *command, t_list *);
int		create_egg_on_team(int x, int y, t_team_name *team);

/*
**	get_trantorien.c
*/

t_trantorien	*get_trantorien_baby_from_team(t_team_name *team);
t_trantorien	*get_trantorien_ghost_from_team(t_team_name *team);
t_trantorien	*get_trantorien_from_id(t_list *list, int id);
t_trantorien	*get_trantorien_egg_from_team(t_team_name *team);

/*
**	food_gestion.c
*/

int	        food_gestion_for_trantorien(t_list *list,
					    t_command_line *command,
					    t_server *server);

/*
**	buffer_gestion.c
*/

void		display_buffer_from_client(t_ref *ref);
void		buffer_pop_front(t_ref *ref);
void		buffer_push_back(t_ref *ref, char *buffer,
				 char **);

/*
**	map.c
*/

void			display_map(t_map *map);
t_map			*create_map(int width, int height);
void			display_inventories(t_inventories *inventories);
void			generate_random_ressources(t_map *map);

/*
**	convert_client.c
*/

void		convert_to_trantorien(t_ref *ref,
				      t_trantorien *trantorien);
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
t_ref	*delete_all_in_client(t_list *list,
			      t_command_line *command,
			      t_server *server,
			      t_ref *ref);
t_ref	*remove_client_if_trantorien_change_state(t_list *list,
						  t_command_line *command,
						  t_server *server,
						  t_ref *ref);

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

/*
**	trantorien_connection.c
*/

int	trantorien_connection(t_ref *ref, t_team_name *team,
			      t_command_line *command, t_list *);
int		create_egg_on_team_from_trantorien(t_vector2d,
						   t_team_name *team,
						   t_trantorien *player,
						   t_list *);
void	init_trantorien(t_trantorien *trantorien,
			int x, int y);

#endif
