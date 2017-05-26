/*
** str.c for my_printf in /home/cedric/delivery/my_printf/misc
** 
** Made by Cédric Thomas
** Login   <cedric@epitech.net>
** 
** Started on  Sat Nov 12 08:33:22 2016 Cédric Thomas
** Last update Mon Nov 28 21:37:13 2016 Cédric Thomas
*/
#include <stdlib.h>
#include "my.h"
#include "my_printf.h"

int	getindex(char c, char *str)
{
  int           i;

  i = 0;
  while (str[i])
    {
      if (str[i] == c)
	return (i);
      i += 1;
    }
  return (-1);
}

int	strcmp_i(char *s1, char *s2)
{
  int	i;

  i = 0;
  while (s1[i] != '\0' || s2[i] != '\0')
    {
      if (s1[i] != s2[i])
	  return (s1[i] - s2[i] < 0 ? -1 : 1);
      i += 1;
    }
  return (0);
}
