/*
** builtins.c for 42sh in /home/thibrex/Dropbox/delivery/PSU/PSU_2016_42sh
** 
** Made by Thibaut Cornolti
** Login   <thibaut.cornolti@epitech.eu>
** 
** Started on  Thu May 18 23:57:02 2017 Thibaut Cornolti
** Last update Sun May 21 17:40:17 2017 Thibaut Cornolti
*/

#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include "syntax.h"
#include "exec.h"
#include "my.h"

static t_history	*goin_index(int size, t_info *info)
{
  t_history		*temp;

  if (size < 0)
    return (info->histo->start);
  temp = info->histo->end;
  while (temp && --size > 0)
    temp = temp->prev;
  return (!temp ? info->histo->start : temp);
}

void		builtin_history(t_command *cmd, t_status *status,
				t_info *info)
{
  t_history	*temp;
  struct tm	*tm;

  UNUSED(status);
  if (cmd->argv[1])
    if (!composed_of(cmd->argv[1], "0123456789"))
      {
	printf("history: Badly formed number.\n");
	info->exit_value = 1;
	return ;
      }
  temp = goin_index(cmd->argv[1] ? my_getnbr(cmd->argv[1]) : -1, info);
  while (temp)
    {
      tm = localtime(&temp->time);
      printf("\t%d\t%d:", temp->index, tm->tm_hour);
      if (tm->tm_min < 10)
	printf("0");
      printf("%d\t%s\n", tm->tm_min, temp->cmd);
      temp = temp->next;
    }
  info->exit_value = 0;
}
