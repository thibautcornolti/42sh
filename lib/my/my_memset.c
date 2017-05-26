/*
** my_memset.c for memset in /home/cedric
** 
** Made by Cédric Thomas
** Login   <cedric@epitech.net>
** 
** Started on  Mon Oct 31 16:15:04 2016 Cédric Thomas
** Last update Fri May 12 16:53:33 2017 Thibaut Cornolti
*/

void	my_memset(char *data, int c, int size)
{
  char	*str;
  int	i;

  str = (char *)data;
  i = 0;
  while (i < size)
    {
      str[i] = c;
      i += 1;
    }
}
