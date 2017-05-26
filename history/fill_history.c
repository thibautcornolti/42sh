/*
** fill_history.c for 42sh in /home/maje/Dropbox/delivery/B2/PSU/PSU_2016_42sh
**
** Made by maje
** Login   <marin.brunel@epitech.eu>
**
** Started on  Thu May 18 09:56:38 2017 maje
** Last update Sun May 21 23:38:14 2017 Thibaut Cornolti
*/
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include "syntax.h"
#include "exec.h"
#include "my.h"

static char		*get_path_history(t_info *info)
{
  int			len;
  char			*home;
  char			*path;

  if ((home = getkey(info->env, "HOME", 0)) == NULL)
    return (NULL);
  len = my_strlen(home);
  if (len > 0 && home[len - 1] != '/')
    path = my_strcatdup("/", FILE_HISTORY, 0);
  else
    path = my_strdup(FILE_HISTORY);
  if (path)
    path = my_strcatdup(home, path, 2);
  return (path);
}

int		write_history(t_info *info)
{
  char			*path;
  int			fd;
  t_history		*tmp;

  tmp = info->histo->start;
  if ((path = get_path_history(info)) == NULL)
    return (1);
  if ((fd = open(path, O_TRUNC| O_CREAT | O_WRONLY, 0644)) == -1)
    return (1);
  free(path);
  while (tmp)
    {
      dprintf(fd, "%ld#%s\n", tmp->time, tmp->cmd);
      tmp = tmp->next;
    }
  close(fd);
  return (0);
}

void	put_history(t_info *info, long time,
		    char *cmd, int idx)
{
  if (errno != 0)
    exit(84);
  if (info->histo->start == NULL)
    {
      my_put_list_history(&info->histo->start, cmd, time, idx);
      info->histo->current = info->histo->start;
    }
  else
    {
      my_put_list_history(&info->histo->current, cmd, time, idx);
      info->histo->current = info->histo->current->next;
    }
  free(cmd);
}

static void	end_loading(t_info *info, int idx)
{
  info->histo->end = info->histo->current;
  info->histo->current = NULL;
  info->histo->len = idx;
}

int		load_history(t_info *info)
{
  int		i;
  char		*path;
  long		time;
  char		*cmd;
  FILE		*stream;
  char		*line;
  size_t	len;

  if ((path = get_path_history(info)) == NULL ||
      (stream = fopen(path, "r")) == NULL)
    return (1);
  free(path);
  len = 0;
  line = NULL;
  i = 0;
  errno = 0;
  while ((getline(&line, &len, stream)) != -1 && ++i)
    {
      sscanf(line, "%ld#%m[^\n]s", &time, &cmd);
      put_history(info, time, cmd, i);
    }
  free(line);
  end_loading(info, i);
  fclose(stream);
  return (0);
}
