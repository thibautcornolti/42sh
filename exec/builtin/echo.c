/*
** echo.c for builtin in /home/thibrex/Dropbox/delivery/PSU/PSU_2016_42sh/parseur 42/exec/builtin
** 
** Made by Thibaut Cornolti
** Login   <thibaut.cornolti@epitech.eu>
** 
** Started on  Thu May 11 13:22:48 2017 Thibaut Cornolti
** Last update Sat May 20 13:37:24 2017 Thibaut Cornolti
*/

#include <stdio.h>
#include <string.h>
#include "syntax.h"
#include "my_printf.h"
#include "exec.h"
#include "my.h"

void		builtin_echo(t_command *cmd, t_status *status, t_info *info)
{
  int		i;
  int		new_line;

  i = 0;
  UNUSED(status);
  info->exit_value = 0;
  new_line = 1;
  if (cmd->argv[1] && !strcmp(cmd->argv[1], "-n"))
    {
      new_line = 0;
      i += 1;
    }
  while (cmd->argv[++i])
    {
      my_printf("%s", cmd->argv[i]);
      if (cmd->argv[i + 1])
	my_printf("%s", " ");
    }
  if (new_line)
    my_printf("%s", "\n");
  info->exit_value = 0;
}
