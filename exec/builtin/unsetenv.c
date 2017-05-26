/*
** unsetenv.c for builtin in /home/thibrex/Dropbox/delivery/PSU/PSU_2016_42sh/parseur 42/exec/builtin
** 
** Made by Thibaut Cornolti
** Login   <thibaut.cornolti@epitech.eu>
** 
** Started on  Thu May 11 13:22:48 2017 Thibaut Cornolti
** Last update Sun May 21 18:35:06 2017 Thibaut Cornolti
*/

#include "syntax.h"
#include "exec.h"
#include "my.h"

void		builtin_unsetenv(t_command *cmd, t_status *status,
				 t_info *info)
{
  int		argc;
  int		i;

  argc = 0;
  while (cmd->argv[argc])
    argc += 1;
  i = 0;
  info->exit_value = 0;
  if (argc <= 1)
    {
      info->exit_value = 1;
      my_puterror("unsetenv: Too few arguments.\n");
    }
  else
    while (cmd->argv[++i])
      info->env = deletekey(info->env, cmd->argv[i], 0);
  UNUSED(status);
}
