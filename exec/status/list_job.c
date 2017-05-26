/*
** list_job.c for 42sh in /home/thibrex/Dropbox/delivery/PSU/PSU_2016_42sh/parseur42
** 
** Made by Thibaut Cornolti
** Login   <thibaut.cornolti@epitech.eu>
** 
** Started on  Mon May 15 21:10:07 2017 Thibaut Cornolti
** Last update Sun May 21 21:53:44 2017 Thibaut Cornolti
*/

#include <stdlib.h>
#include "syntax.h"
#include "exec.h"
#include "my_printf.h"

t_job		*my_create_job(t_status *status, int pid,
			       int pgid, int stats)
{
  t_job		*elem;

  if ((elem = malloc(sizeof(*elem))) == NULL)
    exit(84);
  elem->pid = pid;
  elem->pgid = pgid;
  elem->status = stats;
  elem->number = status->job_nbr;
  return (elem);
}

void		show_job_status(t_exit *ll)
{
  static char   *status[6] = {"Running (waiting for print)", "Suspended",
			      "Running (fg)", "Running (bg)",
			      "Terminated (waiting for print)", "Terminated"};
  static int    code[6] = {JOB_CREATPRINT, JOB_SUSPENDED,
			   JOB_FOREGROUND, JOB_BACKGROUND,
			   JOB_TERMPRINT, JOB_TERMINATED};
  int           i;

  while (ll)
    {
      i = -1;
      while (++i < 6)
	if (code[i] == ll->job->status)
	  my_printf("[%d] pid : %d (%s)\n", ll->job->number,
		    ll->job->pid, status[i]);
      ll = ll->next;
    }
}

t_job		*get_job_by_number(t_exit *ll, int number)
{
  if (number)
    while (ll)
      {
	if (ll->job->number == number &&
	    ll->job->status < JOB_TERMPRINT)
	  return (ll->job);
	ll = ll->next;
      }
  return (NULL);
}

int		get_free_job(t_exit *ll)
{
  int		number;
  int		is_free;
  t_exit	*tmp;

  number = 0;
  while (++number)
    {
      tmp = ll;
      is_free = 1;
      while (tmp)
	{
	  if (tmp->job->number == number)
	    is_free = 0;
	  tmp = tmp->next;
	}
      if (is_free)
	return (number);
    }
  return (-1);
}
