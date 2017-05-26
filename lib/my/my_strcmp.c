/*
** my_strcmp.c for my_strcmp.c in /home/cedric/delivery/CPool_Day06
** 
** Made by Cédric Thomas
** Login   <cedric@epitech.net>
** 
** Started on  Mon Oct 10 14:57:15 2016 Cédric Thomas
** Last update Mon Oct 10 15:46:25 2016 Cédric Thomas
*/

int	my_strcmp(char *s1, char *s2)
{
  int	i;

  i = 0;
  while (s1[i] != '\0' || s2[i] != '\0')
    {
      if (s1[i] != s2[i])
	{
	  return (s1[i] - s2[i] < 0 ? -1 : 1);
	}
      i += 1;
    }
  return (0);
}
