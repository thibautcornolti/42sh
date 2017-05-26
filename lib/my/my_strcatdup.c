/*
** my_strcatdup.c for my_strcatdup.c in /home/cedric/delivery/CPool_Day12/grep
** 
** Made by Cédric Thomas
** Login   <cedric@epitech.net>
** 
** Started on  Tue Oct 18 15:24:12 2016 Cédric Thomas
** Last update Fri May 12 16:53:50 2017 Thibaut Cornolti
*/

#include <stdlib.h>
#include "my.h"

char	*my_strcatdup(char *s1, char *s2, int freeval)
{
  int   i;
  char	*dest;
  int	len;

  i = -1;
  if (s2 == NULL)
    return (s1);
  len = 0;
  if (s1 != NULL)
    len = my_strlen(s1);
  if ((dest = malloc(sizeof(char) * (len + my_strlen(s2) + 1))) == NULL)
    return (NULL);
  while (++i <  (len + my_strlen(s2)))
    {
      if (i < len)
	dest[i] = s1[i];
      else
	dest[i] = s2[i - len];
    }
  dest[i] = '\0';
  if (freeval == 1 || freeval == 3)
    free(s1);
  if (freeval == 2 || freeval == 3)
    free(s2);
  return (dest);
}
