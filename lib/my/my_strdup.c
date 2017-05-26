/*
** my_strdup.c for CPool_Day08 in /home/cedric/delivery/CPool_Day08
** 
** Made by Cédric Thomas
** Login   <cedric@epitech.net>
** 
** Started on  Wed Oct 12 09:38:43 2016 Cédric Thomas
** Last update Tue Nov 29 16:04:52 2016 Cédric Thomas
*/
#include <stdlib.h>
#include "my.h"

char	*my_strdup(char *src)
{
  char	*dest;
  int	i;

  i = 0;
  if (src == NULL)
    return (NULL);
  dest = malloc(sizeof(char) * (my_strlen(src) + 1));
  if (dest == NULL)
    return (NULL);
  while (src[i] != '\0')
    {
      dest[i] = src[i];
      i += 1;
    }
  dest[i] = '\0';
  return (dest);
}
