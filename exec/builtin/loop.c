/*
** loop.c for 42sh in /home/rectoria/delivery/Projets/PSU_2016_42sh
** 
** Made by Bastien
** Login   <rectoria@epitech.net>
** 
** Started on  Tue May 16 19:00:41 2017 Bastien
** Last update Sun May 21 18:34:52 2017 Thibaut Cornolti
*/

#include <string.h>
#include "syntax.h"
#include "exec.h"

static void	set_loop(t_info *info, int value, int j)
{
  int		i;

  i = -1;
  if (value)
    info->alias[j].loop = value;
  while (info->alias[++i].link)
    info->alias[i].loop = (info->alias[i].loop == 2)
      ? value : info->alias[i].loop;
}

void	check_loop(t_info *info)
{
  int	i;
  int	j;
  char	*temp;
  char	*witness;

  i = -1;
  while (info->alias[++i].link)
    if (!info->alias[i].loop)
      {
	witness = info->alias[i].link;
	temp = info->alias[i].value;
	info->alias[i].loop = 2;
	j = -1;
	while (info->alias[++j].link && strcmp(temp, witness))
	  if (!strcmp(temp, info->alias[j].link) && !info->alias[j].loop)
	    {
	      temp = info->alias[j].value;
	      info->alias[j].loop = 2;
	      j = -1;
	    }
	set_loop(info, (info->alias[j].link) ? 1 : 0, j);
      }
}
