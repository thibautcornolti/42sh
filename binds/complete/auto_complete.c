/*
** auto_complete.c for 42sh in /home/cedric/Desktop/get_next_cmd
**
** Made by Cédric THOMAS
** Login   <cedric.thomas@epitech.eu>
**
** Started on  Tue May 16 14:34:55 2017 Cédric THOMAS
** Last update Sat May 20 15:42:50 2017 maje
*/
#include <unistd.h>
#include <curses.h>
#include <dirent.h>
#include <stdlib.h>
#include <stdio.h>
#include <termio.h>
#include "syntax.h"
#include "exec.h"
#include "my_printf.h"
#include "get_next_command.h"
#include "my.h"
#include "match.h"

static void	exec_complete(char **tab, t_keypad *key)
{
  unsigned int	exit_val;
  int		i;
  char		*cmd;

  i = -1;
  if ((cmd = my_strdup("echo '")) == NULL)
    exit(84);
  while (tab && tab[++i])
    {
      if ((cmd = my_strcatdup(cmd, tab[i], 1)) == NULL)
	exit(84);
      if ((cmd = my_strcatdup(cmd, "\n", 1)) == NULL)
	exit(84);
    }
  if ((cmd = my_strcatdup(cmd, "' | sort | column", 1)) == NULL)
    exit(84);
  exit_val = key->sys->info->exit_value;
  my_system(cmd, key->sys);
  key->sys->info->exit_value = exit_val;
}

int		add_matched(char ***tab, char *str, char *pattern, int *size)
{
  if (str[0] == '.' && pattern[0] != '.')
    return (0);
  if (advanced_match(str, pattern) &&
      exist_in_tab(str, *tab) < 0)
    {
      if ((*tab = realloc(*tab, (sizeof(char *) * (*size + 2)))) == NULL)
	exit(84);
      if (((*tab)[*size] = my_strdup(str)) == NULL)
	exit(84);
      (*tab)[*size + 1] = NULL;
      *size += 1;
      return (1);
    }
  return (0);
}

int		add_matching_files(char *folder, char *pattern,
				   int *size, char ***tab)
{
  DIR		*dir;
  struct dirent	*dirent;

  pattern = my_strcatdup(pattern, "*", 0);
  if ((dir = opendir(folder)) == NULL)
    {
      free(pattern);
      return (1);
    }
  while ((dirent = readdir(dir)) != NULL)
    if (add_matched(tab, dirent->d_name, pattern, size)
	&& (dirent->d_type & DT_DIR))
      if (((*tab)[*size - 1] = my_strcatdup((*tab)[*size - 1],
					    "/", 1) ) == NULL)
	exit(84);
  closedir(dir);
  free(pattern);
  return (0);
}

void		get_folder_and_path(char *full_path,
				    char **path, char **file)
{
  int		i;

  i = my_strlen(full_path);
  while (full_path[i] != '/' && i > 0)
    i -= 1;
  if (full_path[i] == '/')
    i += 1;
  if (i == 0)
    *path = my_strdup(".");
  else
    *path = my_strndup(full_path, i);
  if (full_path[i] == 0)
    *file = my_strdup("");
  else
    *file = my_strdup(full_path + i);
}

int		auto_complete(t_keypad *key)
{
  int		size;
  char		**files;

  if (key->line == NULL)
    if ((key->line = my_strdup("")) == NULL)
      exit(84);
  if (key->mod)
    return (complete_history(key));
  size = 0;
  files = NULL;
  search_all(key, &files, &size);
  if (size == 1)
    del_raw_line(key);
  if (one_find(key, files, size) > 0 && files)
    {
      my_printf("\n");
      exec_complete(files, key);
      print_line(key);
    }
  if (size == 1)
    print_raw_line(key);
  free_tab(files);
  return (0);
}
