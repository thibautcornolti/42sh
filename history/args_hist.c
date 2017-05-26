/*
** args_hist.c for hist in /home/cedric/delivery/PSU/PSU_2016_42sh/history
**
** Made by Cédric THOMAS
** Login   <cedric.thomas@epitech.eu>
**
** Started on  Sat May 20 13:43:45 2017 Cédric THOMAS
** Last update Sun May 21 18:25:23 2017 Cédric THOMAS
*/
#include <termio.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include "match.h"
#include "syntax.h"
#include "exec.h"
#include "get_next_command.h"
#include "my.h"

static char	*history_fct_def(char *src, int *idx,
				 t_history_info *history)
{
  UNUSED(history);
  UNUSED(idx);
  free(src);
  return (NULL);
}

static void	fill_fct(char *pattern[6],
			 char *(*fct[6])(char *, int *, t_history_info *))
{
  fct[0] = history_fct_exclam;
  fct[1] = history_fct_dollar;
  fct[2] = history_fct_colon;
  fct[3] = history_fct_dash;
  fct[4] = history_fct_number;
  fct[5] = history_fct_def;
  pattern[0] = "!*";
  pattern[1] = "$*";
  pattern[2] = ":*";
  pattern[3] = "-*";
  pattern[4] = "[0-9]*";
  pattern[5] = "*";
}

int	get_index(char *cmd, int *i)
{
  int	backslash;

  *i -= 1;
  backslash = 0;
  while (cmd[++(*i)] && !(cmd[*i] == '!' && !backslash))
    {
      if (cmd[*i] != '!' && backslash)
	backslash = 0;
      if (cmd[*i] == '\\')
	backslash = 1;
    }
  while (*i > 0 && cmd[*i - 1] == '!')
    *i -= 1;
  if (!cmd[*i])
    return (-1);
  return (*i);
}

char	*change_hist(char *cmd, t_info *info)
{
  int	stop;
  char	*flag[6];
  char	*(*fct[6])(char *, int *, t_history_info *);
  int	index;
  int	i;

  fill_fct(flag, fct);
  index = 0;
  while ((get_index(cmd, &index)) >= 0)
    {
      stop = 0;
      i = -1;
      while (flag[++i] && !stop)
	if (advanced_match(cmd + index + 1, flag[i]))
	  {
	    stop = 1;
	    if ((cmd = fct[i](cmd, &index, info->histo)) == NULL)
	      return (NULL);
	  }
    }
  return (cmd);
}
