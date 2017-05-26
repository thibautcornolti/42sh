/*
** star.c for match in /home/cedric/delivery/extract_match
** 
** Made by 
** Login   <cedric.thomas@epitech.eu>
** 
** Started on  Mon Apr 24 09:50:10 2017 
** Last update Fri Apr 28 14:14:06 2017 
*/
#include <stdlib.h>
#include "match.h"
#include "my.h"

static int	len_to_braquet(char *str)
{
  int		stack;
  int		i;

  if (str == NULL)
    return (-1);
  i = 0;
  stack = 1;
  while (str[i] && stack)
    {
      if (str[i] == '{')
	stack += 1;
      if (str[i] == '}')
	stack -= 1;
      i += 1;
    }
  if (str[i] == 0 && stack != 0)
    return (-1);
  return (i);
}

static int	len_to_arg(char *str)
{
  int		stack;
  int		i;

  if (str == NULL)
    return (-1);
  i = 0;
  stack = 0;
  while (str[i] && ((str[i] != ',' && str[i] != '}') || stack))
    {
      if (str[i] == '{')
	stack += 1;
      if (str[i] == '}')
	stack -= 1;
      i += 1;
    }
  return (i);
}

static int	auto_cmp(char *s1, char *s2, char *pattern_end)
{
  int		len;
  int		ret;
  char		*pattern;

  ret = -1;
  while (ret < 0 && *s2 && *(s2 - 1) != '}')
    {
      if ((len = len_to_arg(s2)) < 0)
	return (-1);
      if ((pattern = my_strndup(s2, len)) == NULL)
	return (-1);
      if ((pattern = my_strcatdup(pattern, pattern_end, 1)) == NULL)
	return (-1);
      if (advanced_match(s1, pattern))
	ret = 1;
      s2 += len + 1;
      free(pattern);
    }
  return (ret);
}

int	braquet(char **s1, char **s2)
{
  int	len;
  int	pattern;

  *s2 += 1;
  if ((len = len_to_braquet(*s2)) < 0)
    return (0);
  if ((pattern = auto_cmp(*s1, *s2, *s2 + len)) > 0)
    return (1);
  return (-1);
}
