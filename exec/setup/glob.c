/*
** glob.c for 42sh in /home/rectoria/delivery/Projets/PSU_2016_42sh
** 
** Made by Bastien
** Login   <rectoria@epitech.net>
** 
** Started on  Wed May 17 10:35:38 2017 Bastien
** Last update Sat May 20 20:31:20 2017 Cédric THOMAS
*/

#include <unistd.h>
#include <stdlib.h>
#include <glob.h>
#include "my.h"
#include "syntax.h"
#include "exec.h"

static void	set_token(t_token **save, t_token **new, t_token **token)
{
  if (!(*token)->prev)
    *save = *new;
  (*new)->prev = (*token)->prev;
  if ((*token)->prev)
    (*token)->prev->next = *new;
  while ((*new)->next)
    {
      (*new)->type = T_COMMON;
      (*new) = (*new)->next;
    }
  (*new)->type = T_COMMON;
  (*new)->next = (*token)->next;
  if ((*token)->next)
    (*token)->next->prev = *new;
  *token = *new;
}

static void	get_glob(glob_t *globbuf, t_token **save,
			 t_token **token, t_syntax *syntax)
{
  unsigned int	i;
  t_token	*new;
  char		*temp;

  i = 0;
  temp = 0;
  i = 0;
  while (i <= globbuf->gl_pathc)
    {
      temp = my_strcatdup(temp, globbuf->gl_pathv[i], 1);
      if (i + 1 < globbuf->gl_pathc)
	temp = my_strcatdup(temp, " ", 1);
      i++;
    }
  new = get_token(temp, syntax, 0, 1);
  globfree(globbuf);
  set_token(save, &new, token);
}

t_token		*globbing(t_token *token, t_syntax *syntax)
{
  t_token	*save;
  glob_t	globbuf;

  save = token;
  while (token)
    {
      if (!(GLOB_NOMATCH & glob(token->token, GLOB_TILDE, 0, &globbuf))
	  && token->type & T_COMMON)
	get_glob(&globbuf, &save, &token, syntax);
      else if (token->type & T_COMMON)
	token->type = T_COMMON;
      token = token->next;
    }
  shape_token(save);
  return (save);
}
