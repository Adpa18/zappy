##
## Makefile for client ai makefile in /home/gaspar_q/rendu/semestre4/SystemeUnix/PSU_2015_zappy/src_client_ai
##
## Made by Quentin Gasparotto
## Login   <gaspar_q@epitech.net>
##
## Started on  Fri Jun 10 17:14:14 2016 Quentin Gasparotto
## Last update Sat Jun 11 16:05:46 2016 Quentin Gasparotto
##

NAME		=	zappy_ai

CC		=	g++

RM		=	rm -rf

SRCDIR		=	./src/
INCDIR		=	./include/
LIBDIR		=	./lib/

NETDIR		=	$(LIBDIR)network/
NETINC		=	$(NETDIR)include/

LUADIR		=	$(LIBDIR)luawrap/
LUAINC		=	$(LUADIR)include/
LUALIBINC	=	$(LUADIR)lua-5.3.2/src/

SRCS		=	Core.cpp		\
			IAClient.cpp		\
			ZappyData.cpp		\
			ZappyRequest.cpp    \
			Inventory.cpp       \
			Vector2.cpp         \
			ZappyMap.cpp        \
			ObjectArray.cpp     \
			main.cpp

OBJS		=	$(addprefix $(SRCDIR), $(SRCS:.cpp=.o))

CPPFLAGS	=	-Wall -Wextra -W
CPPFLAGS	+=	-I$(INCDIR) -I$(NETINC) -I$(LUAINC) -I$(LUALIBINC)
CPPFLAGS	+=	-std=c++1y

LDFLAGS		=	-L$(NETDIR) -lnetwork -L$(LUADIR) -lluawrapper

WINDIR      =   ./win/

WINLIB      =   $(WINDIR)winlib.zip

DLLS        =   $(WINDIR)libgcc_s_dw2-1.dll  \
                $(WINDIR)libstdc++-6.dll     \
                $(WINDIR)libwinpthread-1.dll \
                $(WINDIR)lua53.dll

ifeq ($(OS),Windows_NT)
    NAME    =  $(WINDIR)zappy_ai.exe
    LDFLAGS += $(WINDIR)lua53.dll -lws2_32
else
    LDFLAGS += -ldl
endif

DEBUG		=	no

ifeq	($(DEBUG),yes)
	CPPFLAGS += -g
endif

$(NAME):	$(DLLS) $(OBJS)
	$(CC) -o $(NAME) $(OBJS) $(LDFLAGS)

$(DLLS):
	@unzip -q -o $(WINLIB) -d $(WINDIR)
	@echo -e "\n[===\e[33mCompiling Network library\e[0m===]"
	@make -C $(NETDIR)
	@echo -e "[===\e[32mDone\e[0m===]\n"
	@echo -e "\n[===\e[33mCompiling Lua Wrapper library\e[0m===]"
	@make -C $(LUADIR)
	@echo -e "[===\e[32mDone\e[0m===]\n"

all:	$(NAME)

clean:
	@echo -e "\n[===\e[35mCleaning Network library\e[0m===]"
	@make clean -C $(NETDIR)
	@echo -e "[===\e[31mDone\e[0m===]\n"
	@echo -e "\n[===\e[35mCleaning Lua Wrapper library\e[0m===]"
	@make clean -C $(LUADIR)
	@echo -e "[===\e[31mDone\e[0m===]\n"
	$(RM) $(OBJS)
	$(RM) $(DLLS)

fclean:	clean
	@echo -e "\n[===\e[35mFCleaning Network library\e[0m===]"
	@make fclean -C $(NETDIR)
	@echo -e "[===\e[31mDone\e[0m===]\n"
	@echo -e "\n[===\e[35mFCleaning Lua Wrapper library\e[0m===]"
	@make fclean -C $(LUADIR)
	@echo -e "[===\e[31mDone\e[0m===]\n"
	$(RM) $(NAME)

re:	fclean all

.PHONY:	all clean fclean re
