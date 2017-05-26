/*
** my_putchar.c for my_putchar.c in /home/cedric/delivery/CPool_Day07/lib/my
** 
** Made by Cédric Thomas
** Login   <cedric@epitech.net>
** 
** Started on  Tue Oct 11 17:12:01 2016 Cédric Thomas
** Last update Fri Nov 18 08:51:08 2016 Cédric Thomas
*/
#include <unistd.h>

int	my_putchar(char c)
{
  write(1, &c, 1);
}
