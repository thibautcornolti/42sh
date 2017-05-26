/*
** alias_len.c for 42sh in /home/rectoria/delivery/Projets/PSU_2016_42sh
** 
** Made by Bastien
** Login   <rectoria@epitech.net>
** 
** Started on  Wed May 17 22:33:50 2017 Bastien
** Last update Sat May 20 19:51:14 2017 Thibaut Cornolti
*/

#include "syntax.h"
#include "exec.h"

int	my_strtablen(char **tab)
{
  int	i;

  i = -1;
  while (tab && tab[++i]);
  return (i < 0 ? 0 : i);
}

int	my_aliastablen(t_alias *alias)
{
  int	i;

  i = -1;
  while (alias && alias[++i].link);
  return (i < 0 ? 0 : i);
}
