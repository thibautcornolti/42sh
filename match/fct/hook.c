/*
** star.c for match in /home/cedric/delivery/extract_match
** 
** Made by 
** Login   <cedric.thomas@epitech.eu>
** 
** Started on  Mon Apr 24 09:50:10 2017 
** Last update Mon Apr 24 20:30:56 2017 
*/
#include <stdlib.h>
#include "match.h"
#include "my.h"

static int	len_to_hook(char *str)
{
  int		stack;
  int		i;

  if (str == NULL || str[0] != '[')
    return (-1);
  i = 0;
  stack = 0;
  while (str[i] && str[i] != ']' && (str[i] == '[' || stack))
    {
      if (str[i] == '[')
	stack += 1;
      i += 1;
      if (str[i] == ']')
	stack -= 1;
    }
  while (str[i] == ']')
    i += 1;
  if (str[i] == 0 && stack != 0)
    return (-1);
  return (i);
}

static int	cmp(char **s1, char *first, char *sec)
{
  if (my_strlen(sec) == 1 && my_strlen(first) == 1)
    {
      if (is_betw(*first, **s1, *sec))
	return (0);
      else
	return (-1);
    }
  return (-1);
}

int	hook(char **s1, char **s2)
{
  char	*first;
  char	*sec;
  int	ret;
  int	len;
  int	separator;

  if ((len = len_to_hook(*s2)) < 0)
    return (0);
  *s2 += 1;
  separator = my_cstrlen(*s2, '-');
  if ((first = my_strndup(*s2, separator)) == NULL)
    return (-1);
  if ((sec = my_strndup(*s2 + separator + 1, len - separator - 3)) == NULL)
    return (-1);
  ret = cmp(s1, first, sec);
  if (ret == 0)
    {
      *s1 += 1;
      *s2 += len - 1;
    }
  return (advanced_match(*s1, *s2));
}
