/*
** my_putnbr_base.c for my_putnbr_base.c in /home/cedric/delivery/CPool_Day06
** 
** Made by Cédric Thomas
** Login   <cedric@epitech.net>
** 
** Started on  Mon Oct 10 18:21:39 2016 Cédric Thomas
** Last update Tue Mar  7 01:08:34 2017 
*/
#include <stdlib.h>
#include <unistd.h>
#include "my_alloc.h"

char	*my_astrdup(char *src)
{
  char	*dest;
  int	i;

  i = -1;
  if (src == NULL)
    return (NULL);
  while (src[++i]);
  dest = malloc(sizeof(char) * (i + 1));
  if (dest == NULL)
    return (NULL);
  i = 0;
  while (src[i] != '\0')
    {
      dest[i] = src[i];
      i += 1;
    }
  dest[i] = '\0';
  return (dest);
}

int	my_astrcmp(char *s1, char *s2)
{
  int	i;

  i = 0;
  if (s1 == NULL && s2 == NULL)
    return (0);
  else if (s1 == NULL || s2 == NULL)
    return (1);
  while (s1[i] != '\0' || s2[i] != '\0')
    {
      if (s1[i] != s2[i])
	{
	  return (s1[i] - s2[i] < 0 ? -1 : 1);
	}
      i += 1;
    }
  return (0);
}

void	aputchar(char c)
{
  write(1, &c, 1);
}

static void	put_core(long nb, char *base, int size)
{
  if (nb / size > 0)
    put_core(nb / size, base, size);
  aputchar(base[nb % size]);
}

int		my_put_apointer(void *addr, char *base)
{
  long		rnb;
  int		i;
  t_point	nb;

  nb.point = addr;
  i = 0;
  rnb = nb.addr;
  while (base[i] != '\0')
      i += 1;
  if (rnb < 0)
    {
      aputchar(45);
      rnb = rnb * -1;
    }
  put_core(rnb, base, i);
  return (0);
}
