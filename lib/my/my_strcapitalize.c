/*
** my_strcapitalize.c for my_strcapitalize.c in /home/cedric/delivery/CPool_Day06
** 
** Made by Cédric Thomas
** Login   <cedric@epitech.net>
** 
** Started on  Mon Oct 10 16:31:16 2016 Cédric Thomas
** Last update Fri Nov 18 09:02:00 2016 Cédric Thomas
*/
#include "my.h"

char	*my_strcapitalize(char *str)
{
  int	i;

  i = 0;
  my_strlowcase(str);
  while (str[i] != 0)
    {
      if (i == 0 || (str[i - 1] < '0' || str[i - 1] > '9'))
	{
	  if (i == 0 || (str[i - 1] < 'a' || str[i - 1] > 'z'))
	    {
	      if (i == 0 || (str[i - 1] < 'A' || str[i - 1] > 'Z'))
		{
		  if (i == 0 || (str[i] >= 'a' &&
				 str[i] <= 'z' || str[i] >= 'A' && str[i] <= 'Z'))
		    str[i] -= 32;
		}
	    }
	}
      i += 1;
    }
  return (str);
}
