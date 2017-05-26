/*
** alias.c for 42sh in /home/rectoria/delivery/Projets/PSU_2016_42sh/parseur42/exec/builtin
** 
** Made by Bastien
** Login   <rectoria@epitech.net>
** 
** Started on  Mon May 15 15:48:20 2017 Bastien
** Last update Sun May 21 22:18:42 2017 Cédric THOMAS
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fnmatch.h>
#include "syntax.h"
#include "exec.h"
#include "my.h"

static int	show_cmd(t_info *info, char *str, int size)
{
  int		i;

  i = -1;
  while (size && info->alias[++i].link)
    {
      if (str && !strcmp(info->alias[i].link, str))
	{
	  printf("%s\n", info->alias[i].value);
	  return (0);
	}
      else if (!str)
	{
	  if (is_in(' ', info->alias[i].value))
	    printf("%s\t(%s)\n", info->alias[i].link, info->alias[i].value);
	  else
	    printf("%s\t%s\n", info->alias[i].link, info->alias[i].value);
	}
    }
  return (0);
}

static int	verify_exist(t_info *info, char *str, char *value)
{
  int		i;

  i = -1;
  while (info->alias && info->alias[++i].link)
    if (!my_strcmp(info->alias[i].link, str))
      {
	free(info->alias[i].value);
	info->alias[i].value = value;
	return (0);
      }
  return (1);
}

char	*get_whole_alias(t_command *cmd)
{
  int	i;
  char	*temp;

  i = 1;
  temp = NULL;
  while (cmd->argv[++i])
    {
      if ((temp = my_strcatdup(temp, cmd->argv[i], 1)) == NULL)
	exit(84);
      if (cmd->argv[i + 1])
	if ((temp = my_strcatdup(temp, " ", 1)) == NULL)
	  exit(84);
    }
  return (temp);
}

static int	secure_test(char *str, t_info *info)
{
  if (!strcmp("alias", str))
    {
      printf("alias: Too dangerous to alias that.\n");
      info->exit_value = 1;
    }
  if (!strcmp("unalias", str))
    {
      printf("unalias: Too dangerous to alias that.\n");
      info->exit_value = 1;
    }
  return (info->exit_value);
}

void		builtin_alias(t_command *cmd, t_status *status,
			      t_info *info)
{
  int		nb_arg;
  char		*temp;
  int		size;

  UNUSED(status);
  info->exit_value = 0;
  size = my_aliastablen(info->alias);
  nb_arg = my_strtablen(cmd->argv);
  if (nb_arg <= 2 && !show_cmd(info, cmd->argv[1], size))
    return ;
  if (secure_test(cmd->argv[1], info))
    return ;
  temp = get_whole_alias(cmd);
  if (verify_exist(info, cmd->argv[1], temp))
    {
      if (!(info->alias = realloc(info->alias, sizeof(t_alias) * (size + 2))))
	exit(84);
      memset(&info->alias[size], 0, sizeof(t_alias) * 2);
      info->alias[size].link = strdup(cmd->argv[1]);
      info->alias[size].value = temp;
    }
  nb_arg = -1;
  while (info->alias[++nb_arg].link)
    info->alias[nb_arg].loop = 0;
  check_loop(info);
}
