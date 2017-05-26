/*
** padd.c for my_printf in /home/cedric/delivery/my_printf
** 
** Made by Cédric Thomas
** Login   <cedric@epitech.net>
** 
** Started on  Sat Nov 12 22:41:59 2016 Cédric Thomas
** Last update Mon Nov 28 21:37:55 2016 Cédric Thomas
*/
#include <stdlib.h>
#include "my_printf.h"
#include "my.h"

int	paddchar(char c, t_flag *flag, int len)
{
  int	i;
  int	padd;

  i = 0;
  if (flag->precision < len && flag->precision != -1)
    padd = flag->paddlen - flag->precision;
  else
    padd = flag->paddlen - len;
  while (i < padd)
    {
      putchar_i(c);
      i += 1;
    }
  return (i);
}

int	paddit(t_flag *flag, int precis, char mod, char *str)
{
  int	size;

  size = 0;
  if (flag->padd == 0)
    flag->padd = ' ';
  if (flag->padd == '0' && flag->precision >= 0)
    flag->padd = ' ';
  if (flag->padd == '0' && flag->precision == -1 && str[0])
    {
      flag->precision = flag->paddlen;
      return (size);
    }
  if (mod == 'g' && flag->padd != '-')
    size += putnchar_i(flag->padd, flag->paddlen - precis);
  else if  (mod == 'd' && flag->padd == '-')
    size += putnchar_i(' ', flag->paddlen - precis);
  return (size);
}

int	getlenprecision(t_flag *flag, char *str, int lenadded, long long *nb)
{
  int	size;
  int	i;

  size = 0;
  i = 0;
  if (str[0] == '-')
    i += 1;
  if (flag->sign != 0 || str[0] == '-')
    size += 1;
  if (flag->precision >= my_strlen(str) + lenadded)
    size += flag->precision - (my_strlen(str) + lenadded - i);
  while (i < my_strlen(str) + lenadded && !(*nb == 0 && flag->precision == 0))
    {
      size += 1;
      i += 1;
    }
  return (size);
}

int	precision(t_flag *flag, char *str, int lenadded, long long *nb)
{
  int	size;
  char	sign;
  int	i;

  size = 0;
  sign = 0;
  i = 0;
  if (flag->sign != 0)
    sign = flag->sign;
  if  (str[0] == '-')
    {
      sign = '-';
      i += 1;
    }
  if (sign != 0)
    size += putchar_i(sign);
  if (flag->precision >= my_strlen(str) + lenadded)
    size += putnchar_i('0', flag->precision - (my_strlen(str) + lenadded - i));
  while (str[i] && !(*nb == 0 && flag->precision == 0))
    {
      size += putchar_i(str[i]);
      i += 1;
    }
  return (size);
}

long long	cast(t_flag *flag, va_list *arg, char sign)
{
  long long casted;

  if (strcmp_i("l", flag->len) == 0)
    casted = va_arg(*arg, long);
  else if (strcmp_i("ll", flag->len) == 0)
      casted = va_arg(*arg, long long);
  if (sign =='s')
    {
      if (strcmp_i("h", flag->len) == 0)
  	casted = (short int) va_arg(*arg, int);
      else if (strcmp_i("hh", flag->len) == 0)
  	casted = (char) va_arg(*arg, int);
      else if (flag->len[0] == 0)
  	casted = (int)va_arg(*arg, int);
    }
  else
    {
      if (strcmp_i("h", flag->len) == 0)
  	casted = (unsigned short int) va_arg(*arg, int);
      else if (strcmp_i("hh", flag->len) == 0)
  	casted = (unsigned char) va_arg(*arg, int);
      else if (flag->len[0] == 0)
  	casted = (unsigned int) va_arg(*arg, int);
    }
  return (casted);
}
