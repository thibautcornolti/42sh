/*
** key.c for key in /home/cedric/delivery/PSU/PSU_2016_minishell1
** 
** Made by 
** Login   <cedric.thomas@epitech.eu>
** 
** Started on  Thu Jan  5 10:13:49 2017 
** Last update Tue May  9 10:27:25 2017 
*/
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <limits.h>
#include "get_next_line.h"
#include "my.h"

char	*getkey_pwd()
{
  char	*pwd;

  if ((pwd = getcwd(NULL, PATH_MAX)) == NULL)
    return (NULL);
  return (pwd);
}

char		*getkey_hostname()
{
  char		*host;
  int		fd;

  if (access("/etc/hostname", R_OK) < 0)
    return (NULL);
  if ((fd = open("/etc/hostname", O_RDONLY)) == -1)
    return (NULL);
  host = get_next_line(fd);
  while (get_next_line(fd));
  close(fd);
  return (host);
}
