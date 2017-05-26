/*
** bind.c for get_next_cmd in /home/cedric/Desktop/get_next_cmd
**
** Made by
** Login   <cedric.thomas@epitech.eu>
**
** Started on  Fri Apr 21 22:13:11 2017
** Last update Sun May 21 17:52:16 2017 Cédric THOMAS
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

int		enter(t_keypad *key)
{
  t_info	*info;

  if (key->line == NULL)
    if ((key->line = my_strdup("")) == NULL)
      exit(84);
  info = key->sys->info;
  my_printf("\n");
  info->histo->current = NULL;
  key->end = 1;
  return (0);
}

int	end_of_file(t_keypad *keypad)
{
  if (keypad->line == NULL || !keypad->line[0])
    keypad->end = -1;
  else
    auto_complete(keypad);
  return (0);
}

int	left_arrow(t_keypad *keypad)
{
  char	*seq;

  if ((seq = tigetstr("cub1")) == (char *)-1)
    return (0);
  if (keypad->index > 0)
    {
      keypad->index -= 1;
      my_printf(seq);
    }
  return (0);
}

int	right_arrow(t_keypad *keypad)
{
  char	*seq;

  if ((seq = tigetstr("cuf1")) == (char *)-1)
    return (0);
  if (keypad->line &&
      keypad->index < my_strlen(keypad->line))
    {
      keypad->index += 1;
      my_printf(seq);
    }
  return (0);
}

int	bind_clear(t_keypad *keypad)
{
  char	*seq;

  if ((seq = tigetstr("clear")) == (char *)-1)
    return (0);
  my_printf(seq);
  print_line(keypad);
  return (0);
}
