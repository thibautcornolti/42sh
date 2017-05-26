/*
** my_put_nbr.c for my_put_nbr.c in /home/cedric/delivery/CPool_Day03/Complete_src
** 
** Made by Cédric Thomas
** Login   <cedric.thomas@epitech.net>
** 
** Started on  Wed Oct  5 14:25:45 2016 Cédric Thomas
** Last update Fri Nov 18 08:51:36 2016 Cédric Thomas
*/
#include "my.h"

static long	get_size(long nbr)
{
  long		i;

  i = 1;
  if (nbr < 0)
    {
      nbr = -nbr;
    }
  while (nbr >=  i)
    {
      i = i * 10;
    }
  if (i > 1)
    {
      i = i / 10;
    }
  return (i);
}

int	my_put_nbr(int nbr)
{
  long	size;
  long	buffer;

  buffer = nbr;
  size = get_size(buffer);
  if (nbr < 0)
    {
      my_putchar('-');
      buffer = -buffer;
    }
  while (size != -1)
    {
      my_putchar((buffer - buffer % size) / size + 48);
      buffer = buffer % size;
      if (size > 1)
	{
	  size = size / 10;
	}
      else
	{
	  size = -1;
	}
    }
  return (0);
}
