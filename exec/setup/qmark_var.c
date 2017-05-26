/*
** qmark_var.c for 42sh in /home/rectoria/delivery/Projets/PSU_2016_42sh
** 
** Made by Bastien
** Login   <rectoria@epitech.net>
** 
** Started on  Sat May 20 15:03:24 2017 Bastien
** Last update Sun May 21 17:25:11 2017 Thibaut Cornolti
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "syntax.h"
#include "exec.h"
#include "my_alloc.h"
#include "my.h"

void	   	free_var(t_var *var)
{
  int		i;

  i = -1;
  while (var && var[++i].name)
    {
      free(var[i].name);
      free(var[i].value);
    }
  free(var);
}

int		qmark_var(t_info *info, t_command *cmd, int pos)
{
  char		*temp;
  int		len;
  char		*nbr;

  asprintf(&nbr, "%d", info->exit_value);
  len = my_cstrlen(cmd->argv[pos], '$');
  if (!(temp = my_alloc(sizeof(char) * (len + my_strlen(nbr) + 1))))
    return (1);
  my_tag_alloc(temp, "tree", 0);
  temp = (len > 0) ? strncat(temp, cmd->argv[pos], len) : temp;
  temp = strncat(temp, nbr, my_strlen(nbr));
  my_vfree((void **)(&cmd->argv[pos]), NULL);
  cmd->argv[pos] = temp;
  return (0);
}
