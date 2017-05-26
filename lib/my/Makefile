##
## Makefile for CPool_Day10 in /home/cedric/delivery/CPool_Day10/lib/my
## 
## Made by Cédric Thomas
## Login   <cedric@epitech.net>
## 
## Started on  Fri Oct 14 09:33:10 2016 Cédric Thomas
## Last update Sun Apr 16 13:57:11 2017 
##

SRC	=	is_betw.c		\
		my_puterror.c		\
		free_tab.c		\
		is_nb.c			\
		is_in.c			\
		my_find_prime_sup.c	\
		my_memset.c		\
		my_getnbr.c		\
		my_isneg.c		\
		my_is_prime.c		\
		my_power_rec.c		\
		my_putchar.c		\
		my_put_nbr.c		\
		my_putstr.c		\
		my_revstr.c		\
		my_showmem.c		\
		my_showstr.c		\
		my_show_wordtab.c	\
		my_sort_int_tab.c	\
		my_split.c		\
		my_square_root.c	\
		my_strcapitalize.c	\
		my_strcat.c		\
		my_strcmp.c		\
		my_strcpy.c		\
		my_strdup.c		\
		my_str_isalpha.c	\
		my_str_islower.c	\
		my_str_isnum.c		\
		my_str_isprintable.c	\
		my_str_isupper.c	\
		my_strlen.c		\
		my_strlowcase.c		\
		my_strncat.c		\
		my_strncmp.c		\
		my_strncpy.c		\
		my_strstr.c		\
		my_str_to_wordtab.c	\
		my_strupcase.c		\
		my_strcatdup.c		\
		convert_base.c		\
		str.c			\
		match.c			\
		my_swap.c

OBJ	=	$(SRC:.c=.o)

INCLUDE =	my.h

NAME	=	libmy.a

all:	$(NAME)

$(NAME):	$(OBJ)
	ar rc $(NAME) $(OBJ)
	cp my.h ../../include
	cp $(NAME) ..
clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re:	fclean all
