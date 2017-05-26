/*
** job.c for 42sh in /home/thibrex/Dropbox/delivery/PSU/PSU_2016_42sh/parseur42
** 
** Made by Thibaut Cornolti
** Login   <thibaut.cornolti@epitech.eu>
** 
** Started on  Mon May 15 20:54:17 2017 Thibaut Cornolti
** Last update Sun May 21 21:51:51 2017 Thibaut Cornolti
*/

#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include "syntax.h"
#include "exec.h"
#include "my_printf.h"

static void	show_process(t_status *status)
{
  t_exit	*exit;
  t_job		*job;
  int		last;

  exit = status->exit_list;
  last = 0;
  while (exit)
    {
      job = exit->job;
      if (job->status & JOB_CREATPRINT)
	{
	  if (last != job->number)
	    {
	      printf((last) ? "\n[%d]" : "[%d]", job->number);
	      last = job->number;
	    }
	  printf(" %d", job->pid);
	  job->status = JOB_BACKGROUND;
	}
      exit = exit->next;
    }
  printf("\n");
}

int		exec_job(t_node *root, t_status *status, t_info *info)
{
  status->status |= JOB;
  auto_select(root->left, status, info);
  show_process(status);
  status->status -= JOB;
  auto_select(root->right, status, info);
  return (0);
}
