/*
** builtins.c for 42sh in /home/thibrex/Dropbox/delivery/PSU/PSU_2016_42sh
** 
** Made by Thibaut Cornolti
** Login   <thibaut.cornolti@epitech.eu>
** 
** Started on  Thu May 18 23:57:02 2017 Thibaut Cornolti
** Last update Sun May 21 18:33:22 2017 Thibaut Cornolti
*/

#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "syntax.h"
#include "exec.h"
#include "my.h"

static int	verify_alias(t_info *info, char *str)
{
  int		i;

  i = -1;
  while (info->alias && info->alias[++i].link)
    if (!strcmp(str, info->alias[i].link))
      {
	printf("%s is aliased to %s\n", str, info->alias[i].value);
	return (1);
      }
  return (0);
}

static int	verify_builtin(t_info *info, char *str)
{
  int		i;

  i = -1;
  while (++i < BUILTINS_NB)
    if (!strcmp(str, info->builtins[i]))
      {
	printf("%s is a shell built-in\n", str);
	return (1);
      }
  return (0);
}

int	check_inpath(char **tab, char *str)
{
  char	*path;
  int	i;

  i = -1;
  while (tab[++i])
    {
      path = my_strcatdup(tab[i], "/", 0);
      path = my_strcatdup(path, str, 1);
      if (!access(path, F_OK))
	{
	  printf("%s\n", path);
	  free(path);
	  return (1);
	}
      free(path);
    }
  return (0);
}

int	verify_path(t_info *info, char *str)
{
  char	*path;
  char	**tab;
  int	value;

  if (!(path = getkey(info->env, "PATH", 1)))
    return (0);
  if (!(tab = my_split(path, ':')))
    {
      free(path);
      return (0);
    }
  free(path);
  value = check_inpath(tab, str);
  free_tab(tab);
  return (value);
}

void		builtin_where(t_command *cmd, t_status *status, t_info *info)
{
  int		i;
  int		finded;

  UNUSED(status);
  i = 0;
  info->exit_value = cmd->argv[1] ? 0 : 1;
  if (!cmd->argv[1])
    {
      printf("where: Too few arguments.\n");
      return ;
    }
  while (cmd->argv[++i])
    {
      finded = 0;
      finded += verify_alias(info, cmd->argv[i]);
      finded += verify_builtin(info, cmd->argv[i]);
      finded += verify_path(info, cmd->argv[i]);
      info->exit_value = (!info->exit_value && !finded) ? 1 :
	info->exit_value;
    }
}
