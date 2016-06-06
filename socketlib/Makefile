##
## Makefile for my socket lib makefile in /home/gaspar_q/rendu/semestre4/SystemeUnix/PSU_2015_myftp/include/socketlib
##
## Made by Quentin Gasparotto
## Login   <gaspar_q@epitech.net>
##
## Started on  Mon May  2 12:46:26 2016 Quentin Gasparotto
## Last update Thu May 19 13:46:52 2016 Quentin Gasparotto
##

DEBUG	=	no

NAME	=	libmy_socket.a

RM	=	rm -rf

CC	=	gcc

SRCNAM	=	intercommunication.c	\
		socket_creation.c	\
		socket_deletion.c	\
		connections.c		\
		bind_sockets.c		\
		crlf_getnextline.c

SRCPREF	=	./src/

SRCS	=	$(addprefix $(SRCPREF), $(SRCNAM))

OBJS	=	$(SRCS:.c=.o)

CFLAGS	=	-W -Wall -Wextra

ifeq	($(DEBUG),yes)
	CFLAGS	+= -g
endif

$(NAME):	$(OBJS)
	@echo -e "------------------------\n| \e[32mCOMPILING SOCKET LIB\e[0m |\n------------------------"
	ar rc $(NAME) $(OBJS)
	ranlib $(NAME)
	@echo -e "-------------------------\n| \e[32mSOCKET LIB IS RUNNING\e[0m |\n-------------------------"

all:	$(NAME)

clean:
	$(RM) $(OBJS)

fclean:	clean
	$(RM) $(NAME)

re:	fclean all
