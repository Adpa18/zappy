##
## Makefile for MAKEFILE in /home/gouet_v/Rendu/semester4/PSU/PSU_2015_myftp
##
## Made by Victor Gouet
## Login   <gouet_v@epitech.net>
##
## Started on  Mon May  2 10:16:12 2016 Victor Gouet
## Last update Sun Jun 26 21:51:52 2016 Victor Gouet
##

CC		= gcc

RM		= rm -f

NAME		= zappy_server

NAMEAI		= zappy_ai

AIDIR		= ./src_client_ai/

SOCKETLIB	= ./socketlib/

STRINGLIB	= ./stringLib/

SRCS		= src_server/main.c \
		  src_server/command_input.c \
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
		  src_server/food_gestion.c \
		  src_server/get_trantorien.c \
		  src_server/egg_gestion.c \
		  src_server/end_of_game.c \
		  src_server/monitor_connection.c \
		  src_server/get_buffer.c \
		  src_server/remove_map.c \
		  src_server/ring_buffer.c \
		  src_server/flush_buffer.c \
		  src_server/ressources_generation.c \
		  src_server/server_running.c \
		  src_server/trantorien_connection.c \
		  src_server/Trantorien_Event/die_event.c \
		  src_server/Trantorien_Event/avance_event.c \
		  src_server/Trantorien_Event/broadcast_event.c \
		  src_server/Trantorien_Event/connect_nbr_event.c \
		  src_server/Trantorien_Event/droite_event.c \
		  src_server/Trantorien_Event/expulse_event.c \
		  src_server/Trantorien_Event/fork_event.c \
		  src_server/Trantorien_Event/gauche_event.c \
		  src_server/Trantorien_Event/incantation_event.c \
		  src_server/Trantorien_Event/incantation_func.c \
		  src_server/Trantorien_Event/inventaire_event.c \
		  src_server/Trantorien_Event/pose_obj_event.c \
		  src_server/Trantorien_Event/prend_obj_event.c \
		  src_server/Trantorien_Event/voir_event.c \
		  src_server/Monitor_event/bct.c \
		  src_server/Monitor_event/time_event.c \
		  src_server/Monitor_event/ebo.c \
		  src_server/Monitor_event/edi.c \
		  src_server/Monitor_event/eht.c \
		  src_server/Monitor_event/enw.c \
		  src_server/Monitor_event/msz.c \
		  src_server/Monitor_event/pbc.c \
		  src_server/Monitor_event/pdi.c \
		  src_server/Monitor_event/pdr.c \
		  src_server/Monitor_event/pex.c \
		  src_server/Monitor_event/pfk.c \
	 	  src_server/Monitor_event/pgt.c \
		  src_server/Monitor_event/pic.c \
		  src_server/Monitor_event/pie.c \
		  src_server/Monitor_event/pin.c \
		  src_server/Monitor_event/plv.c \
		  src_server/Monitor_event/pnw.c \
		  src_server/Monitor_event/ppo.c \
		  src_server/Monitor_event/sbp.c \
		  src_server/Monitor_event/seg.c \
		  src_server/Monitor_event/sgt.c \
		  src_server/Monitor_event/smg.c \
		  src_server/Monitor_event/suc.c \
		  src_server/Monitor_event/tna.c \
		  src_server/Monitor_event/mct.c \
		  src_server/Monitor_event/sst.c \
		  src_server/Monitor_event/send_msg_monitor.c \
		  src_server/Object/object.c \
		  src_server/Object/leaveObject.c \
		  src_server/Object/leaveObject_next.c \
		  src_server/Object/takeObject.c \
		  src_server/Object/takeObject_next.c \
		  src_server/Tools/direction.c \
		  src_server/Tools/player.c \

OBJS		= $(SRCS:.c=.o)

OBJSLIB		= $(LIBS:.c=.o)

GRAPHIC_SERVER		= no

CFLAGS      =   -W -Wall -Wextra -Werror

CFLAGS		+=  -I./include -I ./lib -I $(SOCKETLIB)include/ -I ./include_server/ -I./stringLib/

ifeq ($(GRAPHIC_SERVER),true)
	CFLAGS		+= -D GRAPHIC_SERVER=true
endif

LDFLAGS		= -L $(STRINGLIB) -lstringLib -L $(SOCKETLIB) -lmy_socket -lm

all:		$(NAME) $(NAMEAI)

$(NAME):	$(OBJS)
		make -C $(SOCKETLIB)
		make -C $(STRINGLIB)
		$(CC) -o $(NAME) $(OBJS) $(LDFLAGS)

$(NAMEAI):
	make -C $(AIDIR)
	cp $(AIDIR)$(NAMEAI) $(NAMEAI)

clean:
		$(RM) $(OBJS)
		make clean -C $(SOCKETLIB)
		make clean -C $(STRINGLIB)
		make clean -C $(AIDIR)

fclean:		clean
		$(RM) $(NAME)
		$(RM) $(NAMEAI)
		make fclean -C $(SOCKETLIB)
		make fclean -C $(STRINGLIB)
		make fclean -C $(AIDIR)

re:		fclean all

.PHONY:		all clean fclean re client
