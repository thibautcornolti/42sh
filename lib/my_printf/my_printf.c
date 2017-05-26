/*
** my_printf.c for my_printf in /home/cedric/delivery/PSU/PSU_2016_my_printf
** 
** Made by Cédric Thomas
** Login   <cedric@epitech.net>
** 
** Started on  Thu Nov 17 18:47:15 2016 Cédric Thomas
** Last update Mon Nov 28 21:17:52 2016 Cédric Thomas
*/
#include <stdlib.h>
#include <stdarg.h>
#include "my_printf.h"
#include "my.h"

static int	get_fct(int (*fct[12])(va_list *, t_flag *), char **flags)
{
  if ((*flags = my_strdup("sc%SpdiuoxXb")) == NULL)
    return (1);
  fct[0] = &flag_s;
  fct[1] = &flag_c;
  fct[2] = &flag_percent;
  fct[3] = &flag_smaj;
  fct[4] = &flag_p;
  fct[5] = &flag_d;
  fct[6] = &flag_d;
  fct[7] = &flag_u;
  fct[8] = &flag_o;
  fct[9] = &flag_x;
  fct[10] = &flag_xmaj;
  fct[11] = &flag_b;
  return (0);
}

static void	flag_n(va_list *arg, int written)
{
  int		*point;

  point = va_arg(*arg, void *);
  *point = written;
}

static int	puterror(int save, int *i, const char *format, t_flag *flag)
{
  int	size;
  char	*preci;
  char	*width;

  size = 0;
  preci = convertbase(flag->precision, "0123456789");
  width = convertbase(flag->paddlen, "0123456789");
  size += putchar_i('%');
  size += print_flag(&save, format, flag);
  size += print_width(&save, format, flag, width);
  size += print_precision(&save, format, flag, preci);
  size += print_len(&save, format, flag);
  while (save <= *i && format[save])
    {
      size += putchar_i(format[save]);
      save += 1;
    }
  free(width);
  free(preci);
  return (size);
}

static int	parse(va_list *arg, int *i, const char *format, int writted)
{
  t_flag	flag;
  int		(*fct[12])(va_list *, t_flag *);
  char		*flags;
  int		size;
  int		save;

  size = 0;
  save = *i;
  fill_flag(i, format, &flag);
  fill_width(i, format, &flag, arg);
  fill_precision(i, format, &flag, arg);
  if (fill_len(i, format, &flag))
    return (0);
  if (get_fct(fct, &flags))
    return (0);
  if (format[*i] == 'n')
    flag_n(arg, writted);
  else if (is_in(format[*i], flags))
    size += fct[getindex(format[*i], flags)](arg, &flag);
  else
    size += puterror(save, i, format, &flag);
  free(flags);
  free(flag.len);
  return (size);
}

int		my_printf(const char *format, ...)
{
  int		i;
  int		sum;
  int		temp;
  va_list	args;
  int		error;

  i = -1;
  error = 0;
  sum = 0;
  temp = 1;
  va_start(args, format);
  while (format[++i])
    {
      if (format[i] == '%' && ++i)
  	{
	  if ((temp = parse(&args, &i, format, sum)) != 0)
	    sum += temp;
	  else
	    error = 1;
  	}
      else
	sum += putchar_i(format[i]);
    }
  va_end(args);
  return (sum);
}
