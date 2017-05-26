/*
** star.c for match in /home/cedric/delivery/extract_match
** 
** Made by 
** Login   <cedric.thomas@epitech.eu>
** 
** Started on  Mon Apr 24 09:50:10 2017 
** Last update Mon Apr 24 10:13:27 2017 
*/
#include "match.h"

int	escape(char **s1, char **s2)
{
  (void)(s1);
  (*s2) += 1;
  return (0);
}
