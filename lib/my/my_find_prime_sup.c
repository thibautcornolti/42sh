/*
** my_find_prime_sup.c for my_find_prime_sup.c in /home/cedric/delivery/CPool_Day05
** 
** Made by Cédric Thomas
** Login   <cedric@epitech.net>
** 
** Started on  Fri Oct  7 16:54:47 2016 Cédric Thomas
** Last update Fri Nov 18 08:50:05 2016 Cédric Thomas
*/
#include "my.h"

int	my_find_prime_sup(int nb)
{
  while (!(my_is_prime(nb)))
    {
      nb += 1;
    }
  return (nb);
}
