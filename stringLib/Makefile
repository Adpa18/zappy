##
## Makefile for MAKEFILE in /home/gouet_v/Rendu/semester4/PSU/PSU_2015_myftp
## 
## Made by Victor Gouet
## Login   <gouet_v@epitech.net>
## 
## Started on  Mon May  2 10:16:12 2016 Victor Gouet
## Last update Mon Jun  6 21:48:53 2016 Victor Gouet
##

CC		= gcc

RM		= rm -f

LIBNAME		= libstringLib.a

LIBS		= on_flag_bounded.c \
		  on_flag_reverse.c \
		  on_flag_strings.c \
		  controller_flags.c \
		  on_flag_char.c \
		  on_flags_bits.c \
		  storage.c \
		  counts_size_bytes.c \
		  on_flag_integer.c \
		  on_flags_less.c \

OBJSLIB		= $(LIBS:.c=.o)

CFLAGS		=  -Wall -Wextra -W -I ./

$(LIBNAME):	$(OBJSLIB)
		ar rc $(LIBNAME) $(OBJSLIB)
		ranlib $(LIBNAME)

all:		$(LIBNAME)

clean:
		$(RM) $(OBJSLIB)

fclean:		clean
		$(RM) $(LIBNAME)

re:		fclean all

.PHONY:		all clean fclean re client
