/*
** is_nb.c for is_nb.c in /home/cedric/delivery/MUL/wireframe
** 
** Made by Cédric Thomas
** Login   <cedric@epitech.net>
** 
** Started on  Mon Nov 21 09:06:02 2016 Cédric Thomas
** Last update Mon Nov 21 09:07:03 2016 Cédric Thomas
*/
#include "my.h"

int	is_nb(char c)
{
  if (is_in(c, "0123456789"))
    return (1);
  return (0);
}
