/*
** my_power_rec.c for my_power_rec in /home/cedric/delivery/Day05
** 
** Made by Cédric Thomas
** Login   <cedric@epitech.net>
** 
** Started on  Fri Oct  7 12:46:07 2016 Cédric Thomas
** Last update Mon Oct 10 21:32:31 2016 Cédric Thomas
*/

int	my_power_rec(int nb, int p)
{
  long	buffer;

  buffer = nb;
  if (p == 0)
    return (1);
  else if (p < 0)
    return (0);
  if (p > 1)
    {
      buffer = buffer * my_power_rec(buffer, p - 1);
    }
  if ((buffer < -2147483648) || (buffer > 2147483647))
    {
      return (0);
    }
  return (buffer);
}
