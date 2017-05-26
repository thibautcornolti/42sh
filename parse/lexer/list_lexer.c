/*
** list_lexer.c for lexer in /home/cedric/delivery/parseur_ll
** 
** Made by 
** Login   <cedric.thomas@epitech.eu>
** 
** Started on  Wed Mar 22 21:39:39 2017 
** Last update Mon May 15 15:12:31 2017 
*/
#include <string.h>
#include <stdlib.h>
#include "syntax.h"
#include "my_printf.h"

void		swap_token(t_token *one, t_token *two)
{
  char		*token;
  int		type;

  token = one->token;
  type = one->type;
  one->token = two->token;
  one->type = two->type;
  two->token = token;
  two->type = type;
}

int		my_put_list_token(t_token **ll, char *token, int type)
{
  t_token	*elem;
  t_token	*tmp;

  if ((elem = malloc(sizeof(*elem))) == NULL)
    exit(84);
  memset(elem, 0, sizeof(*elem));
  elem->token = token;
  elem->type = type;
  if (*ll == NULL)
    {
      elem->next = NULL;
      elem->prev = NULL;
      *ll = elem;
    }
  else
    {
      tmp = *ll;
      while (tmp->next != NULL)
	tmp = tmp->next;
      elem->prev = tmp;
      elem->next = NULL;
      tmp->next = elem;
    }
  return (0);
}

int		my_show_token(t_token *ll)
{
  while (ll != NULL)
    {
      my_printf("type : %d\ntoken : %s\n\n", ll->type, ll->token);
      ll = ll->next;
    }
  return (0);
}

int		my_del_list_token(t_token **ll, t_token *elem)
{
  if (*ll == elem)
    {
      if ((*ll)->next != NULL)
	*ll = (*ll)->next;
      else if ((*ll)->prev != NULL)
	*ll = (*ll)->prev;
      else
	*ll = NULL;
    }
  if (elem->next != NULL)
    elem->next->prev = elem->prev;
  if (elem->prev != NULL)
    elem->prev->next = elem->next;
  free(elem->token);
  free(elem);
  return (0);
}

int		my_free_token(t_token **ll)
{
  while (*ll != NULL)
    my_del_list_token(ll, *ll);
  *ll = NULL;
  return (0);
}
