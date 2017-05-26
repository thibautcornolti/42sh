/*
** main.c for main.c in /home/cedric/delivery/ex
** 
** Made by Cédric Thomas
** Login   <cedric@epitech.net>
** 
** Started on  Sat Oct 22 10:31:05 2016 Cédric Thomas
** Last update Sun May 21 21:27:39 2017 Thibaut Cornolti
*/

#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <termio.h>
#include "my.h"
#include "get_next_command.h"
#include "syntax.h"
#include "exec.h"
#include "my_printf.h"

static int	setup_sh(t_system *sys, char **env)
{
  if ((sys->syntax = get_syntax()) == NULL)
    return (1);
  if ((sys->info = get_info(env)) == NULL)
    return (1);
  if ((sys->keypad = init_keypad(sys)) == NULL)
    return (1);
  my_memset(sys->status, 0, sizeof(t_status));
  signal(SIGINT, &signal_sigint);
  signal(SIGQUIT, SIG_IGN);
  signal(SIGTSTP, SIG_IGN);
  signal(SIGTTIN, SIG_IGN);
  signal(SIGTTOU, SIG_IGN);
  setpgid(getpid(), getpid());
  tcsetpgrp(0, getpgrp());
  getter_system(sys);
  return (0);
}

static int	free_sh(t_system *sys)
{
  int		exit;

  exit = sys->info->exit_value;
  my_del_exit(&(sys->status->exit_list), 1);
  free_syntax(&(sys->syntax));
  write_history(sys->info);
  free_info(&(sys->info));
  end_keypad(sys->keypad);
  return (exit);
}

int		my_system(char *command, t_system *system)
{
  void		*root;

  if ((root = parse_cmd(system->syntax, command, system)))
    {
      auto_select(root, system->status, system->info);
      my_free_tree(&root);
    }
  else
    {
      auto_wait(system->status, system->info);
      if (!isatty(0))
	system->status->exit = 1;
    }
  print_wait_job(system->status);
  system->status->pgid = 0;
  if (system->info->exit_arg)
    system->info->exit_value = 1;
  system->info->exit_arg = 0;
  my_del_exit(&(system->status->exit_list), 0);
  return (system->info->exit_value);
}

int		my_histo_system(char *command, t_system *system)
{
  command = change_hist(command, system->info);
  new_line_history(command, system->info);
  return (my_system(command, system));
}

int		main(int ac, char **av, char **env)
{
  t_system	system;
  t_status	status;
  char		*cmd;

  UNUSED(ac);
  UNUSED(av);
  system.status = &status;
  if (setup_sh(&(system), env))
    return (84);
  load_rc(system.status, &system, system.syntax);
  if (isatty(0))
    print_prompt(system.info);
  my_set_term(system.keypad);
  while (!system.status->exit && (cmd = get_next_cmd(system.keypad)))
    {
      my_reset_term(system.keypad);
      my_histo_system(cmd, &system);
      if (!system.status->exit && isatty(0) && cmd)
	print_prompt(system.info);
      my_set_term(system.keypad);
    }
  if (isatty(0))
    my_putstr("exit\n");
  return (free_sh(&system));
}
