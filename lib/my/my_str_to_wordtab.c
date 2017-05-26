/*
** my_str_to_wordtab.c for CPool_Day08.c in /home/cedric/delivery/CPool_Day08/task04
** 
** Made by Cédric Thomas
** Login   <cedric@epitech.net>
** 
** Started on  Wed Oct 12 12:19:23 2016 Cédric Thomas
** Last update Fri Mar 17 10:20:51 2017 
*/
#include <stdlib.h>
#include "my.h"

static void	init_tab(int *alpha, int size, char *str)
{
  int		i;

  if (alpha == NULL)
    return ;
  i = 0;
  while (i < size)
    {
      alpha[i] = 0;
      i += 1;
    }
}

static int	*wordscounter(char *str, int *words)
{
  int		i;
  int		j;
  int		*alpha;

  i = 0;
  j = 0;
  while (str[i] != '\0')
    {
      if (i == 0 && str[i] != 32 || i > 0 && str[i] != 32 && str[i - 1] == 32)
	*words += 1;
      i += 1;
    }
  i = 0;
  if ((alpha = malloc(sizeof(int) * (*words + 1))) == NULL)
    return (NULL);
  init_tab(alpha, *words, str);
  while (str[i] != '\0')
    {
      if (str[i] != ' ')
	alpha[j] += 1;
      else if (i > 0 && str[i - 1] != ' ' && str[i] == ' ')
	j += 1;
      i += 1;
    }
  return (alpha);
}

static char	*replace_no_an(char *str)
{
  int		i;
  char		c;
  int		last;
  char		*getmalloc;

  i = 0;
  getmalloc = malloc(sizeof(char) * (my_strlen(str) + 1));
  if (getmalloc == NULL)
    return (NULL);
  my_strcpy(getmalloc, str);
  while (str[i] != '\0')
    {
      c = getmalloc[i];
      if (c < '0' || c > '9')
	if (c < 'a' || c > 'z')
	  if (c < 'A' || c > 'Z')
	    {
	      getmalloc[i] = ' ';
	    }
      i += 1;
    }
  return (getmalloc);
}

static char	**split(char *str, int *alpha, int size)
{
  int		i;
  int		j;
  int		k;
  char		**wordtab;

  i = -1;
  k = 0;
  if ((wordtab = malloc(sizeof(char *) * (size + 1))) == NULL)
    return (NULL);
  while (++i < size)
    {
      j = 0;
      if ((wordtab[i] = malloc(sizeof(char) * (alpha[i] + 1))) == NULL)
	return (NULL);
      while (j + k < my_strlen(str) - 1 && str[j + k] == ' ')
	k += 1;
      j -= 1;
      while (++j < alpha[i])
	wordtab[i][j] = str[k + j];
      k += j;
      wordtab[i][j] = '\0';
    }
  wordtab[i] = NULL;
  return (wordtab);
}

char	**my_str_to_wordtab(char *str)
{
  char	*s1;
  int	words;
  int	*alpha;
  int	i;
  char	**wordtab;

  if (str == NULL)
    return (NULL);
  i = 0;
  words = 0;
  if ((s1 = replace_no_an(str)) == NULL)
    return (NULL);
  if ((alpha = wordscounter(s1, &words)) == NULL)
    return (NULL);
  if ((wordtab = split(s1, alpha, words)) == NULL)
    return (NULL);
  free(alpha);
  return (wordtab);
}
