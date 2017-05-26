/*
** wait_job.c for 42sh in /home/thibrex/Dropbox/delivery/PSU/PSU_2016_42sh
** 
** Made by Thibaut Cornolti
** Login   <thibaut.cornolti@epitech.eu>
** 
** Started on  Sat May 20 20:32:44 2017 Thibaut Cornolti
** Last update Sat May 20 20:35:32 2017 Thibaut Cornolti
*/

#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <stdio.h>
#include <sys/wait.h>
#include "syntax.h"
#include "exec.h"
#include "my.h"
#include "my_printf.h"

static void	write_state(t_exit *exit, t_job *job, int *last)
{
  if (exit->exit)
    printf("[%d]    Exit %d\n", job->number, exit->exit % 255);
  else
    printf("[%d]    Done\n", job->number);
  *last = job->number;
}

void		print_wait_job(t_status *status)
{
  t_exit	*exit;
  t_job		*job;
  int		last;

  exit = status->exit_list;
  while (exit && exit->next)
    exit = exit->next;
  last = 0;
  while (exit)
    {
      job = exit->job;
      if (job && job->status & JOB_TERMPRINT && job->number)
	{
	  if (last != job->number)
	    write_state(exit, job, &last);
	  job->status = JOB_TERMINATED;
	  job->number = 0;
	  exit->exit = 0;
	}
      exit = exit->prev;
    }
}
