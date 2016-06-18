/*
** command_line_arguments.h for COMMAND LINE in /home/gouet_v/Rendu/semester4/PSU/PSU_2015_zappy
** 
** Made by Victor Gouet
** Login   <gouet_v@epitech.net>
** 
** Started on  Mon Jun  6 22:40:45 2016 Victor Gouet
** Last update Wed Jun 15 10:27:18 2016 Victor Gouet
*/

#ifndef COMMAND_LINE_ARGUMENTS_H_
# define COMMAND_LINE_ARGUMENTS_H_

# define SUCCESS	1
# define FAILURE	0
# define OPTION_NBR	6
# define DEFAULTTIME	100

# define USAGE		"Usage: -p port -x width -y height -n team"
# define USAGE_END	" -c client\'s number [-t] [time > 0]\n"

typedef struct		s_team_name
{
  char			*name;
  void			*begin;
  void			*end;
  int			nbr_client;
  int			nbr_max;
  struct s_team_name	*next;
}			t_team_name;

typedef struct		s_team_list
{
  struct s_team_name	*begin;
  struct s_team_name	*end;
}			t_team_list;

typedef struct	s_command_line
{
  int		port;
  int		x;
  int		y;
  int		nb_client;
  t_team_list	team_list;
  int		time;
}		t_command_line;

typedef struct	s_opt_gestion
{
  int		(*fptr)();
  char		opt;
}		t_opt_gestion;

int		on_port(t_command_line *);
int		on_width(t_command_line *);
int		on_height(t_command_line *);
int		on_team_name(t_command_line *, char **);
int		on_client_nbr(t_command_line *);
int		on_time(t_command_line *);

/*
**	command_line_arguments.c
*/

t_team_name	*add_team_elem(t_team_list *list);
int	on_command_line_server(int ac, char **av,
			       t_command_line *command);

#endif
