/*
** pipe_error.c for error in /home/thibrex/Dropbox/delivery/PSU/PSU_2016_42sh/parseur 42
** 
** Made by Thibaut Cornolti
** Login   <thibaut.cornolti@epitech.eu>
** 
** Started on  Thu May  4 21:26:36 2017 Thibaut Cornolti
** Last update Fri May 12 16:57:23 2017 Thibaut Cornolti
*/

#include "syntax.h"
#include "my.h"

static int	check_command(t_token *start, t_token *end,
			      int mask_available)
{
  while (start != end)
    {
      if (!(mask_available & start->type))
	return (1);
      start = start->next;
    }
  return (0);
}

static int	print_error(t_token *start, int *already_check)
{
  if (start->type == T_FLUX_REDIR_IN &&
      *already_check & start->type)
    {
      my_puterror("Ambigous input redirect.\n");
      return (1);
    }
  else if (start->type == T_FLUX_REDIR_OUT &&
	   *already_check & start->type)
    {
      my_puterror("Ambigous output redirect.\n");
      return (1);
    }
  return (0);
}

static int	check_file(t_token *start, t_token *end)
{
  int		already_check;

  already_check = 0;
  while (start != end)
    {
      if (!print_error(start, &already_check) &&
	  (start->type == T_FLUX_REDIR_OUT ||
	   start->type == T_FLUX_REDIR_IN) &&
	  (!start->next ||
	   start->next == end ||
	   start->next->type != T_FILE))
	{
	  my_puterror("Missing name for redirect.\n");
	  return (1);
	}
      already_check |= start->type;
      start = start->next;
    }
  return (0);
}

int		error_command_node(t_field *field, t_token *mid)
{
  int		next_available;
  int		prev_available;

  next_available =  T_ARGS | T_FILE | T_FLUX_REDIR_OUT | T_FLUX_REDIR_IN;
  prev_available = T_FILE | T_FLUX_REDIR_IN | T_FLUX_REDIR_OUT;
  if (check_command(field->start, mid, prev_available) ||
      check_command(mid->next, field->end, next_available) ||
      check_file(field->start, field->end))
    return (1);
  return (0);
}
