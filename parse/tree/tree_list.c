/*
** tree_list.c for parseur in /home/cedric/delivery/parseur_ll/tree
**
** Made by
** Login   <cedric.thomas@epitech.eu>
**
** Started on  Fri Mar 24 15:04:43 2017
** Last update Sun May 21 18:36:40 2017 Cédric THOMAS
*/

#include <stdlib.h>
#include "syntax.h"
#include "my.h"
#include "my_printf.h"
#include "my_alloc.h"

static void	pad_me(int depth)
{
  int		i;

  i = -1;
  while (++i < depth)
    my_putchar('\t');
}

static void	line_wordtab(char **tab)
{
  int		i;

  if (!tab)
    return ;
  my_printf(", argv :");
  i = -1;
  while (tab[++i])
    my_printf(" %s", tab[i]);
  my_printf("\n");
}

void	show_nodes(t_node *root, int depth, int side)
{
  if (!root)
    return ;
  if (root->right != NULL)
    show_nodes((t_node *)root->right, depth + 1, 2);
  pad_me(depth);
  my_printf("%d: [%d] %s", side, root->type, root->data);
  if (root->type == T_COMMAND)
    {
      line_wordtab(((t_command *)root)->argv);
      show_redir(((t_command *)root)->redir);
    }
  else
    my_printf("\n");
  if (root->left != NULL)
    show_nodes((t_node *)root->left, depth + 1, 1);
}

void	my_free_tree(void **root)
{
  my_free_tag("tree", 0);
  *root = NULL;
}
