/*
** pipe.c for mysh in /home/cedric/delivery/PSU/PSU_2016_minishell2
**
** Made by
** Login   <cedric.thomas@epitech.eu>
**
** Started on  Wed Mar 29 21:29:03 2017
** Last update Sun May 21 15:57:28 2017 Thibaut Cornolti
*/

#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include "syntax.h"
#include "exec.h"
#include "my.h"

static void	pipe_error(t_pipe *root)
{
  if (((t_pipe *) root)->fd[0] != 0)
    close(((t_pipe *) root)->fd[0]);
  my_puterror("Cant't make pipe.\n");
}

static void	pipe_and_send(t_pipe *root, t_status *status, t_info *info)
{
  int		fd[2];

  if (pipe(fd) < 0)
    {
      pipe_error(root);
      return ;
    }
  status->status += LEFT_PIPE;
  ((t_pipe *) root->left)->fd[1] = fd[1];
  ((t_pipe *) root->left)->fd[0] = root->fd[0];
  status->fd_to_close = fd[0];
  auto_select(root->left, status, info);
  close(fd[1]);
  if (((t_pipe *) root->left)->fd[0] != 0)
    close(((t_pipe *) root->left)->fd[0]);
  status->fd_to_close = 0;
  status->status -= LEFT_PIPE;
  status->status += RIGHT_PIPE;
  ((t_pipe *) root->right)->fd[0] = fd[0];
  auto_select(root->right, status, info);
  close(fd[0]);
  status->status -= RIGHT_PIPE;
}

int		exec_pipe(t_node *root, t_status *status, t_info *info)
{
  t_pipe	*my_pipe;
  int		first;

  first = 0;
  my_pipe = (t_pipe *) root;
  if ((status->status & PIPELINE) != PIPELINE)
    {
      first = 1;
      status->status += PIPELINE;
    }
  pipe_and_send(my_pipe, status, info);
  if (first)
    {
      auto_wait(status, info);
      status->status -= PIPELINE;
    }
  return (0);
}
