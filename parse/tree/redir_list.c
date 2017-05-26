/*
** redir_list.c for parseur 42 in /home/cedric/delivery/PSU/PSU_2016_42sh/parseur 42
**
** Made by Cédric THOMAS
** Login   <cedric.thomas@epitech.eu>
**
** Started on  Thu May  4 21:28:56 2017
** Last update Mon May 15 14:23:21 2017 
*/
#include <stdlib.h>
#include "my_alloc.h"
#include "my_printf.h"
#include "syntax.h"
#include "match.h"

static int	get_tag(char *type)
{
  int		flag;

  flag = 0;
  if (advanced_match(type, "*<<*") || advanced_match(type, "*>>*"))
    flag |= DOUBLE;
  if (advanced_match(type, "{\\<\\<,\\<}"))
    {
      flag |= STDIN;
      return (flag);
    }
  if (advanced_match(type, "{2,&}{>>,>}"))
    flag |= STDERROR;
  if (advanced_match(type, "{1,&,}{>>,>}"))
    flag |= STDOUT;
  return (flag);
}

void		show_redir(t_redir *redir)
{
  int		tag;

  while (redir)
    {
      tag = redir->tag;
      if (tag & DOUBLE)
	my_printf("DOUBLE\n");
      if (tag & STDOUT)
	my_printf("OUT\n");
      if (tag & STDERROR)
	my_printf("ERROR\n");
      if (tag & STDIN)
	my_printf("INPUT\n");
      my_printf("full %d\n", tag);
      my_printf("|\n`->%s\n", redir->file);
      redir = redir->next;
    }
}

int		add_redir_list(t_redir **my_redir, char *file, char *type)
{
  t_redir	*elem;

  if ((elem = my_alloc(sizeof(t_redir))) == NULL)
    exit(84);
  my_tag_alloc(elem, "tree", 0);
  elem->tag = get_tag(type);
  if ((elem->file = alloc_strdup(file)) == NULL)
    exit(84);
  my_tag_alloc(elem->file, "tree", 0);
  elem->next = *my_redir;
  *my_redir = elem;
  return (0);
}
