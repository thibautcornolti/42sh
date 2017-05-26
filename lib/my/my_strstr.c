/*
** my_strstr.c for my_strstr.c in /home/cedric/delivery/CPool_Day06
** 
** Made by Cédric Thomas
** Login   <cedric@epitech.net>
** 
** Started on  Mon Oct 10 12:00:59 2016 Cédric Thomas
** Last update Fri Nov 18 08:59:55 2016 Cédric Thomas
*/
#include <stdlib.h>
#include "my.h"

char	*my_strstr(char *str, char *to_find)
{
  int	i;
  int	j;
  int	s_len;

  i = 0;
  s_len = my_strlen(str);
  if (my_strlen(to_find) == 0)
    return (str);
  while (str[i] != '\0')
    {
      if (str[i] == to_find[0])
	{
	  j = 0;
	  while (i + j < s_len && str[j + i] != '\0' && str[i + j] == to_find[j])
	    {
	      if (to_find[j + 1] == '\0')
		{
		  return (&(str[i]));
		}
	      j += 1;
	    }
	}
      i += 1;
    }
  return (NULL);
}
