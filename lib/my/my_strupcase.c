/*
** my_strupcase.c for my_strupcase.c in /home/cedric/delivery/CPool_Day06
** 
** Made by Cédric Thomas
** Login   <cedric@epitech.net>
** 
** Started on  Mon Oct 10 15:51:30 2016 Cédric Thomas
** Last update Mon Oct 10 16:02:05 2016 Cédric Thomas
*/

#include <unistd.h>

char	*my_strupcase(char *str)
{
  int	i;

  i = 0;
  if (str == NULL)
    return (NULL);
  while (str[i] != 0)
    {
      if (str[i] <= 'z' && str[i] >= 'a')
	str[i] -= 32;
      i += 1;
    }
  return (str);
}
