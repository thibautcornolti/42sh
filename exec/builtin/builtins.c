/*
** builtins.c for 42sh in /home/thibrex/Dropbox/delivery/PSU/PSU_2016_42sh
** 
** Made by Thibaut Cornolti
** Login   <thibaut.cornolti@epitech.eu>
** 
** Started on  Thu May 18 23:57:02 2017 Thibaut Cornolti
** Last update Sat May 20 20:05:04 2017 Thibaut Cornolti
*/

#include <stdlib.h>
#include "syntax.h"
#include "exec.h"
#include "my.h"

void		builtin_builtins(t_command *cmd, t_status *status,
				 t_info *info)
{
  char		*builtins;
  int		i;

  UNUSED(cmd);
  UNUSED(status);
  i = -1;
  if ((builtins = my_strdup("echo ")) == NULL)
    return ;
  while (++i < BUILTINS_NB)
    {
      builtins = my_strcatdup(builtins, info->builtins[i], 1);
      builtins = my_strcatdup(builtins, "\n", 1);
    }
  builtins = my_strcatdup(builtins, " | sort | column", 1);
  my_system(builtins, getter_system(NULL));
  info->exit_value = 0;
}
