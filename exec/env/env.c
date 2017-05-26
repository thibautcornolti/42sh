/*
** env.c for env.c in /home/cedric/delivery/PSU/PSU_2016_minishell1
** 
** Made by Cédric Thomas
** Login   <cedric@epitech.net>
** 
** Started on  Wed Jan  4 16:06:24 2017 Cédric Thomas
** Last update Thu May 11 18:04:03 2017 Thibaut Cornolti
*/
#include <unistd.h>
#include <stdlib.h>
#include "my.h"
#include "syntax.h"
#include "exec.h"

static int	getkeyindex(char **ae, char *key)
{
  int		i;
  int		len;

  i = 0;
  if (!ae || !key)
    return (-1);
  len = my_strlen(key);
  while (ae[i] && (my_strncmp(key, ae[i], len) || ae[i][len] != '='))
    i += 1;
  if (!ae[i])
    return (-1);
  return (i);
}

char	*getkey(char **ae, char *key, int dup)
{
  int	index;
  int	len;
  char	*keyvalue;

  if ((index = getkeyindex(ae, key)) < 0)
    return (NULL);
  len = my_strlen(key);
  if (dup)
    {
      if ((keyvalue = my_strdup(ae[index] + len + 1)) == NULL)
	exit(84);
      else
	return (keyvalue);
    }
  return (ae[index] + len + 1);
}

int	changekey(char **ae, char *key, char *value, int freeit)
{
  int	i;
  int	lenkey;
  char	*newkey;

  i = -1;
  if (!ae || !key || !value)
    return (1);
  lenkey = my_strlen(key);
  while (ae[++i] && (my_strncmp(key, ae[i], lenkey) || ae[i][lenkey] != '='));
  if (!ae[i])
    return (1);
  newkey = my_strcatdup(key, "=", freeit);
  newkey = my_strcatdup(newkey, value, 1 + freeit * 2);
  free(ae[i]);
  ae[i] = newkey;
  if (freeit)
    {
      free(value);
      free(key);
    }
  return (0);
}

char	**deletekey(char **ae, char *key, int freeit)
{
  int	i;
  int	index;
  char	**dup;

  i = -1;
  if ((index = getkeyindex(ae, key)) < 0)
    return (ae);
  while (ae[++i]);
  if ((dup = malloc(sizeof(char *) * i)) == NULL)
    exit(84);
  i = -1;
  while (ae[++i])
    {
      if (i < index)
	dup[i] = ae[i];
      else if (i > index)
	dup[i - 1] = ae[i];
      else
	free(ae[i]);
    }
  dup[i - 1] = 0;
  free(ae);
  if (freeit)
    free(key);
  return (dup);
}

char	**addkey(char **ae, char *key, char *value, int freeit)
{
  int	i;
  char	**dup;

  i = 0;
  while (ae[i])
    i += 1;
  if ((dup = malloc(sizeof(char *) * (i + 2))) == NULL)
    exit(84);
  i = -1;
  while (ae[++i])
    dup[i] = ae[i];
  free(ae);
  dup[i] = my_strcatdup(key, "=", freeit);
  dup[i] = my_strcatdup(dup[i], value, 1 + freeit * 2);
  dup[i + 1] = 0;
  return (dup);
}
