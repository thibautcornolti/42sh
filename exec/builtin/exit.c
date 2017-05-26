/*
** exit.c for builtin in /home/thibrex/Dropbox/delivery/PSU/PSU_2016_42sh/parseur 42/exec/builtin
** 
** Made by Thibaut Cornolti
** Login   <thibaut.cornolti@epitech.eu>
** 
** Started on  Thu May 11 13:22:48 2017 Thibaut Cornolti
** Last update Thu May 11 21:27:25 2017 
*/

#include "syntax.h"
#include "exec.h"
#include "my.h"

static void	check_syntax(char *arg, t_info *info, t_status *status)
{
  int		i;

  i = 0;
  while (arg[i] && (is_nb(arg[i]) || (i == 0 && arg[0] == '-')))
    i += 1;
  if (!arg[i])
    {
      info->exit_value = my_getnbr(arg);
      status->exit = 1;
      return ;
    }
  else if (!is_nb(arg[i]) && i > 0)
    my_puterror("exit: Badly formed number.\n");
  else if (!is_nb(arg[i]))
    my_puterror("exit: Expression Syntax.\n");
  info->exit_value = 1;
}

void		builtin_exit(t_command *cmd, t_status *status, t_info *info)
{
  int		argc;

  argc = 0;
  while (cmd->argv[argc])
    argc += 1;
  info->exit_value = 0;
  if (argc == 1)
    status->exit = 1;
  else if (argc == 2)
    check_syntax(cmd->argv[1], info, status);
  else
    {
      info->exit_value = 1;
      my_puterror("exit: Expression Syntax.\n");
    }
}
