/*
** pipe_error.c for error in /home/thibrex/Dropbox/delivery/PSU/PSU_2016_42sh/parseur 42
** 
** Made by Thibaut Cornolti
** Login   <thibaut.cornolti@epitech.eu>
** 
** Started on  Thu May  4 21:26:36 2017 Thibaut Cornolti
** Last update Mon May 15 17:50:03 2017 Thibaut Cornolti
*/

#include <string.h>
#include "syntax.h"
#include "my.h"

static int	check_pipe(t_token *start, t_token *end, int mask_need_one)
{
  int		already_check;

  already_check = 0;
  while (start != end)
    {
      already_check |= start->type;
      start = start->next;
    }
  if (!(mask_need_one & already_check))
    {
      my_puterror("Invalid null command.\n");
      return (1);
    }
  return (0);
}

int		error_logic_node(t_field *field, t_token *mid)
{
  int		next_need_one;
  int		prev_need_one;

  next_need_one = T_COMMAND;
  prev_need_one = T_COMMAND;
  if ((!strcmp(mid->token, "||") &&
       check_pipe(field->start, mid, prev_need_one)) ||
      check_pipe(mid->next, field->end, next_need_one))
    return (1);
  return (0);
}
