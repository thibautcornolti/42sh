/*
** complete_history.c for complete_history.c in /home/cedric/delivery/PSU/PSU_2016_42sh
** 
** Made by Cédric THOMAS
** Login   <cedric.thomas@epitech.eu>
** 
** Started on  Sat May 20 00:07:17 2017 Cédric THOMAS
** Last update Sat May 20 20:23:12 2017 Thibaut Cornolti
*/
#include <unistd.h>
#include <curses.h>
#include <stdlib.h>
#include <termio.h>
#include "syntax.h"
#include "exec.h"
#include "my_printf.h"
#include "get_next_command.h"
#include "my.h"

void		search_matched(t_keypad *key)
{
  t_history	*hist;
  int		len;

  if (key->line == NULL)
    if ((key->line = my_strdup("")) == NULL)
      exit(84);
  free(key->matched);
  key->matched = NULL;
  len = my_strlen(key->line);
  hist = key->sys->info->histo->end;
  while (hist)
    {
      if (!my_strncmp(key->line, hist->cmd, len)
	  && my_strlen(hist->cmd) > len)
	{
	  key->matched = my_strdup(hist->cmd + len);
	  return ;
	}
      hist = hist->prev;
    }
}

int		complete_history(t_keypad *key)
{
  if (key->matched == NULL)
    return (0);
  del_raw_line(key);
  if ((key->line = my_strcatdup(key->line, key->matched, 3)) == NULL)
    exit(84);
  key->matched = NULL;
  key->index = my_strlen(key->line);
  print_raw_line(key);
  return (0);
}
