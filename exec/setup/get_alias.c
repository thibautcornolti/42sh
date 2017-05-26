/*
** alias.c for 42sh in /home/rectoria/delivery/Projets/PSU_2016_42sh/parseur 42/exec/setup
**
** Made by Bastien
** Login   <rectoria@epitech.net>
**
** Started on  Fri May 12 15:28:34 2017 Bastien
** Last update Sun May 21 23:09:39 2017 Bastien
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fnmatch.h>
#include "syntax.h"
#include "exec.h"

void		free_alias(t_alias *alias)
{
  int		i;

  i = -1;
  while (alias && alias[++i].link)
    {
      free(alias[i].link);
      free(alias[i].value);
    }
  free(alias);
}

static void	set_new_token(t_token *token, t_token **save, t_token *new)
{
  if (!token->prev)
    *save = new;
  new->prev = token->prev;
  if (token->prev)
    token->prev->next = new;
  while (new->next)
    new = new->next;
  new->next = token->next;
  if (token->next)
    token->next->prev = new;
  token->next = 0;
  token->prev = 0;
  my_del_list_token(&token, token);
}

static int	verify_cmd(t_token **save, t_token *token,
			   t_info *info, t_syntax *syntax)
{
  int		i;
  t_token	*new;

  i = -1;
  while (info->alias[++i].link)
    if (!strcmp(info->alias[i].link, token->token)
	&& !info->alias[i].loop && !token->used)
      {
	if (!(new = get_token(strdup(info->alias[i].value), syntax, NULL, 1)))
	  return (null_alias(token));
	set_new_token(token, save, new);
	if (!strcmp(info->alias[i].link, new->token))
	  new->used = 1;
	return (1);
      }
    else if (!strcmp(info->alias[i].link, token->token) &&
	     info->alias[i].loop &&
	     strcmp(info->alias[i].link, info->alias[i].value))
      {
	*save = NULL;
	printf("Alias loop.\n");
	return (1);
      }
  return (0);
}

static t_token 	*check_alias(t_token *token, t_info *info, t_syntax *syntax)
{
  t_token	*temp;

  temp = token;
  while (temp)
    {
      if (temp->type & T_COMMAND && verify_cmd(&token, temp, info, syntax))
	temp = token;
      else
	temp = temp->next;
    }
  return (token);
}

t_token	*get_alias(t_token *token, t_info *info, t_syntax *syntax)
{
  if (!info->alias)
    return (token);
  token = check_alias(token, info, syntax);
  return (token);
}
