/*
** my_puterror.c for my_puterror.c in /home/cedric/delivery/MUL/wireframe
** 
** Made by Cédric Thomas
** Login   <cedric@epitech.net>
** 
** Started on  Mon Nov 21 09:08:19 2016 Cédric Thomas
** Last update Mon Nov 21 08:20:08 2016 Cédric Thomas
*/
#include <unistd.h>
#include "my.h"

void	my_puterror(char *str)
{
  write(2, str, my_strlen(str));
}
