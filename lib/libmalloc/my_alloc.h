/*
** my_alloc.h for my_alloc in /home/cedric/delivery/libmalloc
** 
** Made by 
** Login   <cedric.thomas@epitech.eu>
** 
** Started on  Mon Mar  6 18:13:51 2017 
** Last update Thu Mar 16 20:22:11 2017 
*/

#ifndef MY_ALLOC_H_
# define MY_ALLOC_H_

typedef union		u_point
{
  int			addr;
  void			*point;
}			t_point;

typedef struct		s_alloc
{
  void			*addr;
  size_t		size;
  char			*tag;
  char			type;
  struct s_alloc	*prev;
  struct s_alloc	*next;
}			t_alloc;

/*
**print
*/
void	aputnbr(int nb);
void	aputstr(char *str);
void	putalloc(t_alloc *tp);

/*
**misc
*/
char	*my_astrdup(char *src);
int	my_astrcmp(char *s1, char *s2);
int	my_put_apointer(void *addr, char *base);
void	aputchar(char c);

/*
**alloc_misc.c
*/
t_alloc	*init_alloc(t_alloc *tp, char type, char *tag);

/*
**list
*/
int	my_tag_alloc(void *addr, char *tag, char type);
int	my_put_alloc(void *addr, size_t size);
int	my_del_alloc(t_alloc *elem);
void	my_show_alloc(void *addr, char *tag, char type);
void	my_free_tag(char *tag, char type);

/*
**alloc
*/
size_t	my_alloc_size(void *alloc);
void	*my_realloc(void **alloc, size_t size_new);
void	*my_alloc(size_t size);
void	*my_vfree(void **to_free, void *to_ret);
int	my_ifree(void **to_free, int to_ret);

#endif /* !MY_ALLOC_H_ */
