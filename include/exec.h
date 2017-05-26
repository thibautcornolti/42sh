/*
** exec.h for 42sh in /home/cedric/Desktop/parseur 42
**
** Made by Cédric THOMAS
** Login   <cedric.thomas@epitech.eu>
**
** Started on  Tue May  9 09:25:48 2017
** Last update Sun May 21 23:05:05 2017 Bastien
*/

#ifndef EXEC_H_
# define EXEC_H_

# define HIST_SIZE	100

# define PIPELINE	(1 << 0)
# define LEFT_PIPE	(1 << 1)
# define RIGHT_PIPE	(1 << 2)
# define FORK		(1 << 3)
# define JOB		(1 << 4)
# define JOBLINE	(1 << 5)

# define JOB_CREATPRINT	(1 << 0)
# define JOB_SUSPENDED	(1 << 1)
# define JOB_FOREGROUND	(1 << 2)
# define JOB_BACKGROUND	(1 << 3)
# define JOB_TERMPRINT	(1 << 4)
# define JOB_TERMINATED	(1 << 5)
# define INIB_BACK	(1 << 6)

# define BUILTINS_NB	16
# define REDIR_NB	4

# define FILE_RC	".42shrc"
# define FILE_HISTORY	".42sh_history"

typedef struct		s_alias
{
  char			*link;
  char			*value;
  int			loop;
}			t_alias;

typedef struct		s_var
{
  char			*name;
  char			*value;
}			t_var;

typedef struct		s_history
{
  int			status;
  int			index;
  char			*cmd;
  long			time;
  struct s_history	*prev;
  struct s_history	*next;
}			t_history;

typedef struct		s_history_info
{
  int			len;
  t_history		*start;
  t_history		*current;
  t_history		*end;
}			t_history_info;

typedef struct		s_info
{
  char			*builtins[BUILTINS_NB + 1];
  char			**env;
  t_history_info	*histo;
  unsigned int		exit_value;
  unsigned int		exit_arg;
  char			*old_pwd;
  char			*pwd;
  t_alias		*alias;
  t_var			*var;
}			t_info;

typedef struct		s_exit
{
  int			exit;
  int			pid;
  int			pgid;
  struct s_job		*job;
  struct s_exit		*next;
  struct s_exit		*prev;
}                       t_exit;

typedef struct		s_job
{
  int			pid;
  int			pgid;
  int			status;
  int			number;
}			t_job;

typedef struct		s_status
{
  int			exit;
  int			status;
  int			fd_to_close;
  struct s_exit		*exit_list;
  int			pgid;
  int			job_nbr;
}			t_status;

typedef struct		s_exec_fct
{
  int			type;
  int			(*fct)(t_node *root, t_status *status, t_info *info);
}			t_exec_fct;

typedef struct		s_system
{
  struct s_keypad	*keypad;
  t_syntax		*syntax;
  t_status		*status;
  t_info		*info;
}			t_system;

int		my_system(char *command, t_system *system);
t_system	*getter_system(t_system *setter);

/*
**PROMPT
*/
void		print_prompt(t_info *info);

/*
**MISC
*/
int		exist_in_tab(char *str, char **);
char		**tab_dup(char **);
int		my_perror(char *cmd, char *error);

/*
**SETUP
*/
t_info		*get_info(char **env);
void		*free_info(t_info **info);
t_token		*get_alias(t_token *, t_info *info, t_syntax *syntax);
void		free_alias(t_alias *alias);
t_token		*globbing(t_token *token, t_syntax *syntax);
t_command	*get_var(t_command *cmd, t_info *info);
int		null_alias(t_token *token);
int		qmark_var(t_info *info, t_command *cmd, int pos);
void		free_var(t_var *var);

/*
**ENV
*/
char		*getkey_hostname();
char		*getkey_pwd();
int		changekey(char **ae, char *key, char *value, int freeit);
char		**addkey(char **ae, char *key, char *value, int freeit);
char		**deletekey(char **ae, char *key, int freeit);
char		*getkey(char **ae, char *key, int dup);

/*
**SELECTOR
*/
int	auto_select(t_node *root, t_status *status, t_info *info);
int	exec_cmd(t_node *root, t_status *status, t_info *info);
int	exec_separ(t_node *root, t_status *status, t_info *info);
int	exec_logic(t_node *root, t_status *status, t_info *info);
int	exec_pipe(t_node *root, t_status *status, t_info *info);
int	exec_job(t_node *root, t_status *status, t_info *info);

/*
**SELECTOR/CMD
*/
int	load_redir(t_command *cmd, t_status *status);
int	redir_output(char *file);
int	double_redir_output(char *file);
int	redir_input(char *file);
int	double_redir_input(char *file);
void	my_undup(t_command *cmd, int save[3]);
void	my_dup(t_command *cmd, int *save);

/*
**EXECVE
*/
char	*my_pathfinder(t_command *cmd, t_info *info);
void	simple_exec(t_command *cmd, t_status *status, t_info *info);

/*
**STATUS
*/
void	auto_wait(t_status *status, t_info *info);
void	print_wait_job(t_status *status);
int	my_fork(t_command *cmd, t_status *status, t_info *info,
		void (*fct)(t_command *cmd, t_status *status, t_info *info));
int	my_fork_job(void *root, t_status *status, t_info *info,
		int (*fct)(t_node *root, t_status *status, t_info *info));
t_exit	*my_put_list_exit(t_exit **ll, int pid, int gpid, int last);
void	set_exit_value(t_exit *ll, int pid, int exitval);
void	show_exit_status(t_exit *ll);
int	my_del_exit(t_exit **ll, int mode);

/*
**BUILTINS
*/
void	builtin_echo(t_command *cmd, t_status *status, t_info *info);
void	builtin_cd(t_command *cmd, t_status *status, t_info *info);
void	builtin_setenv(t_command *cmd, t_status *status, t_info *info);
void	builtin_unsetenv(t_command *cmd, t_status *status, t_info *info);
void	builtin_exit(t_command *cmd, t_status *status, t_info *info);
void	builtin_alias(t_command *cmd, t_status *status, t_info *info);
void	builtin_unalias(t_command *cmd, t_status *status, t_info *info);
void	builtin_fg(t_command *cmd, t_status *status, t_info *info);
void	builtin_bg(t_command *cmd, t_status *status, t_info *info);
void	builtin_jobs(t_command *cmd, t_status *status, t_info *info);
void	builtin_set(t_command *cmd, t_status *stauts, t_info *info);
void	builtin_unset(t_command *cmd, t_status *status, t_info *info);
void	builtin_builtins(t_command *cmd, t_status *status, t_info *info);
void	builtin_history(t_command *cmd, t_status *status, t_info *info);
void	builtin_where(t_command *cmd, t_status *status, t_info *info);
void	sort_var(t_info *info);
void	check_loop(t_info *info);
int	my_strtablen(char **);
int	my_aliastablen(t_alias *alias);
int	my_vartablen(t_var *var);

/*
**LOAD
*/
void	load_rc(t_status *status, t_system *sys, t_syntax *syntax);

/*
**JOB
*/
t_job	*my_create_job(t_status *status, int pid, int pgid, int stats);
void	show_job_status(t_exit *ll);
int	get_free_job(t_exit *ll);
t_job	*get_job_by_number(t_exit *ll, int number);
int	fill_history(char *, t_info*);

/*
**HISTORY
*/
int	write_history(struct s_info *info);
int	load_history(struct s_info *info);
int	my_put_list_history(t_history **ll, char *history,
			    long time, int index);
int	my_del_list_history(t_history **ll, t_history *elem);
int	my_free_history(t_history **ll);
void	my_show_hist(t_history *ll);
char	*change_hist(char *cmd, t_info *info);
char	*history_fct_exclam(char *src, int *idx, t_history_info *history);
char	*history_fct_dollar(char *src, int *idx, t_history_info *history);
char	*history_fct_colon(char *src, int *idx, t_history_info *history);
char	*history_fct_dash(char *src, int *idx, t_history_info *history);
char	*history_fct_number(char *src, int *idx, t_history_info *history);
void	new_line_history(char *line, t_info *info);

/*
**OTHER
*/
int	asprintf(char **strp, const char *fmt, ...);

/*
**BACKQUOTE
*/
t_token	*get_system(char *cmd, t_system *sys);
int	do_backquote(t_token **token, t_system *sys);
void	redef_token(t_token *token);
void	redef_all(t_token *token);

/*
**SIGNAL
*/
void	signal_sigint();

#endif /* !EXEC_H_ */
