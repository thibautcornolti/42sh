/*
** parent.c for match in /home/cedric/delivery/extract_match
** 
** Made by Cédric THOMAS
** Login   <cedric.thomas@epitech.eu>
** 
** Started on  Tue May  2 10:08:07 2017 
** Last update Fri May 12 16:10:14 2017 Thibaut Cornolti
*/
#include <stdlib.h>
#include "match.h"
#include "my.h"

static char	*get_already(char **values)
{
  char		*already;
  int		i;

  i = 0;
  while (values[i])
    i += 1;
  if ((already = malloc(i)) == NULL)
    return (NULL);
  my_memset((char *)already, 0, i);
  i = -1;
  while (already[++i])
    if (values[i][0] == '&')
      already[i] = -1;
  return (already);
}

static int	auto_match(char *s1, char **values, char *current, char *already)
{
  int		start;
  int		ret;
  int		idx;

  idx = -1;
  ret = 0;
  while (values[++idx])
    {
      start = 0;
      if (values[idx][0] == '&')
	start = 1;
      if (already[idx] <= 0 && advanced_match(current, values[idx] + start))
	{
	  if (already[idx] == 0)
	    already[idx] = 1;
	  ret += match_parent(s1, values, already);
	}
    }
  return (ret);
}

int		match_parent(char *s1, char **values, char *already)
{
  char		*current;
  int		i;
  int		ret;

  ret = 0;
  i = -1;
  if (*s1 == 0)
    return (1);
  while (s1[++i] && !ret)
    {
      if ((current = my_strndup(s1, i + 1)) == NULL)
	return (0);
      ret = auto_match(s1 + i + 1, values, current, already);
      free(current);
    }
  return (ret);
}

int		parent(char **s1, char **s2)
{
  int		ret;
  int		len;
  char		*already;
  char		*format;
  char		**values;

  len = my_cstrlen(*s2, ')');
  if ((format = my_strndup(*s2 + 1, len - 1)) == NULL)
    return (0);
  if ((values = my_split(format, ',')) == NULL)
    {
      free(format);
      return (0);
    }
  free(format);
  if ((already = get_already(values)) == NULL)
    return (0);
  ret = match_parent(*s1, values, already);
  free_tab(values);
  free(already);
  return (ret);
}

