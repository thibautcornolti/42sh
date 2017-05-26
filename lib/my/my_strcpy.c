/*
** my_strcpy.c for my_strcpy.c in /home/cedric/delivery/CPool_Day06
** 
** Made by Cédric Thomas
** Login   <cedric@epitech.net>
** 
** Started on  Mon Oct 10 09:36:13 2016 Cédric Thomas
** Last update Mon Oct 10 10:33:45 2016 Cédric Thomas
*/

char	*my_strcpy(char *dest, char *src)
{
  int	i;

  i = 0;
  while (src[i] != '\0')
    {
      dest[i] = src[i];
      i += 1;
    }
  dest[i] = src[i];
  return (dest);
}
