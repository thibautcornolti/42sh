/*
** amp.c for match in /home/cedric/delivery/extract_match
** 
** Made by Cédric THOMAS
** Login   <cedric.thomas@epitech.eu>
** 
** Started on  Mon May  1 18:48:43 2017 
** Last update Mon May  1 19:26:22 2017 
*/
#include <stdlib.h>
#include "match.h"
#include "my.h"

int	amp(char **s1, char **s2)
{
  char	*format;
  int	ret;
  int	len;

  len = my_cstrlen(*s2, '>');
  format = my_strndup(*s2 + 1, len - 1);
  change_star_delim(format);
  ret = advanced_match(*s1, *s2 + len + 1);
  free(format);
  change_star_delim(NULL);
  return (ret);
}
