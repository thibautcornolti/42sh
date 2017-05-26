/*
** my_showstr.c for my_showstr.c in /home/cedric/delivery/CPool_Day06
** 
** Made by Cédric Thomas
** Login   <cedric@epitech.net>
** 
** Started on  Tue Oct 11 14:06:56 2016 Cédric Thomas
** Last update Fri Nov 18 08:55:01 2016 Cédric Thomas
*/
#include "my.h"

static int	my_put_base(int nb, char *base)
{
  long		rnb;
  int		i;

  rnb = nb;
  i = 0;
  while (base[i] != '\0')
    i += 1;
  if (rnb < 0)
    {
      my_putchar(45);
      rnb = rnb * -1;
    }
  if (rnb / i > 0)
    my_put_base(rnb / i, base);
  my_putchar(base[rnb % i]);
  return (0);
}

int	my_showstr(char *str)
{
  int	i;

  i = 0;
  while (str[i] != 0)
    {
      if (str[i] < 32 || str[i] > 126)
	{
	  my_putchar('\\');
	  if (str[i] < 16)
	    my_putchar('0');
	  my_put_base(str[i], "0123456789abcdef");
	}
      else
	{
	  my_putchar(str[i]);
	}
      i += 1;
    }
  return (0);
}
