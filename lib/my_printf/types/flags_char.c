/*
** flags_char.c for flags_char.c in /home/cedric/delivery/my_printf/flags
** 
** Made by Cédric Thomas
** Login   <cedric@epitech.net>
** 
** Started on  Wed Nov  9 10:13:51 2016 Cédric Thomas
** Last update Mon Nov 28 21:29:39 2016 Cédric Thomas
*/
#include <stdarg.h>
#include <stdlib.h>
#include "my.h"
#include "my_printf.h"

static int	print_that(t_flag *flag, char *str)
{
  int	i;
  int	len;
  int	size;
  char	*converted;

  i = -1;
  len = 0;
  if (flag->precision == -1)
    size = my_strlen(str);
  else
    size = flag->precision;
  while (i++ < size - 1)
    {
      if (str[i] >= '!' && str[i] <= '~' || str[i] < 0 || str[i] > 127)
	len += putchar_i(str[i]);
      else
	{
	  converted = convertbase(str[i], "01234567");
	  len += putchar_i('\\');
	  len += putnchar_i('0', 3 - my_strlen(converted));
	  len += putstr_i(converted);
	  free(converted);
	}
    }
  return (len);
}

int	flag_s(va_list *arg, t_flag *flag)
{
  char	*str;
  int	size;
  int	null;

  size = 0;
  null = 0;
  if (flag->len[0] == 'l')
    return (0);
  str = va_arg(*arg, char *);
  if (str == NULL)
    {
      str = my_strdup("(null)");
      null = 1;
    }
  if (flag->padd != '-')
    size += paddchar(' ', flag, my_strlen(str));
  if (flag->precision == -1)
    size += putstr_i(str);
  else
    size += putnstr_i(str, flag->precision);
  if (flag->padd == '-')
    size += paddchar(' ', flag, my_strlen(str));
  if (null)
    free(str);
  return (size);
}

int	flag_c(va_list *arg, t_flag *flag)
{
  char	c;
  int	size;

  size = 0;
  c = (char)va_arg(*arg, int);
  if (flag->padd != '-')
    size += putnchar_i(' ', flag->paddlen - 1);
  size += putchar_i(c);
  if (flag->padd == '-')
    size += putnchar_i(' ', flag->paddlen - 1);
  return (size);
}

int	flag_percent(va_list *arg, t_flag *flag)
{
  return (putchar_i('%'));
}

int	flag_smaj(va_list *arg, t_flag *flag)
{
  char	*str;
  int	null;
  int	size;

  size = 0;
  null = 0;
  if (flag->len[0] == 'l')
    return (0);
  str = va_arg(*arg, char *);
  if (str == NULL)
    {
      str = my_strdup("(null)");
      null = 1;
    }
  if (flag->padd != '-')
    size += paddchar(' ', flag, my_strlen(str));
  size += print_that(flag, str);
  if (flag->padd == '-')
    size += paddchar(' ', flag, my_strlen(str));
  if (null)
    free(str);
  return (size);
}
