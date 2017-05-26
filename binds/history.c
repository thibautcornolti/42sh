/*
** history.c for 42sh in /home/cedric/delivery/PSU/PSU_2016_42sh
**
** Made by Cédric THOMAS
** Login   <cedric.thomas@epitech.eu>
**
** Started on  Thu May 18 19:13:06 2017 Cédric THOMAS
** Last update Sun May 21 18:48:11 2017 Cédric THOMAS
*/
#include <curses.h>
#include <termio.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#include "syntax.h"
#include "exec.h"
#include "get_next_command.h"
#include "my.h"
#include "my_printf.h"

static void	change_born(char *line, time_t my_time,
			    t_info *info, int idx)
{
  while (info->histo->len > HIST_SIZE)
    {
      my_del_list_history(&info->histo->start, info->histo->start);
      info->histo->len -= 1;
    }
  info->histo->len += 1;
  if (info->histo->start == NULL)
    {
      my_put_list_history(&info->histo->start, line,
			  (long) my_time, idx);
      info->histo->end = info->histo->start;
    }
  else
    {
      idx = info->histo->end->index + 1;
      my_put_list_history(&info->histo->end, line,
			  (long) my_time, idx);
      info->histo->end = info->histo->end->next;
    }
}

void			new_line_history(char *line, t_info *info)
{
  t_history_info	*hist;
  time_t		my_time;
  int			idx;

  if (!line || !line[0])
    return ;
  idx = 1;
  hist = info->histo;
  if ((time(&my_time)) < 0)
    my_time = 0;
  if (hist->end && hist->end->status
      && hist->end->prev)
    {
      hist->end = hist->end->prev;
      my_del_list_history(&hist->end, hist->end->next);
    }
  change_born(line, my_time, info, idx);
}

static void	switch_line(t_history_info *hist, t_keypad *key)
{
  del_raw_line(key);
  free(key->line);
  key->line = NULL;
  key->index = 0;
  if (hist->current)
    {
      if ((key->line = my_strdup(hist->current->cmd)) == NULL)
	exit(84);
      if (key->line)
	key->index = my_strlen(key->line);
      print_raw_line(key);
    }
}

int			down_arrow(t_keypad *key)
{
  t_history_info	*hist;
  t_info		*info;

  info = key->sys->info;
  hist = info->histo;
  if (hist->current == NULL ||
      (hist->current->status && hist->current == hist->end))
    return (0);
  hist->current = hist->current->next;
  switch_line(hist, key);
  return (0);
}

int			up_arrow(t_keypad *key)
{
  t_history_info	*hist;
  t_info		*info;

  info = key->sys->info;
  hist = info->histo;
  if (hist->current == NULL)
    {
      hist->current = hist->end;
      new_line_history(key->line, info);
      if (info->histo->end && key->line && key->line[0])
	info->histo->end->status = 1;
    }
  else if (hist->current->prev)
    hist->current = hist->current->prev;
  switch_line(hist, key);
  return (0);
}
