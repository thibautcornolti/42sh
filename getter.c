/*
** getter.c for 42sh in /home/thibrex/Dropbox/delivery/PSU/PSU_2016_42sh
** 
** Made by Thibaut Cornolti
** Login   <thibaut.cornolti@epitech.eu>
** 
** Started on  Wed May 17 13:47:54 2017 Thibaut Cornolti
** Last update Fri May 19 00:05:43 2017 Thibaut Cornolti
*/

#include <stdlib.h>
#include "syntax.h"
#include "exec.h"

t_system		*getter_system(t_system *setter)
{
  static t_system	*system = NULL;

  if (setter)
    system = setter;
  return (system);
}
