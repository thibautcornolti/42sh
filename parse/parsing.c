/*
** main.c for main.c in /home/cedric/delivery/ex
**
** Made by Cédric Thomas
** Login   <cedric@epitech.net>
**
** Started on  Sat Oct 22 10:31:05 2016 Cédric Thomas
** Last update Sun May 21 18:39:05 2017 Cédric THOMAS
*/
#include <stdlib.h>
#include "syntax.h"
#include "exec.h"
#include "my.h"
#include "my_alloc.h"
#include "my_printf.h"

void		free_syntax(t_syntax **my_syntax)
{
  int		i;

  i = -1;
  while ((*my_syntax)[++i].values)
    {
      free_tab((*my_syntax)[i].values);
      free((*my_syntax)[i].already);
    }
  free(*my_syntax);
  *my_syntax = NULL;
}

t_syntax		*get_syntax()
{
  t_syntax		*my_syntax;

  if ((my_syntax = malloc(sizeof(t_syntax) *
			  (MAX_TYPES + 1))) == NULL)
    return (NULL);
  my_syntax[0] = syntax_create(T_SEPAR, 1, ";");
  my_syntax[1] = syntax_create(T_LOGIC_OR, 1, "||");
  my_syntax[2] = syntax_create(T_LOGIC_AND, 1, "&&");
  my_syntax[3] = syntax_create(T_FLUX, 1, "|");
  my_syntax[4] = syntax_create(T_JOB, 1, "&");
  my_syntax[5] = syntax_create(T_FLUX_REDIR_OUT, 8,
			       ">>", ">", "2>>", "2>",
			       "1>>", "1>", "&>>", "&>");
  my_syntax[6] = syntax_create(T_FLUX_REDIR_IN, 2, "\\<\\<", "\\<");
  my_syntax[7] = syntax_create(T_COMMON, 1, "#");
  my_syntax[7].already[0] = ULIMT_MATCH;
  my_syntax[8] = syntax_create(T_BACKQUOTE, 1, "`");
  my_syntax[9].values = NULL;
  return (my_syntax);
}

static void		cut_comment(char *str)
{
  int			i;

  i = -1;
  if (!str || !str[0])
    return ;
  while (str[++i] &&
	 !(str[i] == '#' &&
	   (i == 0 || str[i - 1] == ' ' || str[i - 1] == '\t')));
  str[i] = 0;
}

t_node			*parse_cmd(t_syntax *my_syntax, char *str,
				   t_system *sys)
{
  t_token		*tokens;
  void			*root;

  cut_comment(str);
  if ((tokens = get_token(str, my_syntax, sys->info, 1)) == NULL)
    return (NULL);
  tokens = globbing(tokens, my_syntax);
  tokens = get_alias(tokens, sys->info, my_syntax);
  if ((do_backquote(&tokens, sys)) == 1)
    {
      my_puterror("Backquote error!\n");
      sys->info->exit_value = 1;
      return (NULL);
    }
  inib_token(tokens);
  if ((root = auto_create_node(NULL, tokens, NULL)) == NULL)
    {
      sys->info->exit_value = 1;
      my_free_tree(&root);
    }
  my_free_token(&tokens);
  return (root);
}
