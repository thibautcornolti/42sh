/*
** str.c for asm in /home/cedric/delivery/CPE/CPE_2016_corewar/asm
** 
** Made by 
** Login   <cedric.thomas@epitech.eu>
** 
** Started on  Wed Mar  1 15:05:53 2017 
** Last update Fri May 12 16:00:23 2017 Thibaut Cornolti
*/
#include <stdlib.h>
#include "my.h"

int	my_cstrlen(char *str, char c)
{
  int	i;

  i = -1;
  if (str == NULL)
    return (-1);
  while (str[++i] && str[i] != c);
  return (i);
}

int	my_strstrlen(char *str, char *c)
{
  int	i;

  i = -1;
  if (str == NULL || c == NULL)
    return (-1);
  while (str[++i] && !is_in(str[i], c));
  return (i);
}

char	*my_strndup(char *str, int len)
{
  char	*dup;
  int	i;

  i = -1;
  if (str == NULL)
    return (NULL);
  if ((dup = malloc(sizeof(char) * len + 1)) == NULL)
    return (NULL);
  while (str[++i] && i < len)
    dup[i] = str[i];
  dup[i] = 0;
  return (dup);
}

int	composed_of(char *str, char *only_composed)
{
  int	i;

  i = -1;
  while (str[++i])
    {
      if (!is_in(str[i], only_composed))
	return (0);
    }
  return (1);
}
