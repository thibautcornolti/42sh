/*
** GNC.h for GNC in /home/cedric/Desktop/get_next_cmd
**
** Made by
** Login   <cedric.thomas@epitech.eu>
**
** Started on  Fri Apr 21 17:37:03 2017
** Last update Sun May 21 18:02:04 2017 Thibaut Cornolti
*/
#ifndef GNC_H_
# define GNC_H_

# define READ_SIZE	20
# define KEY_LINKED	18

typedef struct s_keypad	t_keypad;

typedef struct		s_keypad_fct
{
  int			(*fct)(t_keypad *keypad);
  char			*sequence;
}			t_keypad_fct;

typedef struct		s_keypad
{
  int			mod;
  char			*matched;
  int			valid;
  int			end;
  int			index;
  char			*line;
  char			*copy;
  struct s_keypad_fct	keys[KEY_LINKED];
  struct termio		term;
  struct s_system	*sys;
}			t_keypad;

/*
**str.c
*/
char		*insert_str(char *s1, char *s2, int pos, int mod);
char		*delete_a_char(char *str, int index);
void		print_line(t_keypad *keypad);
void		print_raw_line(t_keypad *keypad);
void		del_raw_line(t_keypad *keypad);

/*
**binds
*/
int		enter(t_keypad *keypad);
int		end_of_file(t_keypad *keypad);
int		left_arrow(t_keypad *keypad);
int		right_arrow(t_keypad *keypad);
int		ctrl_left_arrow(t_keypad *keypad);
int		ctrl_right_arrow(t_keypad *keypad);
int		delete_char(t_keypad *keypad);
int		suppr_char(t_keypad *keypad);
int		go_end(t_keypad *keypad);
int		go_start(t_keypad *keypad);
int		bind_clear(t_keypad *keypad);
int		bind_copy(t_keypad *keypad);
int		bind_paste(t_keypad *keypad);
int		bind_copy_all(t_keypad *keypad);
int		auto_complete(t_keypad *keypad);
void		search_all(t_keypad *key, char ***files, int *size);
int		add_matched(char ***, char *str, char *pattern, int *size);
int		add_matching_files(char *folder, char *pattern,
				   int *size, char ***);
void		get_folder_and_path(char *full_path, char **path, char **file);
int		one_find(t_keypad *key, char **files, int size);
void		default_append(char *buff, t_keypad *keypad, int size_buff);
int		down_arrow(t_keypad *keypad);
int		up_arrow(t_keypad *keypad);
int		switch_mod(t_keypad *keypad);
int		complete_history(t_keypad *key);
void		search_matched(t_keypad *key);

/*
**setup.c
*/
t_keypad	*init_keypad();
void		sequencer(t_keypad_fct *keys);
void		*end_keypad(t_keypad *keypad);

/*
**get_next_cmd.c
*/
char		*get_next_cmd(t_keypad *keypad);

/*
**term set
*/
int	my_set_term(t_keypad *keypad);
int	my_reset_term(t_keypad *keypad);

#endif /* !GNC_H_ */
