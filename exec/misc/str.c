/*
** str.c for 42Sh in /home/cedric/delivery/PSU/PSU_2016_42sh/parseur 42/exec
** 
** Made by Cédric THOMASCédric Thomas
** Login   <cedric.thomas@epitech.eu>
** 
** Started on  Thu May 11 15:58:47 2017 Cédric Thomas
** Last update Thu May 11 16:00:31 2017 Cédric Thomas
*/
#include "my.h"

int	my_perror(char *cmd, char *error)
{
  my_puterror(cmd);
  my_puterror(": ");
  my_puterror(error);
  return (1);
}
