/*
** my_swap.c for my_swap.c in /home/cedric/delivery/CPool_Day04
** 
** Made by Cédric Thomas
** Login   <cedric@epitech.net>
** 
** Started on  Thu Oct  6 10:49:52 2016 Cédric Thomas
** Last update Thu Oct  6 16:27:46 2016 Cédric Thomas
*/

int	my_swap(int *a, int *b)
{
  int	buffer;

  buffer = *a;
  *a = *b;
  *b = buffer;
  return (0);
}
