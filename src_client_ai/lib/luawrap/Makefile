##
## Makefile for lua cpp wrapper lib makefile in /home/gaspar_q/rendu/semestre4/SystemeUnix/PSU_2015_zappy/src_client_ai/lib/luawrap
##
## Made by Quentin Gasparotto
## Login   <gaspar_q@epitech.net>
##
## Started on  Fri Jun 10 17:45:12 2016 Quentin Gasparotto
## Last update Fri Jun 10 18:43:17 2016 Quentin Gasparotto
##

NAME	=	libluawrapper.a

RM	=	rm -rf

CC	=	g++

SRC	=	LuaScript.cpp

SRCDIR	=	./src/

INCDIR	=	./include/

LUADIR	=	./lua-5.3.2/src/

LUALIB	=	$(LUADIR)liblua.a

OBJ	=	$(addprefix $(SRCDIR), $(SRC:.cpp=.o))

CPPFLAGS	=	-W -Wall -Wextra
CPPFLAGS	+=	-I$(INCDIR) -I$(LUADIR)
CPPFLAGS	+=	-std=c++11

$(NAME):	$(OBJ)
	ar crsT $(NAME) $(OBJ) $(LUALIB)
	ranlib $(NAME)

all:	$(NAME)

clean:
	$(RM) $(OBJ)

fclean:	clean
	$(RM) $(NAME)

re:	fclean all

.PHONY:	all clean fclean re
