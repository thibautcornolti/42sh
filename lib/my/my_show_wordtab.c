/*
** my_show_wordtab.c for CPool_Day08 in /home/cedric/delivery/CPool_Day08/task03
** 
** Made by Cédric Thomas
** Login   <cedric@epitech.net>
** 
** Started on  Wed Oct 12 11:57:25 2016 Cédric Thomas
** Last update Fri Nov 18 08:55:20 2016 Cédric Thomas
*/
#include <stdlib.h>
#include "my.h"

int	my_show_wordtab(char **tab)
{
  int	i;
  int	j;

  i = 0;
  j = 0;
  if (tab == NULL)
    return (0);
  while (tab[i] != 0)
    {
      j = 0;
      while (tab[i][j] != '\0')
	{
	  if (tab[i] != NULL)
	    my_putchar(tab[i][j]);
	  j += 1;
	}
      my_putchar('\n');
      i += 1;
    }
  return (0);
}
