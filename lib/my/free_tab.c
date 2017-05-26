/*
** free_tab.c for free_tab in /home/cedric/delivery/MUL/wireframe
** 
** Made by Cédric Thomas
** Login   <cedric@epitech.net>
** 
** Started on  Mon Nov 21 09:10:01 2016 Cédric Thomas
** Last update Fri Jan  6 16:16:21 2017 
*/
#include <stdlib.h>
#include "my.h"

void	free_tab(char **tab)
{
  int	i;

  i = 0;
  if (tab == NULL)
    return ;
  while (tab[i])
    {
      free(tab[i]);
      i += 1;
    }
  free(tab);
}
