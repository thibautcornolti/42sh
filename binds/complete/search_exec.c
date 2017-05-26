/*
** search_exec.c for 42sh in /home/cedric/delivery/PSU/PSU_2016_42sh/binds/complete
** 
** Made by Cédric THOMAS
** Login   <cedric.thomas@epitech.eu>
** 
** Started on  Wed May 17 23:28:15 2017 Cédric THOMAS
** Last update Sun May 21 17:23:00 2017 Thibaut Cornolti
*/
#include <unistd.h>
#include <stdlib.h>
#include <termio.h>
#include "syntax.h"
#include "exec.h"
#include "my_printf.h"
#include "get_next_command.h"
#include "my.h"
#include "match.h"

static void	search_alias_builtins(t_keypad *key, char ***files,
				      int *size, char *cmd)
{
  char		*current;
  int		i;

  i = -1;
  while (++i < BUILTINS_NB)
    {
      if ((current = my_strcatdup(cmd, "*", 0)) == NULL)
	exit(84);
      add_matched(files, key->sys->info->builtins[i], current, size);
      free(current);
    }
  i = -1;
  while (key->sys->info->alias && key->sys->info->alias[++i].link)
    {
      if ((current = my_strcatdup(cmd, "*", 0)) == NULL)
	exit(84);
      add_matched(files, key->sys->info->alias[i].link, current, size);
      free(current);
    }
}

static void	search_cmd(t_keypad *key, char ***files,
			   int *size, char *cmd)
{
  int		i;
  char		*key_path;
  char		**path;

  if ((key_path = getkey(key->sys->info->env, "PATH", 0)) != NULL)
    {
      if ((path = my_split(key_path, ':')) == NULL)
	exit(84);
      i = -1;
      while (path[++i])
	{
	  if (my_strlen(path[i]) > 0 &&
	      path[i][my_strlen(path[i]) - 1] != '/')
	    if ((path[i] = my_strcatdup(path[i], "/", 1)) == NULL)
	      exit(84);
	  add_matching_files(path[i], cmd, size, files);
	}
      free_tab(path);
    }
}

static void	free_searcher(t_token *token, char *file, char *path)
{
  free(file);
  free(path);
  my_free_token(&token);
}

void		search_all(t_keypad *key, char ***files, int *size)
{
  t_token	*temp;
  t_token	*token;
  char		*file;
  char		*path;

  token = get_token(my_strndup(key->line, key->index),
		    key->sys->syntax, NULL, 1);
  temp = token;
  while (temp && temp->next)
    temp = temp->next;
  if (temp == NULL ||
      (key->index > 0 && is_in(key->line[key->index - 1], SKIP)))
    get_folder_and_path("", &path, &file);
  else
    {
      if (!is_in('/', temp->token) && temp->type == T_COMMAND)
	{
	  search_cmd(key, files, size, temp->token);
	  search_alias_builtins(key, files, size, temp->token);
	}
      get_folder_and_path(temp->token, &path, &file);
    }
  add_matching_files(path, file, size, files);
  free_searcher(token, file, path);
}
