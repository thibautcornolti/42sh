/*
** copy_paste.c for 42sh in /home/thibrex/Dropbox/delivery/PSU/PSU_2016_42sh
**
** Made by Thibaut Cornolti
** Login   <thibaut.cornolti@epitech.eu>
**
** Started on  Fri May 19 22:19:27 2017 Thibaut Cornolti
** Last update Sun May 21 18:42:39 2017 Cédric THOMAS
*/

#include <curses.h>
#include <termio.h>
#include <stdlib.h>
#include <unistd.h>
#include "syntax.h"
#include "exec.h"
#include "get_next_command.h"
#include "my.h"
#include "my_printf.h"

static int	get_shift_left(t_keypad *keypad)
{
  int		i;
  int		shift;
  int		state;

  i = keypad->index;
  shift = 0;
  if (!keypad->line || i == 0)
    return (0);
  state = 0;
  while (state != 2 && i > 0)
    {
      if (keypad->line[i] == ' ' && state == 0 && shift)
	state = 1;
      else if (keypad->line[i] != ' ' && state == 1)
	state = 2;
      else
	{
	  i -= 1;
	  shift += 1;
	}
    }
  return (shift - (i != 0));
}

static int	get_shift_right(t_keypad *keypad)
{
  int		i;
  int		shift;
  int		state;

  i = keypad->index;
  shift = 0;
  if (!keypad->line || !keypad->line[i])
    return (0);
  state = 0;
  while (state != 2 && keypad->line[i])
    {
      if (keypad->line[i] == ' ' && state == 0 && shift)
	state = 1;
      else if (keypad->line[i] != ' ' && state == 1)
	state = 2;
      else
	{
	  i += 1;
	  shift += 1;
	}
    }
  return (shift);
}

int		ctrl_left_arrow(t_keypad *keypad)
{
  char		*seq;
  int		shift;

  if (keypad->line && keypad->index > 0)
    {
      shift = get_shift_left(keypad);
      if ((seq = tigetstr("cub1")) == (char *)-1)
	return (0);
      keypad->index -= shift;
      while (shift-- > 0)
	my_printf(seq);
    }
  return (0);
}

int		ctrl_right_arrow(t_keypad *keypad)
{
  char		*seq;
  int		shift;

  if (keypad->line && keypad->index < my_strlen(keypad->line))
    {
      shift = get_shift_right(keypad);
      if ((seq = tigetstr("cuf1")) == (char *)-1)
	return (0);
      keypad->index += shift;
      while (shift-- > 0)
	my_printf(seq);
    }
  return (0);
}
