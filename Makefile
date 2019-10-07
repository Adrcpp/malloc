##
## Makefile for my_slack in /home/adrien/PISCINE/my_slack/src/client
##
## Made by CESARO Adrien
## Login   <cesaro_a@etna-alternance.net>
##
## Started on  Wed Apr 26 13:54:00 2017 CESARO Adrien
## Last update Wed Apr 26 14:15:30 2017 CESARO Adrien
##

CC       =   gcc

CFLAGS   = 	-Wall -Wextra -Werror -g -I./header/ -fPIC -lm

FLAGTEST =  -g -w -I./header/ -fPIC -lm

LDFLAGS =	-shared

NAME    =	libmy_malloc_$(shell uname).so

LNAME   =   libmy_malloc.so

OBJ     =   $(SRC:%.c=%.o)

OBJ2    =   $(SRC2:%.c=%.o)

SRC     =	malloc.c

SRC2    =	tests/unit_test.c \
 			malloc.c

$(NAME):
			$(CC)  $(CFLAGS) -DDEBUG=0 $(LDFLAGS) -o $(NAME) $(SRC)
			ln -s $(shell pwd)/$(NAME) $(LNAME)

all:     	$(NAME)

test:
			$(CC) $(FLAGTEST) -DDEBUG=1 -o  test_malloc $(SRC2)

debug:
			$(CC) $(CFLAGS)	-DDEBUG=1 $(LDFLAGS) -o $(NAME) $(SRC)
			ln -s $(shell pwd)/$(NAME) $(LNAME)

clean:
			$(RM) $(OBJ) $(OBJ2)

fclean	:	clean
		    $(RM) $(NAME) $(LNAME)

re:			fclean all

.PHONY:		all
