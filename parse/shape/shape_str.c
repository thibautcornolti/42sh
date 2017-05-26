/*
** shape_it.c for parseur in /home/cedric/delivery/parseur_ll/lexer
** 
** Made by 
** Login   <cedric.thomas@epitech.eu>
** 
** Started on  Thu Mar 23 17:12:35 2017 
** Last update Sat May 20 20:20:05 2017 Thibaut Cornolti
*/
#include <stdlib.h>
#include "my.h"
#include "syntax.h"

char	*shape_str(char *str)
{
  char	**delim;

  delim = tab_create(16, ";", "||", "&&", "|", "&>>", "1>>",
		     "2>>", ">>", "&>", "1>", "2>", ">", "&",
		     "<<", "<", "`");
  str = shape_separator(str, delim);
  free_tab(delim);
  return (str);
}
