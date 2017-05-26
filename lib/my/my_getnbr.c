/*
** my_getnbr.c for my_getnbr.c in /home/cedric/delivery/CPool_Day04
** 
** Made by Cédric Thomas
** Login   <cedric@epitech.net>
** 
** Started on  Thu Oct  6 17:50:16 2016 Cédric Thomas
** Last update Sun Oct 16 19:02:18 2016 Cédric Thomas
*/

#include <stdlib.h>

static int	b_int(long nb)
{
  if (nb < -2147483648 || nb > 2147483647)
    {
      return (0);
    }
  else
    {
      return (1);
    }
}

int	my_getnbr(char *str)
{
  long	nb;
  int	i;
  int	sign;
  int	bool;

  nb = 0;
  i = 0;
  sign = 1;
  bool = 1;
  if (str == NULL)
    return (0);
  while (str[i] && (str[i] == '+' || str[i] == '-'))
    {
      ((str[i] == '-') ? (sign *= -1) : (sign *=  1));
      i+=1;
    }
  while (str[i] != '\0' && bool == 1)
    {
      if (str[i] >= '0' && str[i] <= '9')
	nb = nb * 10 + str[i] - 48;
      i +=1;
      if (str[i] < '0' || str[i] > '9')
	bool = 0;
    }
  return (b_int(nb) ? nb * sign : 0);
}
