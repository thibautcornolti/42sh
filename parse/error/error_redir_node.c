/*
** pipe_error.c for error in /home/thibrex/Dropbox/delivery/PSU/PSU_2016_42sh/parseur 42
** 
** Made by Thibaut Cornolti
** Login   <thibaut.cornolti@epitech.eu>
** 
** Started on  Thu May  4 21:26:36 2017 Thibaut Cornolti
** Last update Sat May 20 14:13:29 2017 Thibaut Cornolti
*/

#include "syntax.h"
#include "my.h"

int		error_redir_node(t_field *field, t_token *mid)
{
  if (mid->next == field->end)
    my_puterror("Missing name for redirect.\n");
  else
    my_puterror("Invalid null command.\n");
  return (1);
}
