/*
** is_in.c for is_in.c in /home/cedric/delivery/MUL/wireframe
** 
** Made by Cédric Thomas
** Login   <cedric@epitech.net>
** 
** Started on  Mon Nov 21 09:07:22 2016 Cédric Thomas
** Last update Mon Nov 21 09:07:41 2016 Cédric Thomas
*/
#include "my.h"

int	is_in(char c, char *str)
{
  int	i;

  i = 0;
  while (str[i])
    {
      if (str[i] == c)
	return (1);
      i += 1;
    }
  return (0);
}
