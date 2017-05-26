/*
** star.c for match in /home/cedric/delivery/extract_match
**
** Made by
** Login   <cedric.thomas@epitech.eu>
**
** Started on  Mon Apr 24 09:50:10 2017
** Last update Sun May 21 18:31:05 2017 Cédric THOMAS
*/
#include <stdlib.h>
#include "match.h"
#include "my.h"

static char	*g_delim = NULL;

void		change_star_delim(char *str)
{
  g_delim = str;
}

static int	is_in_delim(char c)
{
  if (g_delim == NULL)
    return (0);
  return (is_in(c, g_delim));
}

int		star(char **s1, char **s2)
{
  if (**s1 == '\0' && **s2 == '*' && *((*s2) + 1) == '\0')
    return (1);
  if (**s2 == '*' && **s1 != '\0' && !is_in_delim(**s1))
    return (advanced_match(*s1 + 1, *s2) || advanced_match(*s1, *s2 + 1));
  else if (**s2 == '*' && **s1 == '\0')
    return (advanced_match(*s1, *s2 + 1));
  return (0);
}
