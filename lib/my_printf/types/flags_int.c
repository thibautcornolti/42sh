/*
** flags_int.c for my_printf in /home/cedric/delivery/my_printf
** 
** Made by Cédric Thomas
** Login   <cedric@epitech.net>
** 
** Started on  Wed Nov  9 10:52:20 2016 Cédric Thomas
** Last update Mon Nov 28 21:23:02 2016 Cédric Thomas
*/
#include <limits.h>
#include <stdlib.h>
#include "my_printf.h"

int		flag_d(va_list *args, t_flag *flag)
{
  int	        preci;
  int		added;
  int		size;
  long long	casted;
  char		*str;

  size = 0;
  added = 0;
  casted = cast(flag, args, 's');
  str = convertbase(casted, "0123456789");
  if (str[0] == '-' && flag->padd == '0')
    added += 1;
  preci = getlenprecision(flag, str, added, &casted);
  size += paddit(flag, preci, 'g', str);
  size += precision(flag, str, added, &casted);
  size += paddit(flag, preci, 'd', str);
  free(str);
  return (size);
}

int			flag_u(va_list *args, t_flag *flag)
{
  int			preci;
  int			size;
  unsigned long long	casted;
  char			*str;

  size = 0;
  casted = (unsigned long long) cast(flag, args, 'u');
  flag->sign = 0;
  str = u_convertbase(casted, "0123456789");
  preci = getlenprecision(flag, str, 0, &casted);
  size += paddit(flag, preci, 'g', str);
  size += precision(flag, str, 0, &casted);
  size += paddit(flag, preci, 'd', str);
  free(str);
  return (size);
}
