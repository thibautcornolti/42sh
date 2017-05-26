/*
** backquote_fork.c for 42sh in /home/thibrex/Dropbox/delivery/PSU/PSU_2016_42sh/parse/backquote
**
** Made by Thibaut Cornolti
** Login   <thibaut.cornolti@epitech.eu>
**
** Started on  Fri May 19 18:17:46 2017 Thibaut Cornolti
** Last update Sun May 21 18:48:48 2017 Cédric THOMAS
*/

#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <wait.h>
#include <limits.h>
#include "syntax.h"
#include "exec.h"
#include "my.h"

static char	*read_son(int fd, int pid, t_system *system)
{
  char		*res;
  int		size;
  char		buf[PIPE_BUF + 1];
  int		readed;
  int		status;

  res = NULL;
  size = 0;
  while (waitpid(pid, &status, WNOHANG) <= 0)
    {
      if ((readed = read(fd, buf, PIPE_BUF)) == -1)
	return (NULL);
      size += readed;
      buf[readed] = 0;
      if ((res = realloc(res, size + 1)) == NULL)
	exit(84);
      my_strcpy(res + size - readed, buf);
    }
  system->info->exit_value = WEXITSTATUS(status);
  if ((res = replace_unquoted_str(res, "\n", " ", "")) == NULL)
    exit(84);
  return (res);
}

void		redef_all(t_token *token)
{
  int		is_arg;

  is_arg = 0;
  while (token)
    {
      if (token->type >= T_FLUX ||
	  (token->type & (T_JOB | T_BACKQUOTE)))
	is_arg = 0;
      if (!is_arg && (token->type & T_COMMON))
	{
	  token->type = T_COMMAND;
	  is_arg = 1;
	}
      else if (is_arg && (token->type & T_COMMON))
	token->type = T_ARGS;
      token = token->next;
    }
}

void		redef_token(t_token *token)
{
  t_token	*tmp;

  tmp = token;
  while (tmp)
    {
      tmp->type = T_ARGS;
      tmp = tmp->next;
    }
}

t_token		*get_system(char *cmd, t_system *sys)
{
  char		*line;
  int		pipefd[2];
  int		pid;

  if (pipe(pipefd) < 0)
    {
      my_puterror("Can't make pipe.");
      return (NULL);
    }
  signal(SIGINT, SIG_IGN);
  if ((pid = fork()) == -1)
    return (NULL);
  else if (pid)
    close(pipefd[1]);
  else
    {
      signal(SIGINT, SIG_DFL);
      dup2(pipefd[1], 1);
      close(pipefd[0]);
      my_system(cmd, sys);
      exit(sys->info->exit_value);
    }
  line = read_son(pipefd[0], pid, sys);
  signal(SIGINT, &signal_sigint);
  return (get_token(line, sys->syntax, sys->info, 0));
}
