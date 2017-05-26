/*
** match.h for match in /home/cedric/delivery/extract_match
**
** Made by
** Login   <cedric.thomas@epitech.eu>
**
** Started on  Mon Apr 24 09:28:55 2017
** Last update Sun May 21 18:02:58 2017 Thibaut Cornolti
*/
#ifndef MATCH_H_
# define MATCH_H_

# define NB_PATTERN	8

typedef struct		s_pattern
{
  char			pattern;
  int			(*fct)(char **s1, char **s2);
}			t_pattern;

/*
**match.c
*/
int	advanced_match(char *str, char *pattern);

/*
**fct
*/
int	braquet(char **s1, char **s2);
int	escape(char **s1, char **s2);
int	inter(char **s1, char **s2);
int	parent(char **s1, char **s2);
int	hook(char **s1, char **s2);
int	star(char **s1, char **s2);
int	amp(char **s1, char **s2);
int	inib(char **s1, char **s2);
void	change_star_delim(char *str);
int	match_parent(char *s1, char **values, char *already);

#endif /* !MATCH_H_ */
