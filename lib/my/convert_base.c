/*
** convert_base.c for CPool_Day08 in /home/cedric/delivery/ex
** 
** Made by Cédric Thomas
** Login   <cedric@epitech.net>
** 
** Started on  Fri Oct 21 15:54:31 2016 Cédric Thomas
** Last update Fri Mar 17 10:25:33 2017 
*/

#include <stdlib.h>
#include <limits.h>
#include "my.h"

static int	search(char *base, char c)
{
  int		i;

  i = 0;
  while (base[i] != c)
    i += 1;
  if (base[i] == c)
    return (i);
  return (-1);
}

static void	try_neg(int *i, char *str, int *sign)
{
  while (str[*i] == '-' || str[*i] == '+')
    {
      if (str[*i] == '-')
	*sign = *sign * -1;
      *i += 1;
    }
}

static long	go_dec(char *nbr, char *from)
{
  int		i;
  int		j;
  long		nb;
  int		sign;
  int		sh;

  i = 0;
  j = my_strlen(from);
  sign = 1;
  nb = 0;
  try_neg(&i, nbr, &sign);
  while (nbr[i] != 0)
    {
      if ((sh = search(from, nbr[i])) == -1)
	return (0);
      nb *= j;
      nb += sh;
      i += 1;
    }
  nb += nbr[i];
  return (nb * sign);
}

static char	*go_base(long dec, char *base, int len, char *futur)
{
  if (dec / my_strlen(base) > 0)
    futur = go_base(dec / my_strlen(base), base, len + 1, futur);
  else
    {
      if ((futur = malloc(sizeof(char) * (len + 2))) == NULL)
	return (NULL);
      futur[len + 1] = '\0';
      futur[len] = base[dec % my_strlen(base)];
      return (futur);
    }
  if (futur == NULL)
    return (NULL);
  futur[len] = base[dec % my_strlen(base)];
  return (futur);
}

char	*convert_base(char *nbr, char *base_from, char *base_to)
{
  char	*converted;
  int	to;
  long	dec;
  int	base;
  int	sign;

  converted = NULL;
  sign = 1;
  to = my_strlen(base_to);
  dec = go_dec(nbr, base_from);
  if (dec < 0)
    {
      dec *= -1;
      sign = -1;
    }
  converted = go_base(dec, base_to, 0, converted);
  my_revstr(converted);
  if (sign == -1)
    converted = my_strcatdup("-", converted, 0);
  free(nbr);
  return (converted);
}
