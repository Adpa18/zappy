##
## Makefile for MAKEFILE in /home/gouet_v/Rendu/semester4/PSU/PSU_2015_myftp
## 
## Made by Victor Gouet
## Login   <gouet_v@epitech.net>
## 
## Started on  Mon May  2 10:16:12 2016 Victor Gouet
## Last update Fri Jun 10 14:42:08 2016 Victor Gouet
##

CC		= gcc

RM		= rm -f

NAME		= zappy_server

SOCKETLIB	= ./socketlib/

STRINGLIB	= ./stringLib/

SRCS		= src_server/main.c \
		  src_server/command_line_arguments.c \
		  src_server/command_line_opt.c \
		  src_server/server_gestion.c \
		  src_server/add_client_to_list.c \
		  src_server/display_client.c \
		  src_server/event_client.c \
		  src_server/remove_client_to_list.c \
		  src_server/add_client_to_team.c \
		  src_server/remove_client_to_team.c \
		  src_server/get_data.c \
		  src_server/unknown_client.c \
		  src_server/convert_client.c \
		  src_server/team_gestion.c \
		  src_server/map.c \
		  src_server/buffer_gestion.c \
		  src_server/time_gestion.c \
		  src_server/Trantorien_Event/avance_event.c \
		  src_server/Trantorien_Event/broadcast_event.c \
		  src_server/Trantorien_Event/connect_nbr_event.c \
		  src_server/Trantorien_Event/droite_event.c \
		  src_server/Trantorien_Event/expulse_event.c \
		  src_server/Trantorien_Event/fork_event.c \
		  src_server/Trantorien_Event/gauche_event.c \
		  src_server/Trantorien_Event/incantation_event.c \
		  src_server/Trantorien_Event/inventaire_event.c \
		  src_server/Trantorien_Event/pose_obj_event.c \
		  src_server/Trantorien_Event/prend_obj_event.c \
		  src_server/Trantorien_Event/voir_event.c \

OBJS		= $(SRCS:.c=.o)

OBJSLIB		= $(LIBS:.c=.o)

CFLAGS		= -I./include -Wall -Wextra -W -I ./lib -I $(SOCKETLIB)include/ -I ./server_include/ -g

LDFLAGS		= -L $(STRINGLIB) -lstringLib -L $(SOCKETLIB) -lmy_socket 

$(NAME):	$(OBJS)
		make -C $(SOCKETLIB)
		make -C $(STRINGLIB)
		$(CC) -o $(NAME) $(OBJS) $(LDFLAGS) 

all:		$(NAME)

clean:
		$(RM) $(OBJS)
		make clean -C $(SOCKETLIB)
		make clean -C $(STRINGLIB)

fclean:		clean
		$(RM) $(NAME)
		make fclean -C $(SOCKETLIB)
		make fclean -C $(STRINGLIB)

re:		fclean all

.PHONY:		all clean fclean re client
