##
## Makefile for CPool_Day10 in /home/cedric/delivery/CPool_Day10/lib/my
## 
## Made by Cédric Thomas
## Login   <cedric@epitech.net>
## 
## Started on  Fri Oct 14 09:33:10 2016 Cédric Thomas
## Last update Sun May 21 18:12:16 2017 Thibaut Cornolti
##

SRC	=	my_alloc.c	\
		misc.c		\
		print.c		\
		alloc_list.c	\
		alloc_misc.c

OBJ	=	$(SRC:.c=.o)

INCLUDE =	my_alloc.h

NAME	=	liballoc.a

all:	$(NAME)

$(NAME):	$(OBJ)
	ar rc $(NAME) $(OBJ)
	cp my_alloc.h ../../include
	cp $(NAME) ..

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re:	fclean all
