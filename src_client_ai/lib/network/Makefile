##
## Makefile for network cpp lib in /home/gaspar_q/rendu/semestre4/SystemeUnix/PSU_2015_zappy/src_client_ai/lib/network
##
## Made by Quentin Gasparotto
## Login   <gaspar_q@epitech.net>
##
## Started on  Fri Jun 10 17:27:06 2016 Quentin Gasparotto
## Last update Fri Jun 10 17:42:29 2016 Quentin Gasparotto
##

NAME		=	libnetwork.a

RM		=	rm -rf

CC		=	g++

SRCDIR		=	./src/

INCDIR		=	./include/

SRCS		=	Client.cpp		\
			NetworkWatcher.cpp	\
			Socket.cpp

OBJS		=	$(addprefix $(SRCDIR), $(SRCS:.cpp=.o))

CPPFLAGS	=	-W -Wall -Wextra
CPPFLAGS	+=	-I$(INCDIR)
CPPFLAGS	+=	-std=c++11

$(NAME):	$(OBJS)
	ar rc $(NAME) $(OBJS)
	ranlib $(NAME)

all:	$(NAME)

clean:
	$(RM) $(OBJS)

fclean:	clean
	$(RM) $(NAME)

re:	fclean all

.PHONY:	all clean fclean re
