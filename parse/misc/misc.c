/*
** str.c for asm in /home/cedric/delivery/CPE/CPE_2016_corewar/asm
** 
** Made by 
** Login   <cedric.thomas@epitech.eu>
** 
** Started on  Wed Mar  1 15:05:53 2017 
** Last update Fri May 12 17:00:56 2017 Thibaut Cornolti
*/
#include <unistd.h>
#include <stdlib.h>
#include "my.h"

int	my_log2(int log)
{
  int	i;

  i = -1;
  while (1 << ++i < log);
  return (i);
}

void	*my_free_null(void *ptr)
{
  free(ptr);
  return (NULL);
}

int	my_putfd(int fd, char *str)
{
  int	i;

  i = 0;
  if  (str == NULL)
    return (1);
  while (str[i])
    i += 1;
  write(fd, str, i);
  return (1);
}
