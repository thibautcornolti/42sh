/*
** my_str_to_wordtab.c for CPool_Day08.c in /home/cedric/delivery/CPool_Day08/task04
** 
** Made by Cédric Thomas
** Login   <cedric@epitech.net>
** 
** Started on  Wed Oct 12 12:19:23 2016 Cédric Thomas
** Last update Wed Mar  1 10:56:04 2017 
*/
#include <stdlib.h>
#include "my.h"

static void	sel_init_tab(int *alpha, int size, char *str)
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

static int	*sel_wordscounter(char *str, int *words, char c)
{
  int		i;
  int		j;
  int		*alpha;

  i = -1;
  j = 0;
  while (str[++i] != '\0')
    if (i == 0 && str[i] != c || i > 0 && str[i] != c && str[i - 1] == c)
      *words += 1;
  i = 0;
  if ((alpha = malloc(sizeof(int) * (*words + 1))) == NULL)
    return (NULL);
  sel_init_tab(alpha, *words, str);
  while (str[i] != '\0')
    {
      if (str[i] != c)
	alpha[j] += 1;
      else if (i > 0 && str[i - 1] != c && str[i] == c)
	j += 1;
      i += 1;
    }
  return (alpha);
}

static char	**sel_split(char *str, int *alpha, int size, char c)
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
      while (j + k < my_strlen(str) - 1 && str[j + k] == c)
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

char	**my_split(char *str, char sep)
{
  int	words;
  int	*alpha;
  int	i;
  char	**wordtab;

  if (str == NULL)
    return (NULL);
  i = 0;
  words = 0;
  if ((alpha = sel_wordscounter(str, &words, sep)) == NULL)
    return (NULL);
  if ((wordtab = sel_split(str, alpha, words, sep)) == NULL)
    return (NULL);
  free(alpha);
  return (wordtab);
}
