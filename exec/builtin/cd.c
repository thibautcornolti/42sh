/*
** cd.c for cd in /home/cedric/delivery/PSU/PSU_2016_minishell1
** 
** Made by 
** Login   <cedric.thomas@epitech.eu>
** 
** Started on  Sun Jan  8 18:51:02 2017 
** Last update Sun May 21 18:34:40 2017 Thibaut Cornolti
*/
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include "syntax.h"
#include "exec.h"
#include "my.h"

static void	print_cderror(char *path)
{
  struct stat	my_stat;

  my_puterror(path);
  if (stat(path, &my_stat) < 0)
    my_puterror(": No such file or directory.\n");
  else if (!S_ISDIR(my_stat.st_mode))
    my_puterror(": Not a directory.\n");
  else if (access(path, R_OK))
    my_puterror(": Permission denied.\n");
}

static void	changepwd(t_info *info)
{
  char		*pwd;

  free(info->old_pwd);
  info->old_pwd = info->pwd;
  pwd = getkey_pwd();
  if (getkey(info->env, "PWD", 0) == NULL)
    info->env = addkey(info->env, "PWD", pwd, 0);
  else
    changekey(info->env, "PWD", pwd, 0);
  info->pwd = pwd;
}

static void	noparams(t_info *info)
{
  char		*home;

  if ((home = getkey(info->env, "HOME", 0)) == NULL)
    {
      my_puterror("cd: No home directory.\n");
      return ;
    }
  if (chdir(home) < 0)
    {
      my_puterror("cd: Can't change to home directory.\n");
      return ;
    }
  changepwd(info);
  info->exit_value = 0;
}

static void	oneparams(t_info *info, t_command *cmd)
{
  char		*path;

  if (!my_strcmp(cmd->argv[1], "-"))
    path = strdup(info->old_pwd);
  else
    path = strdup(cmd->argv[1]);
  if (chdir(path) < 0)
    {
      print_cderror(path);
      free(path);
      return ;
    }
  free(path);
  changepwd(info);
  info->exit_value = 0;
}

void	builtin_cd(t_command *cmd, t_status *status, t_info *info)
{
  int	argc;

  UNUSED(status);
  info->exit_value = 1;
  argc = -1;
  while (cmd->argv[++argc]);
  if (argc == 1)
    noparams(info);
  else if (argc == 2)
    oneparams(info, cmd);
  else
    my_puterror("cd: Too many arguments.\n");
}

