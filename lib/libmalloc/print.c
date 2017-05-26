/*
** print.c for liballoc in /home/cedric/delivery/libmalloc
** 
** Made by 
** Login   <cedric.thomas@epitech.eu>
** 
** Started on  Tue Mar  7 09:17:38 2017 
** Last update Tue Mar  7 09:36:59 2017 
*/
#include <stdlib.h>
#include "my_alloc.h"

void	aputnbr(int nb)
{
  if (nb < 0)
    {
      aputchar('-');
      nb = -nb;
    }
  if (nb / 10 > 0)
    aputnbr(nb / 10);
  aputchar((nb % 10) + '0');
}

void	aputstr(char *str)
{
  int	i;

  i = -1;
  while (str[++i])
    aputchar(str[i]);
}

void	putalloc(t_alloc *tp)
{
  if (tp == NULL)
    return ;
  aputchar('[');
  my_put_apointer(tp->addr, "0123456789abcdef");
  aputstr("] ");
  aputnbr(tp->size);
  aputchar(' ');
  aputchar(tp->type);
  aputchar(' ');
  if (tp->tag != NULL)
    aputstr(tp->tag);
  else
    aputstr("null");
  aputchar('\n');
}
