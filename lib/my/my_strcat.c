/*
** my_strncat.c for my_strncat.c in /home/cedric/delivery/CPool_Day07
** 
** Made by Cédric Thomas
** Login   <cedric@epitech.net>
** 
** Started on  Tue Oct 11 16:19:26 2016 Cédric Thomas
** Last update Tue Oct 11 16:35:11 2016 Cédric Thomas
*/

char	*my_strcat(char *dest, char *src)
{
  int	i;
  int	j;

  i = 0;
  j = 0;
  while (dest[i] != '\0')
    i += 1;
  while (src[j] != '\0')
    {
      dest[i + j] = src[j];
      j += 1;
    }
  dest[i + j] = '\0';
  return (dest);
}
