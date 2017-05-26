/*
** fg.c for 42sh in /home/thibrex/Dropbox/delivery/PSU/PSU_2016_42sh/parseur42
** 
** Made by Thibaut Cornolti
** Login   <thibaut.cornolti@epitech.eu>
** 
** Started on  Mon May 15 22:40:26 2017 Thibaut Cornolti
** Last update Sat May 20 19:55:39 2017 Thibaut Cornolti
*/

#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/wait.h>
#include "syntax.h"
#include "exec.h"
#include "my.h"
#include "my_printf.h"

static void	do_fg(t_job *found, t_status *status, t_info *info)
{
  tcsetpgrp(0, found->pgid);
  kill(-found->pgid, SIGCONT);
  found->status = JOB_FOREGROUND;
  my_printf("Continued\n");
  info->exit_value = 0;
  auto_wait(status, info);
}

void		builtin_fg(t_command *cmd, t_status *status, t_info *info)
{
  t_exit	*exit;
  t_job		*found;
  int		argc;

  UNUSED(info);
  argc = -1;
  while (cmd->argv[++argc]);
  auto_wait(status, info);
  exit = status->exit_list;
  while (!(exit == NULL ||
	   exit->job->status & JOB_BACKGROUND ||
	   exit->job->status & JOB_SUSPENDED))
    exit = exit->next;
  found = exit ? exit->job : NULL;
  if (argc != 1 && cmd->argv[1][0] == '%')
    found = get_job_by_number(status->exit_list, atoi(cmd->argv[1] + 1));
  if (!found)
    {
      my_puterror((argc != 1 && cmd->argv[1][0] == '%') ?
		  "fg: No such job.\n" :
		  "fg: No current job.\n");
      info->exit_value = 1;
      return ;
    }
  do_fg(found, status, info);
}
