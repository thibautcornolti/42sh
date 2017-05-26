/*
** my_strncat.c for my_strncat.c in /home/cedric/delivery/CPool_Day07
** 
** Made by Cédric Thomas
** Login   <cedric@epitech.net>
** 
** Started on  Tue Oct 11 16:19:26 2016 Cédric Thomas
** Last update Fri Nov 18 08:56:04 2016 Cédric Thomas
*/
#include "my.h"

char	*my_strncat(char *dest, char *src, int n)
{
  int	i;
  int	j;

  i = 0;
  j = 0;
  if (n < 0)
    {
      my_strcat(dest, src);
      return (dest);
    }
  while (dest[i] != '\0')
    i += 1;
  while (j < n)
    {
      dest[i + j] = src[j];
      j += 1;
    }
  dest[i + j] = '\0';
  return (dest);
}
