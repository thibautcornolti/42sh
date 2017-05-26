/*
** misc.c for gnc in /home/cedric/Desktop/get_next_cmd
**
** Made by
** Login   <cedric.thomas@epitech.eu>
** 
** Started on  Sat Apr 22 11:50:50 2017 
** Last update Sun May 21 23:02:18 2017 Cédric THOMAS
*/
#include <curses.h>
#include <unistd.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <termio.h>
#include "get_next_command.h"
#include "my.h"
#include "my_printf.h"
#include "syntax.h"
#include "exec.h"
#include "my_alloc.h"

char	*delete_a_char(char *str, int index)
{
  int	nb;
  char	*first;
  char	*second;
  char	*full;

  nb = 1;
  if (str == NULL)
    return (NULL);
  if ((first = my_strndup(str, index)) == NULL)
    return (NULL);
  if ((second = my_strdup(str + index + nb)) == NULL)
    return (NULL);
  if ((full = my_strcatdup(first, second, 3)) == NULL)
    return (NULL);
  free(str);
  return (full);
}

char	*insert_str(char *s1, char *s2, int pos, int mod)
{
  int		len2;
  char		*dest;
  int		len;

  len = 0;
  if (s1 != NULL)
    len = my_strlen(s1);
  if (s2 == NULL)
    return (my_strdup(s1));
  len2 = my_strlen(s2);
  if (mod)
    len2 = 1;
  if ((dest = malloc(sizeof(char) * (len + len2 + 1))) == NULL)
    return (NULL);
  dest[0] = 0;
  if (s1)
    my_strncpy(dest, s1, pos);
  my_strncpy(dest + pos, s2, len2);
  dest[pos + len2] = 0;
  if (s1)
    my_strcat(dest, s1 + pos);
  free(s1);
  return (dest);
}

void		del_raw_line(t_keypad *pad)
{
  int		i;
  int		len1;
  int		len2;
  char		*seq;

  len1 = 0;
  len2 = 0;
  if (pad->line)
    len1 = my_strlen(pad->line);
  if (pad->mod && pad->matched)
    len2 = my_strlen(pad->matched);
  if ((seq = tigetstr("cub1")) == (char *) -1)
    return ;
  i = -1;
  while (++i < pad->index)
    my_printf(seq);
  i = -1;
  while (++i < len1 + len2)
    my_printf(" ");
  i = -1;
  while (++i < len1 + len2)
    my_printf(seq);
}

void		print_raw_line(t_keypad *pad)
{
  int		i;
  int		len1;
  int		len2;
  char		*seq;

  len1 = 0;
  len2 = 0;
  if (pad->mod)
    search_matched(pad);
  if (pad->line)
    {
      my_printf("%s", pad->line);
      len1 = my_strlen(pad->line);
    }
  if (pad->mod && pad->matched)
    {
      my_printf("\033[31;01m%s\033[00m", pad->matched);
      len2 = my_strlen(pad->matched);
    }
  if ((seq = tigetstr("cub1")) == (char *) -1)
    return ;
  i = -1;
  while (++i < (len1 + len2 - pad->index))
    my_printf(seq);
}

void		print_line(t_keypad *pad)
{
  if (isatty(0))
    print_prompt(pad->sys->info);
  print_raw_line(pad);
}
