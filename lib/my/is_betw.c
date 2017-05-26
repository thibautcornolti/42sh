/*
** is_betw.c for is_betw in /home/cedric/lib/lib/my
** 
** Made by Cédric Thomas
** Login   <cedric@epitech.net>
** 
** Started on  Sun Dec 18 14:18:25 2016 Cédric Thomas
** Last update Sun Dec 18 14:25:41 2016 Cédric Thomas
*/
#include "my.h"

int	is_betwr(int a, int nb, int b)
{
  if (a <= nb && b >= nb)
    return (nb);
  else
    {
      if (nb < a)
	return (a);
      else
        return (b);
    }
}

int	is_betw(int a, int nb, int b)
{
  if (a <= nb && b >= nb)
    return (1);
  return (0);
}
