/*
** backquote.c for 42s in /home/thibrex/Dropbox/delivery/PSU/PSU_2016_42sh
**
** Made by Thibaut Cornolti
** Login   <thibaut.cornolti@epitech.eu>
**
** Started on  Fri May 19 16:52:18 2017 Thibaut Cornolti
** Last update Sat May 20 21:14:50 2017 Cédric THOMAS
*/

#include <stdlib.h>
#include "syntax.h"
#include "exec.h"
#include "my.h"

static int	find_born(t_token **start, t_token **end, t_token **tmp)
{
  int		index;

  index = 0;
  *start = NULL;
  *end = NULL;
  while (*tmp && index != 2)
    {
      if ((*tmp)->type == T_BACKQUOTE)
	{
	  if (index == 0)
	    *start = *tmp;
	  else
	    *end = *tmp;
	  index += 1;
	}
      *tmp = (*tmp)->next;
    }
  return (index != 2);
}

static void	insert_tokens(t_token *start, t_token *end, t_token *new)
{
  t_token	*tmp;

  tmp = new;
  while (tmp && tmp->next)
    tmp = tmp->next;
  if (tmp)
    tmp->next = end;
  end->prev = tmp;
  start->next = new;
  if (new)
    new->prev = start;
  if (start->next == NULL && end->prev == NULL)
    {
      start->next = end;
      end->prev = start;
    }
}

static t_token	*exec_backquote(t_token *token, t_system *sys)
{
  char		*command;
  t_token	*ret;

  command = my_strdup(token->token);
  token = token->next;
  while (token)
    {
      command = my_strcatdup(command, " ", 1);
      command = my_strcatdup(command, token->token, 1);
      token = token->next;
    }
  my_free_token(&token);
  ret = get_system(command, sys);
  return (ret);
}

int		do_backquote(t_token **token, t_system *sys)
{
  t_token	*new;
  t_token	*start;
  t_token	*end;
  t_token	*tmp;

  tmp = *token;
  while (!find_born(&start, &end, &tmp))
    {
      if (start && end && start->next != end &&
	  start->next && end->prev)
	{
	  start->next->prev = NULL;
	  end->prev->next = NULL;
	  new = exec_backquote(start->next, sys);
	  redef_token(new);
	  insert_tokens(start, end, new);
	  my_del_list_token(token, end);
	  my_del_list_token(token, start);
	  redef_all(*token);
	}
    }
  return (0);
}
