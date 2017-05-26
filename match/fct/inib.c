/*
** inhib.c for match in /home/thibrex/Dropbox/delivery/PSU/PSU_2016_42sh/parseur 42/match
** 
** Made by Thibaut Cornolti
** Login   <thibaut.cornolti@epitech.eu>
** 
** Started on  Fri May 12 16:18:54 2017 Thibaut Cornolti
** Last update Thu May 18 15:58:24 2017 Cédric THOMAS
*/

#include "match.h"
#include "my.h"
#include "syntax.h"

int		inib(char **s1, char **s2)
{
  int		i;
  char		quote;
  char		*ss1;

  ss1 = *s1;
  UNUSED(s2);
  i = -1;
  quote = 0;
  while (ss1[++i] &&
	 (quote || !is_in(ss1[i], SKIP) || (i && ss1[i - 1] == INIB_C)))
    {
      if (ss1[i] == quote || is_in(ss1[i], INIB))
	quote = (quote == 0) ? ss1[i] : 0;
    }
  if (ss1[i] == 0)
    return (1);
  return (0);
}
