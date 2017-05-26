/*
** format.c for format.c in /home/cedric/delivery/my_printf
** 
** Made by Cédric Thomas
** Login   <cedric@epitech.net>
** 
** Started on  Sat Nov 12 14:26:19 2016 Cédric Thomas
** Last update Mon Nov 28 21:37:38 2016 Cédric Thomas
*/
#include <stdlib.h>
#include <stdarg.h>
#include "my_printf.h"
#include "my.h"

void	fill_flag(int *i, const char *format, t_flag *flag)
{
  flag->form = 0;
  flag->sign = 0;
  flag->padd = 0;
  while (is_in(format[*i], "#0- +"))
    {
      if ((format[*i] == '0' && flag->padd != '-') || format[*i] == '-')
	  flag->padd = format[*i];
      else if ((format[*i] == ' ' && flag->sign != '+') || format[*i] == '+')
	  flag->sign = format[*i];
      if (format[*i] == '#')
	flag->form = '#';
      *i += 1;
    }
}

void	fill_width(int *i, const char *format, t_flag *flag, va_list *arg)
{
  int	width;

  width = 0;
  if (is_in(format[*i], "0123456789"))
    {
      while (is_in(format[*i], "0123456789"))
	{
	  width = width * 10 + (format[*i] - '0');
	  *i += 1;
	}
    }
  else if (format[*i] == '*')
    {
      width = va_arg(*arg, int);
      *i += 1;
    }
  flag->paddlen = width;
}

void	fill_precision(int *i, const char *format, t_flag *flag, va_list *arg)
{
  int	precision;

  precision = -1;
  if (format[*i] == '.')
    *i += 1;
  else
    {
      flag->precision = precision;
      return ;
    }
  precision = 0;
  if (is_in(format[*i], "0123456789"))
    {
      while (is_in(format[*i], "0123456789"))
	{
	  precision = precision * 10 + (format[*i] - '0');
	  *i += 1;
	}
    }
  else if (format[*i] == '*')
    {
      precision = va_arg(*arg, int);
      *i += 1;
    }
  flag->precision = precision;
}

int	fill_len(int *i, const char *format, t_flag *flag)
{
  if ((flag->len = malloc(3)) == NULL)
    return (1);
  flag->len[0] = 0;
  flag->len[1] = 0;
  flag->len[2] = 0;
  if (is_in(format[*i], "hl"))
    {
      flag->len[0] = format[*i];
      *i += 1;
    }
  if (format[*i] == flag->len[0])
    {
      flag->len[1] = format[*i];
      *i += 1;
    }
  return (0);
}
