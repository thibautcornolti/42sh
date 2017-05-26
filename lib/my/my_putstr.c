/*
** my_putstr.c for my_putstr.c in /home/cedric/delivery/CPool_Day04
** 
** Made by Cédric Thomas
** Login   <cedric@epitech.net>
** 
** Started on  Thu Oct  6 11:13:52 2016 Cédric Thomas
** Last update Fri Nov 18 08:53:27 2016 Cédric Thomas
*/
#include <unistd.h>
#include "my.h"

int	my_putstr(char *str)
{
  int	i;

  i = 0;
  if (str == NULL)
    return (0);
  while (str[i] != '\0')
    {
      my_putchar(str[i]);
      i++;
    }
  return (i);
}
