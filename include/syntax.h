/*
** syntax.h for parseur in /home/cedric/delivery/parseur_ll
**
** Made by
** Login   <cedric.thomas@epitech.eu>
**
** Started on  Wed Mar 22 18:26:36 2017
** Last update Sun May 21 17:56:37 2017 Thibaut Cornolti
*/

#ifndef SYNTAX_H_
# define SYNTAX_H_

# define SKIP		" \t"
# define INIB_C		'\\'
# define INIB		"\"'"
# define BACKQUOTE	"`"

# define ULIMT_MATCH	-1
# define LIMT_MATCH	0

# define T_ARGS			(1 << 0)
# define T_FILE			(1 << 1)
# define T_COMMAND		(1 << 2)
# define T_JOB			(1 << 3)
# define T_FLUX_REDIR_OUT	(1 << 4)
# define T_FLUX_REDIR_IN	(1 << 5)
# define T_FLUX			(1 << 6)
# define T_LOGIC_AND		(1 << 7)
# define T_LOGIC_OR		(1 << 8)
# define T_SEPAR		(1 << 9)
# define T_BACKQUOTE		(1 << 10)

# define T_COMMON	(T_ARGS | T_COMMAND | T_FILE)

# define FULL_MAX_TYPES	11
# define MAX_TYPES	FULL_MAX_TYPES - 2
# define TREE_TYPES	MAX_TYPES - 2

# define DOUBLE		(1 << 0)
# define STDOUT		(1 << 1)
# define STDERROR	(1 << 2)
# define STDIN		(1 << 3)

typedef struct	s_info		t_info;
typedef struct	s_system	t_system;

typedef struct		s_redir
{
  char			*file;
  int			tag;
  struct s_redir	*next;
}			t_redir;

typedef struct		s_command
{
  char			*path;
  int			type;
  void			*root;
  void			*left;
  void			*right;
  int			fd[3];
  struct s_redir	*redir;
  char			**argv;
}			t_command;

typedef struct		s_pipe
{
  char			*data;
  int			type;
  void			*root;
  void			*left;
  void			*right;
  int			fd[3];
}			t_pipe;

typedef struct		s_node
{
  char			*data;
  int			type;
  void			*root;
  void			*left;
  void			*right;
}			t_node;

typedef struct		s_syntax
{
  int			*already;
  int			weight;
  char			**values;
}			t_syntax;

typedef struct		s_token
{
  int			type;
  char			*token;
  int			used;
  struct s_token	*prev;
  struct s_token	*next;
}			t_token;

typedef struct		s_field
{
  t_token		*root;
  t_token		*start;
  t_token		*end;
}			t_field;

/*
**MAIN
*/
t_node		*parse_cmd(t_syntax *my_syntax, char *str, t_system *sys);
void		free_syntax(t_syntax **my_syntax);
t_syntax	*get_syntax();

/*
**MISC
*/
char		**tab_create(int size, ...);
t_syntax	syntax_create(int weight, int size, ...);
void		*my_free_null(void *ptr);
int		my_putfd(int fd, char *str);
int		my_log2(int log);
char		*alloc_strdup(char *);
char		*shape_separator(char *str, char **sep_list);
char		*delete_nbchar(char *str, int nb, int index);
char		*add_substr(char *str, char *substr, int index);
char		*replace_unquoted_str(char *str, char *find,
				      char *replace, char *quote_list);
char		*replace_quoted_str(char *str, char *find,
			      char *replace, char *quote_list);
char		*dequotificator(char *str);

/*
**LEXER
*/
t_token		*get_token(char *str, t_syntax *my_syntax,
			   t_info *info, int shape);
int		my_put_list_token(t_token **ll, char *token, int type);
int		my_del_list_token(t_token **ll, t_token *elem);
void		swap_token(t_token *one, t_token *two);
int		my_free_token(t_token **ll);
int		my_show_token(t_token *ll);

/*
**TREE
*/
void		show_nodes(t_node *root, int depth, int side);
void		my_free_tree(void **root);
int		add_redir_list(t_redir **my_redir, char *file, char *type);
void		show_redir(t_redir *redir);
void		*create_tree(void *root,
			     t_token *start, t_token *end);

/*
**NODE
*/
void		*auto_create_node(void *root, t_token *start, t_token *end);
void		*create_standard_node(t_field *field, t_token *mid);
void		*create_command_node(t_field *field, t_token *mid);
void		*create_pipe_node(t_field *field, t_token *mid);

/*
**ERROR
*/
int		error_pipe_node(t_field *field, t_token *mid);
int		error_command_node(t_field *field, t_token *mid);
int		error_logic_node(t_field *field, t_token *mid);
int		error_redir_node(t_field *field, t_token *mid);
int		check_input_lexer(char *str);
int		check_tokens(t_token *token);

/*
**SHAPE
*/
char		*shape_str(char *str);
void		shape_token(t_token *token);
void		inib_token(t_token *token);

/*
**SYNTAX_CHECKER
*/
int		match_all(t_token *token, int type, int reset, int find);
int		match_prev(t_token *token, int type, int reset, int find);
int		match_next(t_token *token, int type, int reset, int find);

#endif /* !SYNTAX_H_ */
