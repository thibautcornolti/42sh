/*
** printformat.c for printformat.c in /home/cedric/delivery/PSU/PSU_2016_my_printf
** 
** Made by Cédric Thomas
** Login   <cedric@epitech.net>
** 
** Started on  Thu Nov 17 17:27:51 2016 Cédric Thomas
** Last update Mon Nov 28 21:38:09 2016 Cédric Thomas
*/
#include <stdlib.h>
#include <stdarg.h>
#include "my_printf.h"
#include "my.h"

int	print_flag(int *i, const char *format, t_flag *flag)
{
  int	size;

  size = 0;
  if (flag->form != 0)
    {
      size += putchar_i(flag->form);
    }
  if (flag->sign != 0)
    {
      size += putchar_i(flag->sign);
    }
  if (flag->padd != 0)
    {
      size += putchar_i(flag->padd);
    }
  while (is_in(format[*i], "#0- +"))
    *i += 1;
  return (size);
}

int	print_width(int *i, const char *format, t_flag *flag, char *w)
{
  int	size;

  size = 0;
  if (is_in(format[*i], "0123456789"))
    {
      while (is_in(format[*i], "0123456789"))
	{
	  size += putchar_i(format[*i]);
	  *i += 1;
	}
    }
  else if (format[*i] == '*')
    {
      size += putstr_i(w);
      *i += 1;
    }
  return (size);
}

int	print_precision(int *i, const char *format, t_flag *flag, char *p)
{
  int	size;

  size = 0;
  if (format[*i] == '.')
    {
      size += putchar_i(format[*i]);
      *i += 1;
    }
  else
    return (0);
  if (is_in(format[*i], "0123456789"))
    {
      while (is_in(format[*i], "0123456789"))
	{
	  size += putchar_i(format[*i]);
	  *i += 1;
	}
    }
  else if (format[*i] == '*')
    {
      size += putstr_i(p);
      *i += 1;
    }
  return (size);
}

int	print_len(int *i, const char *format, t_flag *flag)
{
  int	o;

  o = 0;
  while (flag->len[o])
    {
      o += 1;
      *i += 1;
    }
  return (0);
}
