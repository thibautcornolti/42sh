/*
** alloc_misc.c for misc_alloc in /home/cedric/lib/lib/libmalloc
** 
** Made by 
** Login   <cedric.thomas@epitech.eu>
** 
** Started on  Thu Mar 16 19:07:35 2017 
** Last update Thu Mar 16 19:17:10 2017 
*/
#include <stdlib.h>
#include "my_alloc.h"

t_alloc		*init_alloc(t_alloc *tp, char type, char *tag)
{
  tp->tag = NULL;
  tp->type = ' ';
  return (tp);
}
