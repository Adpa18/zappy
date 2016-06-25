/*
** my_sock.h for my socket lib header in /home/gaspar_q/rendu/semestre4/SystemeUnix/PSU_2015_myftp/include/socketlib
**
** Made by Quentin Gasparotto
** Login   <gaspar_q@epitech.net>
**
** Started on  Mon May  2 11:10:07 2016 Quentin Gasparotto
** Last update Sat Jun 25 10:39:47 2016 Victor Gouet
*/

#ifndef MY_SOCK_LIB_H_
# define MY_SOCK_LIB_H_

# include <unistd.h>
# include <sys/types.h>
# include <sys/socket.h>
# include <netdb.h>
# include <stdbool.h>
# include <netinet/in.h>
# include <arpa/inet.h>
# include <stdlib.h>

# define TCP	"TCP"
# define CRLF	"\r\n"

typedef enum	e_sockmode
  {
    NOMODE,
    LISTENING,
    TALKING
  }		t_sockmode;

typedef struct		s_socket
{
  struct sockaddr_in	sockaddr;
  int			sock;
  t_sockmode		mode;
}			t_socket;

typedef struct		s_client
{
  t_socket		sock;
  socklen_t		len;
  pid_t			pid;
  char			*ip;
}			t_client;

typedef struct		s_server
{
  t_socket		socket;
  int			nbclient;
  t_client		clients[0];
}			t_server;

# define DEF_CO		((struct sockaddr_in){0, 0, {0}, {0}})
# define DEF_SOCKET	((t_socket){DEF_CO, -1, NOMODE})
# define DEF_CLIENT	((t_client){DEF_SOCKET, sizeof(DEF_CO), -1, NULL})

/*
**	Prototypes
*/

/*
**		bind_sockets.c
*/

void		*create_socket(const char *protocol,
			       const int domain,
			       int option,
			       size_t size);
int		bind_listening_socket(t_socket *socket,
				      const int domain,
				      const int port,
				      const int nbc);
int		bind_talking_socket(t_socket *socket,
				    const int domain,
				    const int port,
				    const char *ip);

/*
**		socket_creation.c
*/

t_server	*create_server(const int nbc, const char *protocol,
			       const int domain, const int port);
t_client	*create_client(const char *protocol, const int domain,
			       const char *ip, const int port);

/*
**		socket_deletion.c
*/

int		delete_socket(t_socket *this);
int		delete_server(t_server *this);
int		delete_client(t_client *this);
void		remove_client_from_server(t_server *this,
					  t_client *to_remove);

/*
**		intercommunication.c
*/

int		get_ip_and_port(char *toparse, char *ip, int *port);
char		*receive_message(t_socket *interlocutor);
int		send_message(const char *message, t_socket *interlocutor);
int		send_binary(const char *data, t_socket *interlocutor);
int		sendf_message(t_socket *interlocutor,
			      const char *format, ...);

/*
**		connections.c
*/

t_socket	*get_socket_connection(t_socket *this);
bool		is_default_client(const t_client *tocmp);
t_client	*get_client_connection(t_server *this);

/*
**		crlf_getnextline.c
*/

char		*get_crlf_next_line(t_client *client);
char		*get_crlf_line(t_client *client);

#endif	/* !MY_SOCK_LIB_H_ */
