/*
** my_printf.h for my_printf in /home/cedric/delivery/my_printf
** 
** Made by Cédric Thomas
** Login   <cedric@epitech.net>
** 
** Started on  Wed Nov  9 10:12:10 2016 Cédric Thomas
** Last update Sun May 21 18:05:01 2017 Thibaut Cornolti
*/
#ifndef MY_PRINTF_H_
# define MY_PRINTF_H_

# include <stdarg.h>

typedef struct	s_flag
{
  char		form;
  char		padd;
  int		paddlen;
  char		sign;
  int		precision;
  char		*len;
}		t_flag;

/*
**my_printf.c
*/
int	my_printf(const char *format, ...);

/*
**flag_char.c
*/
int	flag_s(va_list *, t_flag *);
int	flag_c(va_list *, t_flag *);
int     flag_percent(va_list *, t_flag *);
int	flag_smaj(va_list *, t_flag *);

/*
**flag_pointer.c
*/
int	flag_p(va_list *, t_flag *);

/*
**flag_int.c
*/
int	flag_d(va_list *, t_flag *);
int	flag_u(va_list *, t_flag *);

/*
**flag_base.c
*/
int	flag_o(va_list *, t_flag *);
int	flag_x(va_list *, t_flag *);
int	flag_xmaj(va_list *, t_flag *);
int	flag_b(va_list *, t_flag *);

/*
**print.c
*/
int	putnchar_i(char, int);
int     putnstr_i(char *, int);
int	putchar_i(char);
int	putstr_i(char *);

/*
**str.c
*/
int	strcmp_i(char *, char *);
int	getindex(char, char *);

/*
**convert.c
*/
char	*convertbase(long long int, char *);
char	*u_convertbase(unsigned long long int, char *);

/*
**format.c
*/
void	fill_flag(int *, const char *, t_flag *);
void	fill_width(int *, const char *, t_flag *, va_list *);
void	fill_precision(int *, const char *, t_flag *, va_list *);
int	fill_len(int *, const char *, t_flag *);

/*
**printformat.c
*/
int	print_flag(int *, const char *, t_flag *);
int	print_width(int *, const char *, t_flag *, char *);
int	print_precision(int *, const char *, t_flag *, char *);
int	print_len(int *, const char *, t_flag *);

/*
**stru_fct.c
*/
int		paddchar(char, t_flag *, int);
int		getlenprecision(t_flag *, char *, int, long long int *);
int		paddit(t_flag *, int, char, char *);
int		precision(t_flag *, char *, int, long long int *);
long long int	cast(t_flag *, va_list *, char);

#endif /* !MY_PRINTF_H_ */
