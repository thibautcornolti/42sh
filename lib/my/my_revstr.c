/*
** my_revstr.c for my_revstr.c in /home/cedric/delivery/CPool_Day06
** 
** Made by Cédric Thomas
** Login   <cedric@epitech.net>
** 
** Started on  Mon Oct 10 11:04:33 2016 Cédric Thomas
** Last update Thu Oct 13 22:00:06 2016 Cédric Thomas
*/

static int	my_len(char *str)
{
  int		i;

  i = 0;
  while (str[i] != '\0')
    {
      i += 1;
    }
  return (i);
}

char	*my_revstr(char *str)
{
  char	c;
  int	i;
  int	j;

  i = 0;
  j = my_len(str) - 1;
  c = 0;
  while (j > i && j > 0)
    {
      c = str[i];
      str[i] = str[j];
      str[j] = c;
      i++;
      j--;
    }
  return (str);
}
