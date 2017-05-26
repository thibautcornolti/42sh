/*
** standard_node.c for parseur in /home/thibrex/Dropbox/delivery/PSU/PSU_2016_42sh/parseur 42/node
**
** Made by Thibaut Cornolti
** Login   <thibaut.cornolti@epitech.eu>
**
** Started on  Thu May  4 18:11:31 2017 Thibaut Cornolti
** Last update Sun May 21 18:32:24 2017 Cédric THOMAS
*/

#include <sys/types.h>
#include <stdlib.h>
#include "my_alloc.h"
#include "syntax.h"

void		*create_pipe_node(t_field *field, t_token *mid)
{
  t_pipe	*new_node;

  if ((new_node = my_alloc(sizeof(t_pipe))) == NULL)
    exit(84);
  new_node->root = field->root;
  new_node->type = mid->type;
  my_tag_alloc(new_node, "tree", 0);
  if ((new_node->data = alloc_strdup(mid->token)) == NULL)
    exit(84);
  my_tag_alloc(new_node->data, "tree", 0);
  new_node->fd[0] = 0;
  new_node->fd[1] = 1;
  new_node->fd[2] = 2;
  new_node->left = auto_create_node(new_node, field->start, mid);
  if (new_node->left == NULL)
    return (NULL);
  new_node->right = auto_create_node(new_node, mid->next, field->end);
  if (new_node->right == NULL)
    return (NULL);
  return (new_node);
}
