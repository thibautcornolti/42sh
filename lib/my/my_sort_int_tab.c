/*
** my_sort_int_tab.c for my_sort_int_tab.c in /home/cedric/delivery/CPool_Day07
** 
** Made by Cédric Thomas
** Login   <cedric@epitech.net>
** 
** Started on  Tue Oct 11 15:19:46 2016 Cédric Thomas
** Last update Tue Oct 18 08:56:43 2016 Cédric Thomas
*/

void	my_sort_int_tab(int *tab, int size)
{
  int	i;
  int	bool;
  int	buffer;

  bool = 1;
  buffer = 0;
  while (bool == 1)
    {
      i = 0;
      bool = 0;
      while (i < size)
	{
	  if (tab[i] > tab[i + 1])
	    {
	      buffer = tab[i];
	      tab[i] = tab[i + 1];
	      tab[i + 1] = buffer;
	      bool = 1;
	    }
	  i += 1;
	}
    }
}
