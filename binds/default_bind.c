/*
** default_bind.c for gnc in /home/cedric/Desktop/get_next_cmd
**
** Made by Cédric THOMAS
** Login   <cedric.thomas@epitech.eu>
**
** Started on  Mon May 15 22:03:45 2017 Cédric THOMAS
** Last update Sun May 21 18:43:53 2017 Cédric THOMAS
*/
#include <sys/ioctl.h>
#include <ncurses.h>
#include <curses.h>
#include <term.h>
#include "get_next_command.h"
#include "my_printf.h"
#include "my.h"

void		default_append(char *buff, t_keypad *keypad,
			       int size_buff)
{
  int		idx;
  int		i;

  i = -1;
  idx = 0;
  del_raw_line(keypad);
  while (buff[++i])
    {
      if (buff[i] >= ' ' && buff[i] <= '~')
	{
	  keypad->line = insert_str(keypad->line,
				    buff + i, keypad->index + idx, 1);
	  idx += 1;
	}
    }
  keypad->index += idx;
  search_matched(keypad);
  print_raw_line(keypad);
  UNUSED(size_buff);
}
