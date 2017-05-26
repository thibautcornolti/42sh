/*
** complte_line.c for complete in /home/cedric/delivery/PSU/PSU_2016_42sh/binds/complete
**
** Made by Cédric THOMAS
** Login   <cedric.thomas@epitech.eu>
**
** Started on  Thu May 18 12:58:11 2017 Cédric THOMAS
** Last update Sun May 21 23:13:41 2017 Cédric THOMAS
*/
#include <unistd.h>
#include <stdlib.h>
#include <termio.h>
#include "syntax.h"
#include "exec.h"
#include "my_printf.h"
#include "get_next_command.h"
#include "my.h"
#include "match.h"

static char	*get_value_com(char **files)
{
  int		current;
  int		i;
  int		len;

  i = -1;
  len = my_strlen(files[0]);
  while (files[++i] && len)
    {
      current = 0;
      while (current < len && !my_strncmp(files[0], files[i], current + 1))
	current += 1;
      len = current;
    }
  if (len == 0)
    return (NULL);
  return (my_strndup(files[0], len));
}

static int	detect_glob(t_keypad *key)
{
  int		i;

  i = -1;
  while (key->line[++i])
    {
      if (is_in(key->line[i], "#*[]-{}\\\"'`"))
	return (1);
    }
  return (0);
}

int		one_find(t_keypad *key, char **files, int size)
{
  char		*value;
  int		i;

  if (detect_glob(key))
    return (-1);
  if (!files || (value = get_value_com(files)) == NULL)
    return (1);
  i = key->index;
  while (i > 0 && !is_in(key->line[i], SKIP) &&
	 key->line[i] != '/')
    i -= 1;
  if (i != 0 || (i == 0 && key->line[i] == '/'))
    i += 1;
  if ((i = key->index - i) > my_strlen(value))
    return (0);
  if ((key->line = insert_str(key->line, value + i, key->index, 0)) == NULL)
    exit(84);
  key->index += my_strlen(value + i);
  if (key->line[key->index - 1] != '/' && size == 1)
    {
      key->line = my_strcatdup(key->line, " ", 1);
      key->index += 1;
    }
  free(value);
  return (size - 1);
}
