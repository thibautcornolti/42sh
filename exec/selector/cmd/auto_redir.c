/*
** redir.c for mysh in /home/cedric/delivery/PSU/PSU_2016_minishell2
** 
** Made by 
** Login   <cedric.thomas@epitech.eu>
** 
** Started on  Thu Mar 30 13:27:56 2017 
** Last update Mon May 15 15:11:19 2017 
*/
#include <stdlib.h>
#include <unistd.h>
#include "syntax.h"
#include "exec.h"
#include "my.h"

static void	fill_fd_fct(int (*fd_fct[REDIR_NB])(char *file))
{
  fd_fct[0] = &redir_output;
  fd_fct[1] = &double_redir_output;
  fd_fct[2] = &redir_input;
  fd_fct[3] = &double_redir_input;
}

static int	get_fd(int tag, char *file)
{
  int		(*fd_fct[REDIR_NB])(char *file);
  int		index;

  index = 0;
  if ((tag & DOUBLE) == DOUBLE)
    index += 1;
  if ((tag & STDIN) == STDIN)
    index += 2;
  fill_fd_fct(fd_fct);
  return (fd_fct[index](file));
}

static void	dup_fd(int fd, int tag)
{
  if ((tag & STDIN) == STDIN)
    {
      if (dup2(fd, 0) < 0)
	exit(84);
    }
  if ((tag & STDOUT) == STDOUT)
    {
      if (dup2(fd, 1) < 0)
	exit(84);
    }
  if ((tag & STDERROR) == STDERROR)
    {
      if (dup2(fd, 2) < 0)
	exit(84);
    }
}

static void	assign_fd(t_command *cmd, int fd, int tag)
{
  if ((tag & STDIN) == STDIN)
    cmd->fd[0] = fd;
  if ((tag & STDOUT) == STDOUT)
    cmd->fd[1] = fd;
  if ((tag & STDERROR) == STDERROR)
    cmd->fd[2] = fd;
}

int		load_redir(t_command *cmd, t_status *status)
{
  int		fd;
  t_redir	*tmp;

  tmp = cmd->redir;
  while (tmp)
    {
      if ((fd = get_fd(tmp->tag, tmp->file)) < 0)
	return (1);
      if ((status->status & FORK) == FORK)
	dup_fd(fd, tmp->tag);
      else
	assign_fd(cmd, fd, tmp->tag);
      tmp = tmp->next;
    }
  return (0);
}
