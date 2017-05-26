/*
** lexer.c for parseur in /home/cedric/delivery/parseur_ll
**
** Made by
** Login   <cedric.thomas@epitech.eu>
**
** Started on  Wed Mar 22 22:10:45 2017
** Last update Sun May 21 17:18:13 2017 Thibaut Cornolti
*/
#include <unistd.h>
#include <stdlib.h>
#include "syntax.h"
#include "exec.h"
#include "match.h"
#include "my.h"

static void	reset_syntax(t_syntax *my_syntax)
{
  int		i;
  int		j;

  i = -1;
  while (my_syntax[++i].values)
    {
      j = -1;
      while (my_syntax[i].values[++j])
	if (my_syntax[i].already[j] > 0)
	  my_syntax[i].already[j] = LIMT_MATCH;
    }
}

static int	change_len(int *last, int len, int index, t_syntax *syntax)
{
  *last = len;
  if (syntax->already[index] == 0)
    syntax->already[index] = 1;
  return (syntax->weight);
}

static int	len_token(int *type, char *str, t_syntax *my_syntax)
{
  char		temp;
  int		i;
  int		j;
  int		len;
  int		last;

  len = 0;
  last = 0;
  while (str[++len - 1])
    {
      temp = str[len];
      str[len] = 0;
      i = -1;
      while (my_syntax[++i].values)
	{
	  j = -1;
	  while (my_syntax[i].values[++j])
	    if (*type <= my_syntax[i].weight &&
		my_syntax[i].already[j] <= 0 &&
		advanced_match(str, my_syntax[i].values[j]))
	      *type = change_len(&last, len, j, &my_syntax[i]);
	}
      str[len] = temp;
    }
  return (last);
}

static char	*next_token(int *type, char *str, t_syntax *my_syntax)
{
  static int	idx = 0;
  int		len;
  char		*token;

  if (str == NULL || my_syntax == NULL)
    {
      idx = 0;
      return (NULL);
    }
  while (str[idx] && is_in(str[idx], SKIP))
    idx += 1;
  if (str[idx] == 0)
    return (NULL);
  reset_syntax(my_syntax);
  *type = 0;
  len = len_token(type, str + idx, my_syntax);
  token = my_strndup(str + idx, len);
  idx += len;
  return (token);
}

t_token		*get_token(char *str, t_syntax *my_syntax,
			   t_info *info, int shape)
{
  int		type;
  char		*current;
  t_token	*token;

  token = NULL;
  if (check_input_lexer(str))
    {
      if (info)
	info->exit_value = 1;
      return (my_free_null(str));
    }
  if ((str = shape_str(str)) == NULL)
    return (NULL);
  while ((current = next_token(&type, str, my_syntax)))
    {
      if (my_put_list_token(&token, current, type))
	return (NULL);
    }
  next_token(NULL, NULL, NULL);
  if (shape)
    shape_token(token);
  free(str);
  return (token);
}
