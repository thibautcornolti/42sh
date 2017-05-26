/*
** get_next_cmd.c for get_next_cmd.c in /home/cedric/Desktop/get_next_cmd
**
** Made by
** Login   <cedric.thomas@epitech.eu>
**
** Started on  Fri Apr 21 22:22:55 2017
** Last update Sun May 21 18:40:34 2017 Cédric THOMAS
*/
#include <stdio.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/ioctl.h>
#include <ncurses.h>
#include <termio.h>
#include <stdlib.h>
#include <unistd.h>
#include <curses.h>
#include <term.h>
#include "get_next_command.h"
#include "my.h"
#include "my_printf.h"
#include "get_next_line.h"

static int	get_input(char *buff, t_keypad *keypad)
{
  int		size;

  if ((size = read(0, buff, READ_SIZE)) >= 0)
    buff[size] = 0;
  else
    keypad->end = -1;
  return (size);
}

static void	check_key(char *buff, t_keypad *keypad, int size_buff)
{
  int		is_a_key;
  int		size;
  int		i;

  i = -1;
  is_a_key = 0;
  while (++i < KEY_LINKED && !is_a_key)
    if (keypad->keys[i].sequence != (char *) -1 &&
	keypad->keys[i].sequence != NULL &&
	keypad->keys[i].sequence != (char *) 1)
      {
	size = my_strlen(keypad->keys[i].sequence);
	if (!my_strncmp(keypad->keys[i].sequence, buff, size))
	  {
	    keypad->keys[i].fct(keypad);
	    is_a_key = 1;
	  }
      }
  if (!is_a_key && size_buff > 0)
    default_append(buff, keypad, size_buff);
}

static void		wait_input()
{
  fd_set		rdfs;

  FD_ZERO(&rdfs);
  FD_SET(STDIN_FILENO, &rdfs);
  select(1, &rdfs, NULL, NULL, NULL);
}

char			*get_next_cmd(t_keypad *keypad)
{
  char			*save;
  int			len;
  char			buff[READ_SIZE + 1];

  if (!isatty(0) || !keypad->valid)
    return (get_next_line(0));
  keypad->line = NULL;
  keypad->index = 0;
  while (keypad->end == 0)
    {
      wait_input();
      if ((len = get_input(buff, keypad)) < 0)
	return (NULL);
      if (len)
	check_key(buff, keypad, my_strlen(buff));
    }
  if (keypad->end > 0)
    keypad->end = 0;
  save = keypad->line;
  keypad->line = NULL;
  return (save);
}
