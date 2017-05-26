/*
** input_lexer.c for parser in /home/cedric/Desktop/parseur 42/parse/error
** 
** Made by Cédric THOMAS
** Login   <cedric.thomas@epitech.eu>
** 
** Started on  Sun Apr 30 20:11:56 2017 
** Last update Fri May 19 16:59:34 2017 Thibaut Cornolti
*/
#include <unistd.h>
#include <stdlib.h>
#include "syntax.h"
#include "my.h"

static int	checkdouble(char *str)
{
  int		i;
  char		quote;

  i = -1;
  quote = 0;
  while (str && str[++i])
    if ((quote == 0 &&
	 (is_in(str[i], INIB) || is_in(str[i], BACKQUOTE))) ||
	str[i] == quote)
      quote = (!quote ? str[i] : 0);
  if (quote)
    {
      my_puterror("Unmatched ");
      write(2, &quote, 1);
      my_puterror(".\n");
    }
  return (quote ? 1 : 0);
}

int		check_input_lexer(char *str)
{
  if (str == NULL)
    return (1);
  if (checkdouble(str))
    return (1);
  return (0);
}
