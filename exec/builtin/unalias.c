/*
** unalias.c for 42sh in /home/rectoria/delivery/Projets/PSU_2016_42sh
** 
** Made by Bastien
** Login   <rectoria@epitech.net>
** 
** Started on  Thu May 18 09:29:45 2017 Bastien
** Last update Sun May 21 22:19:34 2017 Cédric THOMAS
*/

#include <stdlib.h>
#include <string.h>
#include "syntax.h"
#include "exec.h"

void		remove_alias(t_info *info, int j)
{
  int		size;
  t_alias	temp;

  size = my_aliastablen(info->alias);
  while (++j < size)
    {
      temp.link = info->alias[j].link;
      temp.value = info->alias[j].value;
      info->alias[j].link = info->alias[j + 1].link;
      info->alias[j].value = info->alias[j + 1].value;
      info->alias[j + 1].link = temp.link;
      info->alias[j + 1].value = temp.value;
    }
  if ((info->alias = realloc(info->alias, sizeof(t_alias) * size)) == NULL)
    exit(84);
}

void	builtin_unalias(t_command *cmd, t_status *status, t_info *info)
{
  int	i;
  int	j;

  (void)status;
  info->exit_value = 0;
  i = 0;
  while (cmd->argv[++i])
    {
      j = -1;
      while (info->alias && info->alias[++j].link)
	if (!strcmp(info->alias[j].link, cmd->argv[i]))
	  {
	    remove_alias(info, j - 1);
	    break ;
	  }
    }
  i = -1;
  while (info->alias[++i].link)
    info->alias[i].loop = 0;
  check_loop(info);
}
