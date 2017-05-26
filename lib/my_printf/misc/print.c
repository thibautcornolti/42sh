/*
** putstr_p.c for putstr_p.c in /home/cedric/delivery/my_printf/aff_fct
** 
** Made by Cédric Thomas
** Login   <cedric@epitech.net>
** 
** Started on  Wed Nov  9 17:01:21 2016 Cédric Thomas
** Last update Mon Nov 14 20:38:09 2016 Cédric Thomas
*/
#include <unistd.h>
#include <stdlib.h>

int	putchar_i(char c)
{
  write(1, &c, 1);
  return (1);
}

int	putstr_i(char *str)
{
  int	i;

  i = 0;
  if (str == NULL)
    {
      i += putstr_i("(null)");
      return (i);
    }
  while (str[i])
    {
      putchar_i(str[i]);
      i += 1;
    }
  return (i);
}

int	putnchar_i(char c, int nb)
{
  int	i;

  i = 0;
  while (i < nb)
    {
      putchar_i(c);
      i += 1;
    }
  return (i);
}

int	putnstr_i(char *str, int n)
{
  int	i;

  i = 0;
  while (str[i] && i < n)
    {
      putchar_i(str[i]);
      i += 1;
    }
  return (i);
}
