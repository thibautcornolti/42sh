/*
** fork.c for 42sh in /home/cedric/delivery/PSU/PSU_2016_42sh/parseur 42/exec
** 
** Made by Cédric THOMAS
** Login   <cedric.thomas@epitech.eu>
** 
** Started on  Wed May 10 21:06:35 2017 
** Last update Sun May 21 22:04:12 2017 Thibaut Cornolti
*/
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <signal.h>
#include "syntax.h"
#include "exec.h"
#include "my_printf.h"

static int	select_wait(t_status *status, int pid)
{
  int		job_val;
  t_job		*job;
  t_exit	*exit;

  job_val = (status->status & JOB) ? JOB_CREATPRINT : JOB_FOREGROUND;
  job = my_create_job(status, pid, status->pgid, job_val);
  exit = my_put_list_exit(&(status->exit_list), pid, status->pgid, 0);
  exit->job = job;
  return (0);
}

static void	reset_sig()
{
  const int	sig[5] = {SIGINT, SIGQUIT, SIGTSTP, SIGTTIN, SIGTTOU};
  int		i;

  i = -1;
  while (++i < 5)
    signal(sig[i], SIG_DFL);
}

static void	my_fork_son(t_command *cmd, t_status *status,
			    t_info *info,
			    void (*fct)(t_command *cmd,
					t_status *status, t_info *info))
{
  setpgid(getpid(), (status->pgid) ? status->pgid : getpid());
  reset_sig();
  if (!(status->status & JOB))
    tcsetpgrp(0, getpgrp());
  status->status |= FORK;
  my_dup(cmd, NULL);
  if (status->fd_to_close)
    close(status->fd_to_close);
  if (load_redir(cmd, status))
    exit(1);
  fct(cmd, status, info);
  exit(info->exit_value);
}

static void	my_fork_father(t_status *status, pid_t pid)
{
  if (status->pgid == 0)
    status->pgid = pid;
  setpgid(pid, status->pgid);
  if (!(status->status & JOB))
    tcsetpgrp(0, status->pgid);
  select_wait(status, pid);
}

int		my_fork(t_command *cmd, t_status *status, t_info *info,
			void (*fct)(t_command *cmd,
				    t_status *status, t_info *info))
{
  pid_t		pid;

  pid = fork();
  if (pid == 0)
    my_fork_son(cmd, status, info, fct);
  else if (pid > 0)
    my_fork_father(status, pid);
  else
    return (-1);
  return (0);
}
