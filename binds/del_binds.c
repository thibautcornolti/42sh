/*
** del_binds.c for del_binds in /home/cedric/Desktop/get_next_cmd
**
** Made by Cédric THOMAS
** Login   <cedric.thomas@epitech.eu>
**
** Started on  Mon May 15 22:18:05 2017 Cédric THOMAS
** Last update Sun May 21 18:42:31 2017 Cédric THOMAS
*/
#include <curses.h>
#include <termio.h>
#include <stdlib.h>
#include "get_next_command.h"
#include "my.h"
#include "my_printf.h"

int	suppr_char(t_keypad *keypad)
{
  if (keypad->line && keypad->line[keypad->index])
    {
      del_raw_line(keypad);
      keypad->line = delete_a_char(keypad->line, keypad->index);
      print_raw_line(keypad);
    }
  return (0);
}

int	delete_char(t_keypad *keypad)
{
  if (keypad->line && keypad->index > 0)
    {
      del_raw_line(keypad);
      keypad->line = delete_a_char(keypad->line, keypad->index - 1);
      keypad->index -= 1;
      print_raw_line(keypad);
    }
  return (0);
}
