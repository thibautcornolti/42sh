/*
** my_square_root.c for my_square_root.c in /home/cedric/delivery/Day05
** 
** Made by Cédric Thomas
** Login   <cedric@epitech.net>
** 
** Started on  Fri Oct  7 14:00:12 2016 Cédric Thomas
** Last update Sat Oct  8 18:14:38 2016 Cédric Thomas
*/

int	my_square_root(int nb)
{
  int	square;
  int	i;

  square = nb / 2;
  if (nb == 1)
    return (1);
  while (square > 0)
    {
      i = square * square;
      if (i < nb)
	return (0);
      if (i == nb)
	return (square);
      square -= 1;
    }
  return (0);
}
