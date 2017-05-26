/*
** convert.c for my_printf in /home/cedric/delivery/my_printf
** 
** Made by Cédric Thomas
** Login   <cedric@epitech.net>
** 
** Started on  Sun Nov 13 17:21:27 2016 Cédric Thomas
** Last update Sun May 21 17:41:05 2017 Thibaut Cornolti
*/
#include <stdlib.h>
#include "my.h"

static char	*convert_core(long long nb, char *base,
			      int index, char *str)
{
  int	modulo;

  if (nb / my_strlen(base) != 0)
    str = convert_core(nb / my_strlen(base), base, index + 1, str);
  else
    {
      str = malloc(sizeof(char) * (index + 2));
      str[index + 1] = '\0';
    }
  if (nb % my_strlen(base) < 0)
    modulo = -(nb % my_strlen(base));
  else
    modulo = nb % my_strlen(base);
  str[index] = base[modulo];
  return (str);
}

char	*convertbase(long long nb, char *base)
{
  char	*converted;
  char	temp;
  int	start;
  int	i;
  int	j;

  start = 0;
  temp = 0;
  if (nb < 0)
    start = 1;
  i = start;
  converted = convert_core(nb, base, start, converted);
  if (nb < 0)
    converted[0] = '-';
  j = my_strlen(converted) - 1;
  while (j > i && j > start)
    {
      temp = converted[i];
      converted[i] = converted[j];
      converted[j] = temp;
      i += 1;
      j -= 1;
    }
  return (converted);
}

static char	*convert_coreu(unsigned long long nb,
			       char *base, int index, char *str)
{
  int	modulo;

  if (nb / my_strlen(base) != 0)
    str = convert_core(nb / my_strlen(base), base, index + 1, str);
  else
    {
      str = malloc(sizeof(char) * (index + 2));
      str[index + 1] = '\0';
    }
  if (nb % my_strlen(base) < 0)
    modulo = -(nb % my_strlen(base));
  else
    modulo = nb % my_strlen(base);
  str[index] = base[modulo];
  return (str);
}

char	*u_convertbase(unsigned long long nb, char *base)
{
  char	*converted;
  char	temp;
  int	start;
  int	i;
  int	j;

  start = 0;
  temp = 0;
  if (nb < 0)
    start = 1;
  i = start;
  converted = convert_coreu(nb, base, start, converted);
  if (nb < 0)
    converted[0] = '-';
  j = my_strlen(converted) - 1;
  while (j > i && j > start)
    {
      temp = converted[i];
      converted[i] = converted[j];
      converted[j] = temp;
      i += 1;
      j -= 1;
    }
  return (converted);
}
