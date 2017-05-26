/*
** star.c for match in /home/cedric/delivery/extract_match
** 
** Made by 
** Login   <cedric.thomas@epitech.eu>
** 
** Started on  Mon Apr 24 09:50:10 2017 
** Last update Tue May  2 11:07:32 2017 
*/
#include "match.h"

int	inter(char **s1, char **s2)
{
  if ((**s1) != '\0')
    (*s1) += 1;
  (*s2) += 1;
  return (advanced_match(*s1, *s2));
}
