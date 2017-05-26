/*
** setenv.c for builtin in /home/thibrex/Dropbox/delivery/PSU/PSU_2016_42sh/parseur 42/exec/builtin
** 
** Made by Thibaut Cornolti
** Login   <thibaut.cornolti@epitech.eu>
** 
** Started on  Thu May 11 13:22:48 2017 Thibaut Cornolti
** Last update Fri May 12 16:48:01 2017 Thibaut Cornolti
*/

#include <stdlib.h>
#include "syntax.h"
#include "exec.h"
#include "my.h"

static void	my_setenv(t_info *info, char *key, char *value)
{
  int		i;

  i = -1;
  while (key[++i])
    {
      if (i == 0 && !is_betw('A', key[i], 'Z') && !is_betw('a', key[i], 'z'))
      	{
      	  my_puterror("setenv: Variable name must begin with a letter.\n");
	  info->exit_value = 1;
      	  return ;
      	}
      else if (!is_betw('A', key[i], 'Z') && !is_in(key[i], "_")
      	       && !is_betw('a', key[i], 'z') && !is_betw('0', key[i], '9'))
      	{
      	  my_puterror("setenv: Variable name must");
      	  my_puterror(" contain alphanumeric characters.\n");
	  info->exit_value = 1;
      	  return ;
      	}
    }
  if (getkey(info->env, key, 0) == NULL)
    info->env = addkey(info->env, key, value, 0);
  else
    changekey(info->env, key, value, 0);
}

void		builtin_setenv(t_command *cmd, t_status *status, t_info *info)
{
  int		argc;

  argc = 0;
  UNUSED(status);
  while (cmd->argv[argc])
    argc += 1;
  info->exit_value = 0;
  if (argc == 1 && cmd->argv)
    my_show_wordtab(info->env);
  else if (argc == 2)
    my_setenv(info, cmd->argv[1], "");
  else if (argc == 3)
    my_setenv(info, cmd->argv[1], cmd->argv[2]);
  else
    {
      my_puterror("setenv: Too many arguments.\n");
      info->exit_value = 1;
    }
}
