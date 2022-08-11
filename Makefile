
INC=%%%%

INCLIB=$(INC)/../lib

UNAME := $(shell uname)

CFLAGS= -I$(INC) -O3 -I.. -g

NAME= so_long
SRC = sources/so_long.c sources/get_next_line.c sources/get_next_line_utils.c sources/map.c sources/jeu.c sources/check.c sources/destroy.c sources/utils.c

OBJ = $(SRC:%.c=%.o)

LFLAGS = -L.. -lmlx -L$(INCLIB) -lXext -lX11 -lm -Wall -Wextra

ifeq ($(UNAME), Darwin)
	# mac
	CC = clang
else ifeq ($(UNAME), FreeBSD)
	# FreeBSD
	CC = clang
else
	#Linux and others...
	CC	= gcc
	LFLAGS += -lbsd
endif

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) -o $(NAME) $(OBJ) $(LFLAGS)

show:
	@printf "UNAME		: $(UNAME)\n"
	@printf "NAME  		: $(NAME)\n"
	@printf "CC		: $(CC)\n"
	@printf "CFLAGS		: $(CFLAGS)\n"
	@printf "LFLAGS		: $(LFLAGS)\n"
	@printf "SRC		:\n	$(SRC)\n"
	@printf "OBJ		:\n	$(OBJ)\n"

clean:
	rm -f $(NAME) $(OBJ) *~ core *.core

re: clean all
