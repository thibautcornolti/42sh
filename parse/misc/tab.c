/*
** tab.c for parseur in /home/cedric/delivery/parseur_ll
** 
** Made by 
** Login   <cedric.thomas@epitech.eu>
** 
** Started on  Thu Mar 23 10:00:54 2017 
** Last update Tue May  2 17:21:39 2017 
*/
#include <stdlib.h>
#include <stdarg.h>
#include "syntax.h"
#include "my.h"

t_syntax	syntax_create(int weight, int size, ...)
{
  char	       *str;
  int		i;
  va_list	str_list;
  t_syntax	syntax;

  my_memset((char *)&syntax, 0, sizeof(t_syntax));
  syntax.weight = weight;
  if ((syntax.already = malloc(sizeof(int) * (size))) == NULL)
    return (syntax);
  if ((syntax.values = malloc(sizeof(char *) * (size + 1))) == NULL)
    return (syntax);
  my_memset((char *)syntax.already, 0, sizeof(int) * size);
  i = -1;
  va_start(str_list, size);
  while (++i < size)
    {
      str = va_arg(str_list, char *);
      if ((syntax.values[i] = my_strdup(str)) == NULL)
	return (syntax);
    }
  syntax.values[i] = NULL;
  va_end(str_list);
  return (syntax);
}

char		**tab_create(int size, ...)
{
  char	       *str;
  int		i;
  va_list	str_list;
  char		**tab;

  if ((tab = malloc(sizeof(char *) * (size + 1))) == NULL)
    return (NULL);
  i = -1;
  va_start(str_list, size);
  while (++ i < size)
    {
      str = va_arg(str_list, char *);
      if ((tab[i] = my_strdup(str)) == NULL)
	return (NULL);
    }
  tab[i] = NULL;
  va_end(str_list);
  return (tab);
}
