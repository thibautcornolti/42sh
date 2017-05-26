/*
** inter.c for mysh in /home/cedric/delivery/PSU/PSU_2016_minishell2
** 
** Made by 
** Login   <cedric.thomas@epitech.eu>
** 
** Started on  Tue Mar 28 22:36:31 2017 
** Last update Sun May 21 21:53:45 2017 Thibaut Cornolti
*/
#include <stdlib.h>
#include "syntax.h"
#include "exec.h"

static void	get_fct(t_exec_fct parse[TREE_TYPES])
{
  parse[0].type = T_COMMAND;
  parse[0].fct = &exec_cmd;
  parse[1].type = T_FLUX;
  parse[1].fct = &exec_pipe;
  parse[2].type = T_SEPAR;
  parse[2].fct = &exec_separ;
  parse[3].type = T_LOGIC_AND;
  parse[3].fct = &exec_logic;
  parse[4].type = T_LOGIC_OR;
  parse[4].fct = &exec_logic;
  parse[5].type = T_JOB;
  parse[5].fct = &exec_job;
  parse[6].type = T_BACKQUOTE;
  parse[6].fct = NULL;
}

int		auto_select(t_node *root, t_status *status, t_info *info)
{
  t_exec_fct	fct_parse[TREE_TYPES];
  int		i;

  i = -1;
  if (root == NULL || info->exit_arg)
    return (0);
  get_fct(fct_parse);
  if (root->type & T_SEPAR)
    status->pgid = 0;
  status->job_nbr = get_free_job(status->exit_list);
  while (++i < TREE_TYPES)
    {
      if (root->type == fct_parse[i].type)
	if (fct_parse[i].fct != NULL)
	  return (fct_parse[i].fct(root, status, info));
    }
  return (0);
}
