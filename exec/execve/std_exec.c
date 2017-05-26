/*
** std_exec.c for 42sh in /home/cedric/delivery/PSU/PSU_2016_42sh/parseur 42
** 
** Made by Cédric THOMAS
** Login   <cedric.thomas@epitech.eu>
** 
** Started on  Wed May 10 22:32:29 2017 
** Last update Sun May 21 22:17:21 2017 Thibaut Cornolti
*/
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <termio.h>
#include "syntax.h"
#include "exec.h"
#include "get_next_command.h"
#include "my_alloc.h"
#include "my.h"

static void	check_errno(char *str)
{
  my_puterror(str);
  my_puterror(": ");
  if (ENOEXEC == errno)
    my_perror(str, "Exec format error. Binary file not executable.\n");
  else
    perror(str);
  exit(1);
}

static char	**my_tabdup(char **tab)
{
  int		i;
  int		len;
  char		**res;

  len = -1;
  while (tab[++len]);
  if ((res = malloc(sizeof(char *) * (len + 1))) == NULL)
    return (NULL);
  i = -1;
  while (tab[++i])
    res[i] = my_strdup(tab[i]);
  res[i] = NULL;
  return (res);
}

static void	free_son(t_info *info)
{
  t_system *system;

  my_free_history(&(info->histo->start));
  free(info->histo);
  free(info->pwd);
  free(info->old_pwd);
  free_tab(info->env);
  free_alias(info->alias);
  free_var(info->var);
  my_free_tag("tree", 0);
  system = getter_system(NULL);
  end_keypad(system->keypad);
  free_syntax(&(system->syntax));
}

void	simple_exec(t_command *cmd, t_status *status, t_info *info)
{
  char	*path;
  char	*path_cmd;
  char	**env;
  char	**argv;

  UNUSED(status);
  path = my_pathfinder(cmd, info);
  if ((env = my_tabdup(info->env)) == NULL ||
      (argv = my_tabdup(cmd->argv)) == NULL ||
      (path_cmd = my_strdup(cmd->path)) == NULL)
    exit(84);
  free_son(info);
  if (path && execve(path, argv, env))
    check_errno(path_cmd);
  free_tab(env);
  free_tab(argv);
  free(path);
  free(path_cmd);
}
