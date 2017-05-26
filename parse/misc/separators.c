/*
** epurstr.c for asm in /home/cedric/delivery/CPE/CPE_2016_corewar/asm
** 
** Made by 
** Login   <cedric.thomas@epitech.eu>
** 
** Started on  Wed Mar  1 15:08:23 2017 
** Last update Sun May 21 18:37:06 2017 Thibaut Cornolti
*/

#include <stdlib.h>
#include "my.h"
#include "syntax.h"

int	is_in_tab(char *str, char **tab, int *index)
{
  *index = 0;
  while (tab[*index])
    {
      if (!my_strncmp(tab[*index], str, my_strlen(tab[*index])))
	return (1);
      (*index) += 1;
    }
  *index = -1;
  return (0);
}

static int	my_epur_size(char *str, char **sep_list)
{
  int		tab_size;
  int		size;
  int		i;
  char		quote;

  i = -1;
  size = 0;
  quote = 0;
  while (str[++i])
    {
      if ((quote == 0 && is_in(str[i], INIB)) || str[i] == quote)
	quote = (!quote ? str[i] : 0);
      if (is_in_tab(str + i, sep_list, &tab_size) && !quote)
	size += my_strlen(sep_list[tab_size]) + 1;
      size += 1;
    }
  return (size);
}

static void	my_cpy(char *str, char *epured, char **sep_list)
{
  int		tab_size;
  int		i;
  char		quote;
  int		j;

  i = -1;
  j = 0;
  quote = 0;
  while (str[++i])
    {
      if ((quote == 0 && is_in(str[i], INIB)) || str[i] == quote)
	quote = (!quote ? str[i] : 0);
      if (is_in_tab(str + i, sep_list, &tab_size) && !quote)
	{
	  my_strncpy(epured + j + 1, sep_list[tab_size],
		     my_strlen(sep_list[tab_size]));
	  j += my_strlen(sep_list[tab_size]) + 1;
	  i += my_strlen(sep_list[tab_size]) - 1;
	}
      else
	epured[j] = str[i];
      j += 1;
    }
  epured[j] = 0;
}

char	*shape_separator(char *str, char **sep_list)
{
  char	*epured;
  int	size;

  if (str == NULL)
    return (NULL);
  size = my_epur_size(str, sep_list);
  if ((epured = malloc(sizeof(char) * (size + 1))) == NULL)
    return (NULL);
  my_memset(epured, ' ', size);
  my_cpy(str, epured, sep_list);
  free(str);
  return (epured);
}
