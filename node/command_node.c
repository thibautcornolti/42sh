/*
** standard_node.c for parseur in /home/thibrex/Dropbox/delivery/PSU/PSU_2016_42sh/parseur 42/node
** 
** Made by Thibaut Cornolti
** Login   <thibaut.cornolti@epitech.eu>
** 
** Started on  Thu May  4 18:11:31 2017 Thibaut Cornolti
** Last update Fri May 12 16:45:08 2017 Thibaut Cornolti
*/

#include <stdlib.h>
#include <sys/types.h>
#include "my_alloc.h"
#include "syntax.h"

static int	get_len(t_token *start, t_token *end)
{
  int		len;

  len = 0;
  while (start != end)
    {
      if (start->type == T_COMMAND ||
	  start->type == T_ARGS)
	len += 1;
      start = start->next;
    }
  return (len);
}

static char	**fill_argv(t_field *field)
{
  char		**res;
  int		len;
  t_token	*tmp;
  int		i;

  len = get_len(field->start, field->end);
  if ((res = my_alloc(sizeof(char *) * (len + 1))) == NULL)
    exit(84);
  my_tag_alloc(res, "tree", 0);
  tmp = field->start;
  i = -1;
  while (tmp != field->end)
    {
      if (tmp->type == T_COMMAND ||
	  tmp->type == T_ARGS)
	{
	  if ((res[++i] = alloc_strdup(tmp->token)) == NULL)
	    exit(84);
	  my_tag_alloc(res[i], "tree", 0);
	}
      tmp = tmp->next;
    }
  res[++i] = NULL;
  return (res);
}

static t_redir	*get_redir(t_token *start, t_token *end)
{
  t_redir	*redir;

  redir = NULL;
  while (start != end)
    {
      if (start->next != end &&
	  (start->type &
	   (T_FLUX_REDIR_OUT | T_FLUX_REDIR_IN)) == start->type)
	add_redir_list(&redir, start->next->token, start->token);
      start = start->next;
    }
  return (redir);
}

void		*create_command_node(t_field *field, t_token *mid)
{
  t_command	*new_node;

  if ((new_node = my_alloc(sizeof(t_command))) == NULL)
    exit(84);
  new_node->fd[0] = 0;
  new_node->fd[1] = 1;
  new_node->fd[2] = 2;
  if ((new_node->argv = fill_argv(field)) == NULL)
    return (NULL);
  new_node->root = field->root;
  new_node->type = mid->type;
  my_tag_alloc(new_node, "tree", 0);
  if ((new_node->path = alloc_strdup(mid->token)) == NULL)
    exit(84);
  my_tag_alloc(new_node->path, "tree", 0);
  new_node->redir = get_redir(field->start, field->end);
  return (new_node);
}
