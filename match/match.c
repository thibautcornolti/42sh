/*
** match.c for CPool_matchnmatch in /home/cedric/delivery/matchnmatch
** 
** Made by Cédric Thomas
** Login   <cedric@epitech.net>
** 
** Started on  Thu Oct 13 23:20:58 2016 Cédric Thomas
** Last update Sat May 20 19:48:09 2017 Thibaut Cornolti
*/
#include <stdlib.h>
#include "my.h"
#include "match.h"

static const t_pattern	my_pat[NB_PATTERN] =
  {
    {'#', &inib},
    {'(', &parent},
    {'*', &star},
    {'<', &amp},
    {'?', &inter},
    {'{', &braquet},
    {'[', &hook},
    {'\\', &escape}
  };

static int	pattern_matcher(char **s1, char **s2)
{
  int		i;

  i = -1;
  while (++i < NB_PATTERN)
    {
      if (my_pat[i].pattern ==  **s2)
	return (my_pat[i].fct(s1, s2));
    }
  return (0);
}

int	advanced_match(char *s1, char *s2)
{
  int	value;

  if (*s1 == '\0' && *s2 == '\0')
    return (1);
  if ((value = pattern_matcher(&s1, &s2)) > 0)
    return (1);
  if (value < 0)
    return (0);
  if (*s1 == '\0' && *s2 == '\0')
    return (1);
  if (*s1 == *s2)
    return (advanced_match(s1 + 1, s2 + 1));
  else
    return (0);
}
