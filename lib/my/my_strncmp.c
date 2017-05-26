/*
** my_strncmp.c for my_strncmp.c in /home/cedric/delivery/CPool_Day06
** 
** Made by Cédric Thomas
** Login   <cedric@epitech.net>
** 
** Started on  Mon Oct 10 14:57:15 2016 Cédric Thomas
** Last update Tue Oct 11 14:01:35 2016 Cédric Thomas
*/

int	my_strncmp(char *s1, char *s2, int n)
{
  int	i;

  i = 0;
  while ((s1[i] != '\0' || s2[i] != '\0') && i < n - 1)
    {
      if (s1[i] != s2[i])
	{
	  return (s1[i] - s2[i]);
	}
      i += 1;
    }
  return (s1[i] - s2[i]);
}
