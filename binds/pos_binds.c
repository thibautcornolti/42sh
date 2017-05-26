/*
** pos_bind.c for 42sh in /home/cedric/Desktop/get_next_cmd
**
** Made by Cédric THOMAS
** Login   <cedric.thomas@epitech.eu>
**
** Started on  Tue May 16 12:51:32 2017 Cédric THOMAS
** Last update Sun May 21 18:42:11 2017 Cédric THOMAS
*/
#include <curses.h>
#include <termio.h>
#include <stdlib.h>
#include "get_next_command.h"
#include "my.h"
#include "my_printf.h"

int	go_start(t_keypad *keypad)
{
  char	*seq;

  if (keypad->line != NULL && keypad->index > 0)
    {
      if ((seq = tigetstr("cub1")) == (char *)-1)
	return (0);
      while (keypad->index > 0)
	{
	  my_printf(seq);
	  keypad->index -= 1;
	}
    }
  return (0);
}

int	go_end(t_keypad *keypad)
{
  char	*seq;

  if (keypad->line != NULL && keypad->line[keypad->index])
    {
      if ((seq = tigetstr("cuf1")) == (char *)-1)
	return (0);
      while (keypad->line[keypad->index])
	{
	  my_printf(seq);
	  keypad->index += 1;
	}
    }
  return (0);
}

int	switch_mod(t_keypad *key)
{
  del_raw_line(key);
  if (key->mod)
    {
      free(key->matched);
      key->matched = NULL;
      key->mod = 0;
    }
  else
    {
      key->mod = 1;
      search_matched(key);
    }
  print_raw_line(key);
  return (0);
}
