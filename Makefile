##
## Makefile for MAKEFILE in /home/gouet_v/Rendu/semester4/PSU/PSU_2015_myftp
## 
## Made by Victor Gouet
## Login   <gouet_v@epitech.net>
## 
## Started on  Mon May  2 10:16:12 2016 Victor Gouet
## Last update Tue Jun  7 19:09:48 2016 Victor Gouet
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
