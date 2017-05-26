/*
** my_isneg.c for my_isneg.c in /home/cedric/delivery/CPool_Day03/Complete_src
** 
** Made by Cédric Thomas
** Login   <cedric.thomas@epitech.net>
** 
** Started on  Wed Oct  5 12:01:03 2016 Cédric Thomas
** Last update Fri Nov 18 08:50:41 2016 Cédric Thomas
*/
#include "my.h"

int	my_isneg(int n)
{
  if (n < 0)
    {
      my_putchar('N');
    }
  else
    {
      my_putchar('P');
    }
  return (0);
}
