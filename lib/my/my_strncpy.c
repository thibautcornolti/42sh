/*
** my_strncpy.c for my_strncpy.c in /home/cedric/delivery/CPool_Day06
** 
** Made by Cédric Thomas
** Login   <cedric@epitech.net>
** 
** Started on  Mon Oct 10 09:52:35 2016 Cédric Thomas
** Last update Mon Oct 10 11:27:11 2016 Cédric Thomas
*/

char	*my_strncpy(char *dest, char *src, int n)
{
  int	i;

  i = 0;
  while (i < n && src[i] != '\0')
    {
      dest[i] = src[i];
      i += 1;
    }
  while (i < n)
    {
      dest[i] = '\0';
      i += 1;
    }
  return (dest);
}
