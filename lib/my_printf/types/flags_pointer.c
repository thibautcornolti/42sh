/*
** flags_pointer.c for my_printf in /home/cedric/delivery/my_printf
** 
** Made by Cédric Thomas
** Login   <cedric@epitech.net>
** 
** Started on  Fri Nov 11 17:05:01 2016 Cédric Thomas
** Last update Mon Nov 28 21:22:35 2016 Cédric Thomas
*/
#include <stdarg.h>
#include <limits.h>
#include <stdlib.h>
#include "my_printf.h"
#include "my.h"

static int	getlen(unsigned long long casted, t_flag *flag, char *str)
{
  int	added;

  added = 0;
  if (casted != 0)
    added += 2;
  if (flag->sign)
    added += 1;
  if (flag->precision - my_strlen(str) > 0 && casted != 0)
    added += flag->precision - my_strlen(str);
  if (flag->precision == -1 && flag->padd == '0' &&
      flag->paddlen > my_strlen(str) + added)
    {
      flag->precision = flag->paddlen - added;
      flag->paddlen = 0;
    }
  return (added);
}

int			flag_p(va_list *arg, t_flag *flag)
{
  unsigned long long	casted;
  char			*str;
  int			size;
  int			added;

  size = 0;
  casted = (unsigned long long) va_arg(*arg, long long);
  if (casted != 0)
    str = u_convertbase(casted, "0123456789abcdef");
  else
    str = my_strdup("(nil)");
  added = getlen(casted, flag, str);
  if (flag->padd != '-')
    size += putnchar_i(' ', flag->paddlen - (my_strlen(str) + added));
  if (flag->sign != 0)
    size += putchar_i(flag->sign);
  if (casted != 0)
    size += putstr_i("0x");
  if (flag->precision != 1 && casted != 0)
    size += putnchar_i('0', flag->precision - my_strlen(str));
  size += putstr_i(str);
  if (flag->padd == '-')
    size += putnchar_i(' ', flag->paddlen - (my_strlen(str) + added));
  free(str);
  return (size);
}
