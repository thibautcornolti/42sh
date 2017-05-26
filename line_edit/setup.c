/*
** setup.c for GNC in /home/cedric/Desktop/get_next_cmd
**
** Made by
** Login   <cedric.thomas@epitech.eu>
**
** Started on  Fri Apr 21 22:15:37 2017
** Last update Sun May 21 18:27:10 2017 Cédric THOMAS
*/
#include <unistd.h>
#include <stdlib.h>
#include <termio.h>
#include <curses.h>
#include <sys/ioctl.h>
#include <term.h>
#include "syntax.h"
#include "exec.h"
#include "my.h"
#include "my_alloc.h"
#include "get_next_command.h"

int		my_set_term(t_keypad *keypad)
{
  char		*smkx;

  if (!keypad->valid)
    return (0);
  if (ioctl(0, TCGETA, &keypad->term) == -1)
    return (1);
  keypad->term.c_lflag &= ~(ICANON | ECHO);
  keypad->term.c_cc[VTIME] = 0;
  keypad->term.c_cc[VMIN] = 0;
  if (ioctl(0, TCSETA, &keypad->term) == -1)
    return (1);
  if ((smkx = tigetstr("smkx")) == (char *)-1)
    return (1);
   my_putstr(smkx);
  return (0);
}

int		my_reset_term(t_keypad *keypad)
{
  char		*rmkx;

  if (!keypad->valid)
    return (0);
  if ((rmkx = tigetstr("rmkx")) == (char *)-1)
    return (1);
  my_putstr(rmkx);
  if (ioctl(0, TCGETA, &keypad->term) == -1)
    return (1);
  keypad->term.c_lflag |= (ICANON | ECHO);
  if (ioctl(0, TCSETA, &keypad->term) == -1)
    return (1);
  return (0);
}

t_keypad	*init_keypad(struct s_system *sys)
{
  int		i;
  t_keypad	*keypad;

  if ((keypad = malloc(sizeof(t_keypad))) == NULL)
    return (NULL);
  my_memset(keypad, 0, sizeof(t_keypad));
  keypad->sys = sys;
  if (!isatty(0) || !getkey(sys->info->env, "TERM", 0))
    return (keypad);
  setupterm(NULL, 0, NULL);
  sequencer(keypad->keys);
  i = -1;
  while (++i < KEY_LINKED)
    if (keypad->keys[i].sequence == (char *) -1)
      return (keypad);
  keypad->valid = 1;
  return (keypad);
}

void		*end_keypad(t_keypad *keypad)
{
  free(keypad->matched);
  free(keypad->line);
  free(keypad);
  return (NULL);
}
