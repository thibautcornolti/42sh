/*
** my_strlen.c for my_strlen.c in /home/cedric/delivery/CPool_Day04
** 
** Made by Cédric Thomas
** Login   <cedric@epitech.net>
** 
** Started on  Thu Oct  6 16:13:19 2016 Cédric Thomas
** Last update Thu Oct  6 17:03:08 2016 Cédric Thomas
*/

int	my_strlen(char *str)
{
  int	i;

  i = 0;
  while (str[i] != '\0')
    {
      i += 1;
    }
  return (i);
}
