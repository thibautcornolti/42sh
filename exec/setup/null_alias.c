/*
** null_alias.c for 42sh in /home/rectoria/delivery/Projets/PSU_2016_42sh
** 
** Made by Bastien
** Login   <rectoria@epitech.net>
** 
** Started on  Sun May 21 23:02:37 2017 Bastien
** Last update Sun May 21 23:06:47 2017 Bastien
*/

#include <string.h>
#include <stdlib.h>
#include "syntax.h"
#include "exec.h"

int	null_alias(t_token *token)
{
  free(token->token);
  token->token = strdup("\0");
  return (0);
}
