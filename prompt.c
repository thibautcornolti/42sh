/*
** main.c for main.c in /home/cedric/delivery/ex
**
** Made by Cédric Thomas
** Login   <cedric@epitech.net>
**
** Started on  Sat Oct 22 10:31:05 2016 Cédric Thomas
** Last update Sun May 21 18:33:20 2017 Cédric THOMAS
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>
#include "my.h"
#include "syntax.h"
#include "exec.h"
#include "my_printf.h"

static char	*get_real_path(char *path)
{
  char		buf[PATH_MAX + 1];
  char		*realdist;

  if ((realdist = realpath(path, buf)) == NULL)
    return (NULL);
  return (my_strdup(realdist));
}

static int	print_git_status(char *path)
{
  int		read;
  size_t	len;
  FILE		*stream;
  char		*line;

  len = 0;
  line = NULL;
  if (!path)
    return (1);
  path = my_strcatdup(path, "/.git/HEAD", 1);
  if ((stream = fopen(path, "r")) == NULL)
    return (1);
  if ((read = getline(&line, &len, stream)) == -1)
    return (1);
  printf("\033[36;01m git:(\033[31;01m");
  if (match(line, "ref: refs/heads/*"))
    printf("%.*s", read - 17, line + 16);
  else
    printf("%.7s", line);
  printf("\033[36;01m)\033[00m");
  fclose(stream);
  free(path);
  free(line);
  return (0);
}

static void	find_git(char *path)
{
  int		find;
  DIR		*dir;
  char		*parent_path;
  struct dirent	*dirent;

  if (!path || !my_strcmp(path, "/"))
    return ;
  if ((dir = opendir(path)) == NULL)
    return ;
  find = 0;
  while ((dirent = readdir(dir)) != NULL && !find)
    if (my_strcmp(".git", dirent->d_name) == 0)
      if (!print_git_status(my_strdup(path)))
	find = 1;
  closedir(dir);
  if (find == 0)
    {
      if (path[my_strlen(path)] != '/')
	path = my_strcatdup(path, "/", 1);
      path = my_strcatdup(path, "..", 1);
      parent_path = get_real_path(path);
      find_git(parent_path);
    }
  free(path);
}

static void	print_pwd(t_info *info)
{
  char		*home;
  int		i;

  i = my_strlen(info->pwd);
  home = getkey(info->env, "HOME", 0);
  printf("\033[34;01m");
  if (home && !my_strcmp(info->pwd, home))
    printf("~");
  else
    {
      while (i > 0 && info->pwd[i] != '/')
	i -= 1;
      if (i != 0)
	i += 1;
      printf("%s", info->pwd + i);
    }
  printf("\033[00m");
}

void	print_prompt(t_info *info)
{
  if ((info->exit_value) != 0)
    printf("\033[31;01m➜ %u \033[00m", info->exit_value);
  else
    printf("\033[32;01m➜ %u \033[00m", info->exit_value);
  print_pwd(info);
  find_git(my_strdup(info->pwd));
  printf(" ");
  fflush(stdout);
}
