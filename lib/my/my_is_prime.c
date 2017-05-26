/*
** my_is_prime.c for my_is_prime.c in /home/cedric/delivery/Day05
** 
** Made by Cédric Thomas
** Login   <cedric@epitech.net>
** 
** Started on  Fri Oct  7 15:11:54 2016 Cédric Thomas
** Last update Mon Oct 10 20:29:04 2016 Cédric Thomas
*/

int	my_is_prime(int nb)
{
  int	i;

  i = nb / 2;
  if (nb <= 1)
    return (0);
  while (i > 1)
    {
      if (nb % i == 0)
	return (0);
      i -= 1;
    }
  return (1);
}
