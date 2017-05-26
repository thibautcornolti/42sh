##
## Makefile for Makefile in /home/cedric/lib
## 
## Made by Cédric Thomas
## Login   <cedric@epitech.net>
## 
## Started on  Sat Oct 22 10:37:32 2016 Cédric Thomas
## Last update Sun May 21 23:45:01 2017 Thibaut Cornolti
##

EXEC		=	auto_selector.c			\
			selector/cmd.c			\
			selector/pipe.c			\
			selector/separ.c		\
			selector/logic.c		\
			selector/job.c			\
			selector/cmd/redirections.c	\
			selector/cmd/auto_redir.c	\
			selector/cmd/dup.c		\
			builtin/echo.c			\
			builtin/setenv.c		\
			builtin/unsetenv.c		\
			builtin/cd.c			\
			builtin/exit.c			\
			builtin/fg.c			\
			builtin/alias.c			\
			builtin/alias_len.c		\
			builtin/unalias.c		\
			builtin/jobs.c			\
			builtin/bg.c			\
			builtin/loop.c			\
			builtin/set.c			\
			builtin/set_tools.c		\
			builtin/unset.c			\
			builtin/builtins.c		\
			builtin/history.c		\
			builtin/where.c			\
			status/list_status.c		\
			status/list_job.c		\
			status/wait.c			\
			status/wait_job.c		\
			status/fork.c			\
			setup/info.c			\
			setup/get_alias.c		\
			setup/null_alias.c		\
			setup/get_var.c			\
			setup/qmark_var.c		\
			setup/glob.c			\
			env/env.c			\
			env/key.c			\
			execve/std_exec.c		\
			execve/pathfinder.c		\
			misc/str.c			\
			misc/tab.c

PARSE		=	parsing.c			\
			misc/tab.c			\
			misc/misc.c			\
			misc/quote.c			\
			misc/separators.c		\
			misc/alloc.c			\
			lexer/lexer.c			\
			lexer/list_lexer.c		\
			shape/shape_str.c		\
			shape/shape_token.c		\
			tree/tree.c			\
			tree/redir_list.c		\
			tree/tree_list.c		\
			error/input_lexer.c		\
			error/error_pipe_node.c		\
			error/error_command_node.c	\
			error/error_redir_node.c	\
			error/error_logic_node.c	\
			backquote/backquote.c		\
			backquote/backquote_fork.c	\

MATCH		=	match.c				\
			fct/amp.c			\
			fct/star.c			\
			fct/hook.c			\
			fct/inter.c			\
			fct/parent.c			\
			fct/escape.c			\
			fct/braquet.c			\
			fct/inib.c			\

NODE		=	command_node.c			\
			standard_node.c			\
			pipe_node.c			\

HISTORY		=	fill_history.c			\
			list_history.c			\
			args_hist.c			\
			fct_history.c

LOAD		=	rc.c				\

LINE		=	line_edit/get_next_cmd.c	\
			line_edit/str.c			\
			line_edit/setup.c		\
			line_edit/sequencer.c		\
			binds/std_binds.c		\
			binds/pos_binds.c		\
			binds/del_binds.c		\
			binds/complete/auto_complete.c	\
			binds/complete/auto_history.c	\
			binds/complete/search_exec.c	\
			binds/complete/complete_line.c	\
			binds/history.c			\
			binds/default_bind.c		\
			binds/copy_paste.c		\
			binds/ctrl_arrow.c		\
			binds/sig.c

MAIN		=	main.c				\
			prompt.c			\
			getter.c			\

OBJ		=	$(MAIN:.c=.o)
OBJ		+=	$(LINE:.c=.o)
OBJ		+=	$(addprefix history/, $(HISTORY:.c=.o))
OBJ		+=	$(addprefix parse/, $(PARSE:.c=.o))
OBJ		+=	$(addprefix match/, $(MATCH:.c=.o))
OBJ		+=	$(addprefix node/, $(NODE:.c=.o))
OBJ		+=	$(addprefix exec/, $(EXEC:.c=.o))
OBJ		+=	$(addprefix load/, $(LOAD:.c=.o))

NAME		=	42sh

LIB_F		=	./lib/

LIB		=	-lmy -lmyprintf -lgnl -lalloc -lncurses

INCLUDE		=	-I./include/

CFLAGS		+=	 $(INCLUDE) -W -Wall -Wextra

REDDARK         =       \033[31;2m

RED             =       \033[31;1m

GREEN           =       \033[32;1m

YEL             =       \033[33;1m

BLUE            =       \033[34;1m

PINK            =       \033[35;1m

CYAN            =       \033[36;1m

RES             =       \033[0m

all:		$(NAME)

$(NAME): .CMPLIB .SILENT

.CMPLIB:
	@echo "$(CYAN)Compiling libmy...$(RES)"
	@make --no-print-directory -sC lib/my
	@echo "\t$(GREEN)OK$(RES)$(CYAN)!$(RES)"
	@echo "$(CYAN)Compiling liballoc...$(RES)"
	@make --no-print-directory -sC lib/libmalloc
	@echo "\t$(GREEN)OK$(RES)$(CYAN)!$(RES)"
	@echo "$(CYAN)Compiling libmyprintf...$(RES)"
	@make --no-print-directory -sC lib/my_printf
	@echo "\t$(GREEN)OK$(RES)$(CYAN)!$(RES)"
	@echo "$(CYAN)Compiling libgnl...$(RES)"
	@make --no-print-directory -sC lib/GNL
	@echo "\t$(GREEN)OK$(RES)$(CYAN)!$(RES)"
	@echo

.SILENT:$(OBJ)
	@echo
	@echo "$(GREEN)Everything compiled smoothly. Now compiling dependancies...$(RES)"
	@echo
	@echo "$(CYAN)Linking $(NAME)...$(RES)"
	@gcc -o $(NAME) $(OBJ) -L$(LIB_F) $(LIB)
	@echo "\t$(GREEN)OK$(RES)$(CYAN)!$(RES)"
	@echo
	@echo "$(GREEN)---- $(NAME) READY ----$(RES)"
	@echo

clean:
		@$(foreach var, $(OBJ), if [ -e $(var) ] ; then \
		printf "[$(RED)RM$(RES)] $(YEL)$(var)$(RES)\n" \
		&& $(RM) $(var) ; fi ;)
		@make --no-print-directory -sC lib/GNL fclean
		@make --no-print-directory -sC lib/my fclean
		@make --no-print-directory -sC lib/my_printf fclean
		@make --no-print-directory -sC lib/libmalloc fclean
		@rm -f $(OBJ)
		@echo "$(GREEN)---- $(NAME) CLEANED ----$(RES)"
		@echo

fclean:		clean
		@if [ -e $(NAME) ] ; then \
		printf "[$(RED)RM EXEC$(RES)] $(YEL)$(NAME)$(RES)\n" \
		&& rm -f $(NAME) ; fi
		@rm -f $(NAME)
		@echo "$(GREEN)---- $(NAME) REMOVED ----$(RES)"
		@echo


re: 		fclean all

%.o:	%.c
	@echo "[$(RED)COMPILE$(RES)] $(YEL)$<$(RES) $(BLUE)=>$(RES) $(YEL)$@$(RES)"
	@gcc $(CFLAGS) -o $@ -c $<

.PHONY: all clean fclean re
