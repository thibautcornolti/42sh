/*
** fork.c for mysh.c in /home/cedric/delivery/PSU/PSU_2016_minishell1
** 
** Made by 
** Login   <cedric.thomas@epitech.eu>
** 
** Started on  Tue Jan 10 16:30:38 2017 
** Last update Sun May 21 22:30:35 2017 Cédric THOMAS
*/

#include <signal.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include "syntax.h"
#include "exec.h"
#include "my_alloc.h"
#include "my.h"

static int	check_error(char *path, char *exec_name, t_info *info)
{
  int		isadir;
  struct stat	mstat;

  isadir = 0;
  if (path && !stat(path, &mstat))
    isadir = S_ISDIR(mstat.st_mode);
  if (!path || (access(path, F_OK) || !is_in('/', path)))
    {
      my_puterror(exec_name);
      my_puterror(": Command not found.\n");
      info->exit_value = 1;
      return (1);
    }
  else if ((path && access(path, X_OK)) || isadir)
    {
      my_puterror(exec_name);
      my_puterror(": Permission denied.\n");
      info->exit_value = 1;
      return (1);
    }
  return (0);
}

static char	**get_full_path(t_info *info, char *exec_name)
{
  int		i;
  char		**paths;

  if ((paths = my_split(getkey(info->env, "PATH", 0), ':')) == NULL)
    if ((paths = my_split("/bin:/usr/bin", ':')) == NULL)
      exit(84);
  i = -1;
  while (paths[++i])
    {
      if (paths[i][my_strlen(paths[i])] != '/')
	paths[i] = my_strcatdup(paths[i], "/", 1);
      paths[i] = my_strcatdup(paths[i], exec_name, 1);
    }
  return (paths);
}

static char	*identify_path(char *exec_name, t_info *info)
{
  int		i;
  char		*my_path;
  char		**paths;

  i = -1;
  my_path = NULL;
  paths = get_full_path(info, exec_name);
  while (paths[++i] && !my_path)
    if (!access(paths[i], F_OK))
      {
	my_path = my_strdup(paths[i]);
      }
  free_tab(paths);
  return (my_path);
}

char		*my_pathfinder(t_command *cmd, t_info *info)
{
  char		*path;

  if (is_in('/', cmd->path))
    {
      if (!check_error(cmd->path, cmd->path, info))
	return (my_strdup(cmd->path));
      else
	return (NULL);
    }
  path = identify_path(cmd->path, info);
  if (check_error(path, cmd->path, info))
    {
      free(path);
      path = NULL;
    }
  return (path);
}
