/*
** module_list.c for module_list in /home/cedric/Desktop/pushswap
** 
** Made by Cédric Thomas
** Login   <cedric@epitech.net>
** 
** Started on  Mon Nov 21 12:15:25 2016 Cédric Thomas
** Last update Sun May 21 18:36:00 2017 Thibaut Cornolti
*/
#include <stdlib.h>
#include "my_alloc.h"

extern t_alloc  *g_allocs;

int		my_put_alloc(void *addr, size_t size)
{
  t_alloc	**ll;
  t_alloc	*elem;
  t_alloc	*tmp;

  ll = &g_allocs;
  if ((elem = malloc(sizeof(*elem))) == NULL)
    return (84);
  elem->addr = addr;
  elem->size = size;
  elem = init_alloc(elem, ' ', NULL);
  if (*ll == NULL)
    {
      elem->next = elem;
      elem->prev = elem;
      *ll = elem;
    }
  else
    {
      tmp = (*ll)->prev;
      (*ll)->prev = elem;
      elem->next = *ll;
      elem->prev = tmp;
      tmp->next = elem;
    }
  return (0);
}

int		my_del_alloc(t_alloc *elem)
{
  t_alloc	**ll;

  ll = &g_allocs;
  if (elem == *ll)
    *ll = (*ll)->next;
  elem->next->prev = elem->prev;
  elem->prev->next = elem->next;
  if (elem == *ll)
    *ll = NULL;
  free(elem->addr);
  free(elem->tag);
  free(elem);
  return (0);
}

int		my_tag_alloc(void *addr, char *tag, char type)
{
  int           i;
  t_alloc       *temp;

  i = 0;
  if ((temp = g_allocs) == NULL)
    return (0);
  while (!i || temp != g_allocs)
    {
      if (temp->addr == addr)
	{
	  temp->tag = my_astrdup(tag);
	  temp->type = type;
	}
      temp = temp->next;
      i = 1;
    }
  return (0);
}

void		my_show_alloc(void *addr, char *tag, char type)
{
  int		j;
  int           i;
  t_alloc       *tp;

  i = -1;
  if ((tp = g_allocs) == NULL)
    return ;
  while (!(++i) || tp != g_allocs)
    {
      j = -1;
      if (tp->addr == addr || (!my_astrcmp(tp->tag, tag) && tag)
	  || type == tp->type || type == -1)
	{
	  aputnbr(i);
	  aputstr(" : ");
	  putalloc(tp);
	}
      tp = tp->next;
    }
}

void		my_free_tag(char *tag, char type)
{
  int		i;
  t_alloc	*temp;

  i = 0;
  if ((temp = g_allocs) == NULL)
    return ;
  while (!i || temp != g_allocs)
    {
      if ((type && temp->type == type) ||
	  (tag != NULL && !my_astrcmp(temp->tag, tag)))
	{
	  my_del_alloc(temp);
	  i = 0;
	  if ((temp = g_allocs) == NULL)
	    return ;
	}
      else
	{
	  temp = temp->next;
	  i = 1;
	}
    }
}
