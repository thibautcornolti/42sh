/*
** my.h for CPool_Day09 in /home/cedric/delivery/CPool_Day09
** 
** Made by Cédric Thomas
** Login   <cedric@epitech.net>
** 
** Started on  Thu Oct 13 11:14:10 2016 Cédric Thomas
** Last update Sun Dec 18 14:26:02 2016 Cédric Thomas
*/

#ifndef MY_H_
# define MY_H_

void		my_putchar(char c);
int		my_isneg(int nb);
int		my_put_nbr(int nb);
int		my_swap(int *a, int *b);
int		my_putstr(char *str);
int		my_strlen(char *str);
int		my_getnbr(char *str);
void		my_sort_int_tab(int *tab, int size);
int		my_power_rec(int nb, int power);
int		my_square_root(int nb);
int		my_is_prime(int nombre);
int		my_find_prime_sup(int nb);
char		*my_strcpy(char *dest, char *src);
char		*my_strncpy(char *dest, char *src, int n);
char		*my_revstr(char *str);
char		*my_strstr(char *str, char *to_find);
int		my_strcmp(char *s1, char *s2);
int		my_strncmp(char *s1, char *s2, int n);
char		*my_strupcase(char *str);
char		*my_strlowcase(char *str);
char		*my_strcapitalize(char *str);
int		my_str_isalpha(char *str);
int		my_str_isnum(char *str);
int		my_str_islower(char *str);
int		my_str_isupper(char *str);
int		my_str_isprintable(char *str);
int		my_showstr(char *str);
int		my_showmem(char *str, int size);
char		*my_strcat(char *dest, char *src);
char		*my_strncat(char *dest, char *src, int nb);
int		my_show_wordtab(char **tab);
char		**my_str_to_wordtab(char *str);
char		**my_split(char *str, char sep);
char		*my_strdup(char *src);
char		*my_strcatdup(char *s1, char *s2);
char		*convert_base(char *nbr, char *base_from, char *base_to);
void		my_memset(char *, int, int);
int		is_in(char c, char *str);
int		is_nb(char c);
void		free_tab(char **tab);
void		my_puterror(char *str);
int		is_betwr(int a, int nb, int b);
int		is_betw(int a, int nb, int b);

#endif /* !MY_H_ */
