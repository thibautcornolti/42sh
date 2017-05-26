/*
** get_next_line.c for GNL in /home/cedric/delivery/CPE/CPE_2016_getnextline
** 
** Made by Cédric Thomas
** Login   <cedric@epitech.net>
** 
** Started on  Tue Jan  3 08:53:51 2017 Cédric Thomas
** Last update Mon Jan  9 09:40:32 2017 
*/
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "get_next_line.h"

static int	my_strlen(char *str, char c)
{
  int		i;

  i = -1;
  if (str == NULL)
    return (0);
  while (str[++i] && str[i] != c);
  return (i);
}

static int	my_read(const int fd, char *str)
{
  int		len;
  int		i;

  len = read(fd, str, READ_SIZE);
  if (len == -1)
    return (84);
  str[len] = 0;
  if (len == 0 && READ_SIZE - len > 0)
    return (0);
  return (1);
}

static int	my_strdec(char *str, char *line, char **adress)
{
  int		i;
  int		len;
  int		bool;

  i = -1;
  len = -1;
  bool = 0;
  while (str[++i])
    if (str[i] == '\n' && len == -1)
      {
	len = i + 1;
	bool = 1;
      }
  if (str[i] == 0 && len == -1)
    len = i;
  i = -1;
  while (str[++i + len])
    str[i] = str[i + len];
  str[i] = 0;
  if (line == NULL)
    {
      free(str);
      *adress = NULL;
    }
  return (i == 0 && !bool && str ? 1 : 0);
}

static char	*my_strcat(char *s1, char *s2)
{
  int		len;
  char		*new;
  int		i;

  len = my_strlen(s1, '\0') + my_strlen(s2, '\n');
  i = 0;
  if ((new = malloc(sizeof(char) * (len + 1))) == NULL)
      return (NULL);
  new[len] = 0;
  while (i < len)
    {
      if (i < my_strlen(s1, '\n'))
	new[i] = s1[i];
      else
	new[i] = s2[i - my_strlen(s1, '\n')];
      i += 1;
    }
  free(s1);
  return (new);
}

char		*get_next_line(const int fd)
{
  static char	*buffer = NULL;
  char		*line;
  int		stop;

  stop = 1;
  line = NULL;
  if (READ_SIZE <= 0)
    return (NULL);
  if (buffer == NULL)
    {
      if ((buffer = malloc(sizeof(char) * (READ_SIZE + 1))) == NULL)
	return (NULL);
      buffer[0] = 0;
    }
  while (stop == 1 && buffer)
    {
      if (!my_strlen(buffer, 0))
	if ((stop *= my_read(fd, buffer)) == 84)
	  return (NULL);
      if (buffer[0])
	line = my_strcat(line, buffer);
      stop *= my_strdec(buffer, line, &buffer);
    }
  return (line);
}
