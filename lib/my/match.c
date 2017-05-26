/*
** match.c for CPool_matchnmatch in /home/cedric/delivery/matchnmatch
** 
** Made by Cédric Thomas
** Login   <cedric@epitech.net>
** 
** Started on  Thu Oct 13 23:20:58 2016 Cédric Thomas
** Last update Fri May 12 16:51:02 2017 Thibaut Cornolti
*/
#include <stdlib.h>
#include "my.h"

int		match(char *s1, char *s2)
{
  if (*s1 == '\0' && (*s2 == '\0' || (*s2 == '*' && *(s2 + 1) == '\0')))
    return (1);
  if (*s2 == '*' && *s1 != '\0')
    return (match(s1 + 1, s2) || match(s1, s2 + 1));
  else if (*s2 == '*' && *s1 == '\0')
    return (match(s1, s2 + 1));
  if (*s1 == *s2)
    return (match(s1 + 1, s2 + 1));
  else
    return (0);
}

static int	match_counter(char *pattern)
{
  int		i;
  int		j;
  int		bool;

  j = 0;
  i = -1;
  bool = 0;
  while (pattern[++i])
    if (pattern[i] == '*' && !bool)
      {
	j += 1;
	bool = 1;
      }
    else if (pattern[i] != '*')
      bool = 0;
  return (j);
}

static void	search_pattern(int *idx_str, int *idx_pattern,
			       char *str, char *pattern)
{
  while (pattern[*idx_pattern] != '*' && pattern[*idx_pattern]
	 && str[*idx_str])
    {
      *idx_str += 1;
      *idx_pattern += 1;
    }
  while (pattern[*idx_pattern] == '*' && pattern[*idx_pattern])
    *idx_pattern += 1;
}

static char	*cpy_matcher(int *idx_str, int *idx_pattern,
			       char *str, char *pattern)
{
  char		*matched;
  int		save;

  save = *idx_str;
  while (str[*idx_str] && !match(str + *idx_str, pattern + *idx_pattern))
    *idx_str += 1;
  matched = my_strndup(str + save, *idx_str - save);
  return (matched);
}

char	**extract_match(char *str, char *pattern)
{
  int	index;
  int	i;
  int	j;
  char	**tab;
  int	len;

  if (str == NULL || pattern == NULL || !match(str, pattern))
    return (NULL);
  len = match_counter(pattern);
  if ((tab = malloc(sizeof(char *) * (len + 1))) == NULL)
    return (NULL);
  i = 0;
  j = 0;
  index = 0;
  while (index != len)
    {
      search_pattern(&i, &j, str, pattern);
      if ((tab[index] = cpy_matcher(&i, &j, str, pattern)) == NULL)
	return (NULL);
      index += 1;
    }
  tab[len] = NULL;
  return (tab);
}
