/*
** flags_base.c for my_printf.c in /home/cedric/delivery/my_printf/types
** 
** Made by Cédric Thomas
** Login   <cedric@epitech.net>
** 
** Started on  Sat Nov 12 08:38:21 2016 Cédric Thomas
** Last update Mon Nov 28 21:32:31 2016 Cédric Thomas
*/
#include <limits.h>
#include <stdlib.h>
#include "my_printf.h"

int		flag_x(va_list *args, t_flag *flag)
{
  int			preci;
  int			addlen;
  int			size;
  unsigned long long	casted;
  char			*str;

  size = 0;
  addlen = 0;
  casted = (unsigned long long) cast(flag, args, 'u');
  flag->sign = 0;
  str = u_convertbase(casted, "0123456789abcdef");
  if (flag->form == '#')
    addlen += 2;
  preci = getlenprecision(flag, str, addlen, &casted);
  size += paddit(flag, preci, 'g', str);
  if (flag->form == '#')
    size += putstr_i("0x");
  size += precision(flag, str, addlen, &casted);
  size += paddit(flag, preci, 'd', str);
  free(str);
  return (size);
}

int		flag_xmaj(va_list *args, t_flag *flag)
{
  int			preci;
  int			addlen;
  int			size;
  unsigned long long	casted;
  char			*str;

  size = 0;
  addlen = 0;
  casted = (unsigned long long) cast(flag, args, 'u');
  flag->sign = 0;
  str = u_convertbase(casted, "0123456789ABCDEF");
  if (flag->form == '#')
    addlen += 2;
  preci = getlenprecision(flag, str, addlen, &casted);
  size += paddit(flag, preci, 'g', str);
  if (flag->form == '#')
    size += putstr_i("0X");
  size += precision(flag, str, addlen, &casted);
  size += paddit(flag, preci, 'd', str);
  free(str);
  return (size);
}

int		flag_b(va_list *args, t_flag *flag)
{
  int			preci;
  int			addlen;
  int			size;
  unsigned long long	casted;
  char			*str;

  size = 0;
  addlen = 0;
  casted = (unsigned long long) cast(flag, args, 'u');
  flag->sign = 0;
  str = u_convertbase(casted, "01");
  if (flag->form == '#')
    addlen += 2;
  preci = getlenprecision(flag, str, addlen, &casted);
  size += paddit(flag, preci, 'g', str);
  if (flag->form == '#')
    size += putstr_i("0b");
  size += precision(flag, str, addlen, &casted);
  size += paddit(flag, preci, 'd', str);
  free(str);
  return (size);
}

int		flag_o(va_list *args, t_flag *flag)
{
  int			preci;
  int			addlen;
  int			size;
  unsigned long long	casted;
  char			*str;

  size = 0;
  addlen = 0;
  casted = (unsigned long long) cast(flag, args, 'u');
  flag->sign = 0;
  str = u_convertbase(casted, "01234567");
  if (str[0] != '0' && flag->form == '#')
    addlen += 1;
  preci = getlenprecision(flag, str, addlen, &casted);
  size += paddit(flag, preci, 'g', str);
  if (str[0] != '0' && flag->form == '#')
    size += putchar_i('0');
  size += precision(flag, str, addlen, &casted);
  size += paddit(flag, preci, 'd', str);
  free(str);
  return (size);
}
