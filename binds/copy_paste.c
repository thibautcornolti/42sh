/*
** copy_paste.c for 42sh in /home/thibrex/Dropbox/delivery/PSU/PSU_2016_42sh
**
** Made by Thibaut Cornolti
** Login   <thibaut.cornolti@epitech.eu>
**
** Started on  Fri May 19 22:19:27 2017 Thibaut Cornolti
** Last update Sun May 21 18:43:41 2017 Cédric THOMAS
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

int	bind_paste(t_keypad *keypad)
{
  if (keypad->copy == NULL)
    return (0);
  keypad->line = insert_str(keypad->line, keypad->copy, keypad->index, 0);
  del_raw_line(keypad);
  keypad->index += my_strlen(keypad->copy);
  print_raw_line(keypad);
  return (0);
}

int	bind_copy(t_keypad *keypad)
{
  char	*seq;
  int	i;
  int	len;

  if (keypad->line == NULL)
    return (0);
  if ((seq = tigetstr("cub1")) == (char *)-1)
    return (0);
  free(keypad->copy);
  keypad->copy = my_strdup(keypad->line + keypad->index);
  len = my_strlen(keypad->line + keypad->index);
  i = len;
  while (i--)
    my_printf(" ");
  i = len;
  while (i--)
    my_printf(seq);
  keypad->line[keypad->index] = 0;
  return (0);
}

int	bind_copy_all(t_keypad *keypad)
{
  if (keypad->line == NULL)
    return (0);
  free(keypad->copy);
  keypad->copy = my_strdup(keypad->line);
  del_raw_line(keypad);
  free(keypad->line);
  keypad->line = NULL;
  keypad->index = 0;
  return (0);
}
