/*
** info.c for 42Sh in /home/cedric/Desktop/parseur 42/exec
** 
** Made by Cédric THOMAS
** Login   <cedric.thomas@epitech.eu>
** 
** Started on  Tue May  9 09:30:17 2017 
** Last update Sun May 21 23:44:38 2017 Thibaut Cornolti
*/

#include <stdlib.h>
#include <string.h>
#include "syntax.h"
#include "exec.h"
#include "my.h"

static void	get_builtins(t_info *my_info)
{
  my_info->builtins[0] = "exit";
  my_info->builtins[1] = "cd";
  my_info->builtins[2] = "setenv";
  my_info->builtins[3] = "unsetenv";
  my_info->builtins[4] = "echo";
  my_info->builtins[5] = "alias";
  my_info->builtins[6] = "unalias";
  my_info->builtins[7] = "fg";
  my_info->builtins[8] = "bg";
  my_info->builtins[9] = "jobs";
  my_info->builtins[10] = "set";
  my_info->builtins[11] = "unset";
  my_info->builtins[12] = "builtins";
  my_info->builtins[13] = "history";
  my_info->builtins[14] = "chdir";
  my_info->builtins[15] = "where";
  my_info->builtins[16] = NULL;
}

static int	setup_history(t_info *info)
{
  if ((info->histo = malloc(sizeof(t_history_info))) == NULL)
    exit(84);
  memset(info->histo, 0, sizeof(t_history_info));
  info->alias = 0;
  info->var = 0;
  info->exit_arg = 0;
  return (0);
}

t_info		*get_info(char **env)
{
  char		*temp;
  t_info	*my_info;

  if ((my_info = malloc(sizeof(t_info))) == NULL)
    return (NULL);
  if ((my_info->env = tab_dup(env)) == NULL)
    return (NULL);
  my_info->exit_value = 0;
  if ((temp = getkey_pwd()) == NULL)
    return (NULL);
  if (changekey(my_info->env, "PWD", temp, 0))
    my_info->env = addkey(my_info->env, "PWD", temp, 0);
  my_info->pwd = temp;
  if ((my_info->old_pwd = my_strdup("")) == NULL)
    return (NULL);
  if ((temp = getkey_hostname()) == NULL)
    return (NULL);
  if (changekey(my_info->env, "HOST", temp, 0))
    my_info->env = addkey(my_info->env, "HOST", temp, 0);
  free(temp);
  get_builtins(my_info);
  if (setup_history(my_info) == -1)
    return (NULL);
  return (my_info);
}

void		*free_info(t_info **info)
{
  my_free_history(&((*info)->histo->start));
  free((*info)->histo);
  free((*info)->pwd);
  free((*info)->old_pwd);
  free_tab((*info)->env);
  free_alias((*info)->alias);
  free_var((*info)->var);
  free(*info);
  *info = NULL;
  return (NULL);
}
