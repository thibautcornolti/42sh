/*
** quote.c for minishell2 in /home/cedric/delivery/PSU/PSU_2016_minishell2
** 
** Made by 
** Login   <cedric.thomas@epitech.eu>
** 
** Started on  Wed Mar 15 10:26:45 2017 
** Last update Sat May 20 17:24:24 2017 Cédric THOMAS
*/
#include <stdlib.h>
#include "syntax.h"
#include "my.h"

char	*delete_nbchar(char *str, int nb, int index)
{
  char	*first;
  char	*second;
  char	*full;

  if (str == NULL)
    return (NULL);
  if ((first = my_strndup(str, index)) == NULL)
    return (NULL);
  if ((second = my_strdup(str + index + nb)) == NULL)
    return (NULL);
  if ((full = my_strcatdup(first, second, 3)) == NULL)
    return (NULL);
  free(str);
  return (full);
}

char	*add_substr(char *str, char *substr, int index)
{
  char	*new;

  if (str == NULL || substr == NULL)
    return (NULL);
  if ((new = my_strndup(str, index)) == NULL)
    return (NULL);
  if ((new = my_strcatdup(new, substr, 1)) == NULL)
    return (NULL);
  if ((new = my_strcatdup(new, str + index, 1)) == NULL)
    return (NULL);
  free(str);
  return (new);
}

char	*replace_quoted_str(char *str, char *find,
			    char *replace, char *quote_list)
{
  int	i;
  char	quote;

  quote = 0;
  i = -1;
  if (str == NULL || find == NULL || replace == NULL)
    return (NULL);
  while (str[++i])
    {
      if ((quote == 0 && is_in(str[i], INIB)) || str[i] == quote)
	quote = (!quote ? str[i] : 0);
      if (!my_strncmp(str + i, find, my_strlen(find)) &&
	  is_in(quote, quote_list))
	{
	  if ((str = delete_nbchar(str, my_strlen(find), i)) == NULL)
	    return (NULL);
	  if ((str = add_substr(str, replace, i)) == NULL)
	    return (NULL);
	  i = 0;
	}
    }
  return (str);
}

char	*replace_unquoted_str(char *str, char *find,
			      char *replace, char *quote_list)
{
  int	i;
  char	quote;

  quote = 0;
  i = -1;
  if (str == NULL || find == NULL || replace == NULL)
    return (NULL);
  while (str[++i])
    {
      if ((quote == 0 && is_in(str[i], quote_list)) || str[i] == quote)
	quote = (!quote ? str[i] : 0);
      if (!my_strncmp(str + i, find, my_strlen(find)) && !quote)
	{
	  if ((str = delete_nbchar(str, my_strlen(find), i)) == NULL)
	    return (NULL);
	  if ((str = add_substr(str, replace, i)) == NULL)
	    return (NULL);
	  i = 0;
	}
    }
  return (str);
}

char	*dequotificator(char *str)
{
  char	*dequoted;
  char	quote;
  int	i;
  int	nb;

  i = -1;
  quote = 0;
  nb = 0;
  while (str[++i])
    if ((quote == 0 && is_in(str[i], INIB)) || str[i] == quote)
      quote = (!quote ? str[i] : 0) + 0 * (nb++);
  if ((dequoted = malloc(sizeof(char) * (my_strlen(str) + 1 - nb))) == NULL)
    return (NULL);
  dequoted[my_strlen(str) - nb] = 0;
  i = -1;
  nb = 0;
  while (str[++i])
    if ((quote == 0 && is_in(str[i], INIB)) || str[i] == quote)
      quote = (!quote ? str[i] : 0) + 0 * (nb++);
    else
      dequoted[i - nb] = str[i];
  return (dequoted);
}
