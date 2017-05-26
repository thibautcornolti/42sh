/*
** my_alloc.h for my_alloc in /home/cedric/delivery/libmalloc
** 
** Made by 
** Login   <cedric.thomas@epitech.eu>
** 
** Started on  Mon Mar  6 18:13:51 2017 
** Last update Sat May 20 20:04:25 2017 Thibaut Cornolti
*/
#include <stdlib.h>
#include "my_alloc.h"

t_alloc		*g_allocs = NULL;

size_t		my_alloc_size(void *alloc)
{
  int		i;
  t_alloc	*temp;

  i = 0;
  if ((temp = g_allocs) == NULL || alloc == NULL)
    return (0);
  while (!i || temp != g_allocs)
    {
      if (temp->addr == alloc)
	return (temp->size);
      temp = temp->next;
      i = 1;
    }
  return (0);
}

void	*my_alloc(size_t size)
{
  void	*alloc;
  int	i;

  i = -1;
  if ((alloc = malloc(size)) == NULL)
    return (NULL);
  if (my_put_alloc(alloc, size) == 84)
    {
      free(alloc);
      return (NULL);
    }
  while (++i < size)
    ((char *)alloc)[i] = 0;
  return (alloc);
}

void		*my_realloc(void **alloc, size_t size_new)
{
  void		*new;
  size_t	size;
  int		i;
  t_alloc	*temp;

  i = -1;
  if ((temp = g_allocs) == NULL || alloc == NULL || *alloc == NULL)
    return (NULL);
  while (!(++i) || temp != g_allocs && temp->addr != (*alloc))
    temp = temp->next;
  i = -1;
  if (temp->addr != (*alloc) || (new = malloc(size_new)) == NULL)
    return (NULL);
  size = my_alloc_size(*alloc);
  while (++i < size_new)
    ((char *)new)[i] = (i < size ? ((char *)(*alloc))[i] : 0);
  if (my_put_alloc(new, size_new) == 84)
    {
      free(new);
      return (NULL);
    }
  my_del_alloc(temp);
  *alloc = NULL;
  return (new);
}

void		*my_vfree(void **to_free, void *to_ret)
{
  int		i;
  t_alloc	*temp;

  if (to_free == NULL || *to_free == NULL)
    {
      while (g_allocs != NULL)
	my_del_alloc(g_allocs);
      return (to_ret);
    }
  i = 0;
  if ((temp = g_allocs) == NULL)
    return (NULL);
  while (!i || temp != g_allocs && temp->addr != (*to_free))
    {
      temp = temp->next;
      i = 1;
    }
 if (temp->addr != (*to_free))
    return (to_ret);
  my_del_alloc(temp);
  *to_free = NULL;
  return (to_ret);
}

int		my_ifree(void **to_free, int to_ret)
{
  int		i;
  t_alloc	*temp;

  if (to_free == NULL || *to_free == NULL)
    {
      while (g_allocs != NULL)
	my_del_alloc(g_allocs);
      return (to_ret);
    }
  i = 0;
  if ((temp = g_allocs) == NULL)
    return (-1);
  while (!i || temp != g_allocs && temp->addr != (*to_free))
    {
      temp = temp->next;
      i = 1;
    }
  if (temp->addr != (*to_free))
    return (to_ret);
  my_del_alloc(temp);
  *to_free = NULL;
  return (to_ret);
}
