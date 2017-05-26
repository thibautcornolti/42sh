/*
** sig.c for 42sh in /home/thibrex/Dropbox/delivery/PSU/PSU_2016_42sh
** 
** Made by Thibaut Cornolti
** Login   <thibaut.cornolti@epitech.eu>
** 
** Started on  Sat May 20 00:13:21 2017 Thibaut Cornolti
** Last update Sat May 20 00:22:50 2017 Thibaut Cornolti
*/

#include <unistd.h>
#include <stdlib.h>
#include <termio.h>
#include "syntax.h"
#include "exec.h"
#include "get_next_command.h"
#include "my_printf.h"

void		signal_sigint()
{
  t_system	*system;

  system = getter_system(NULL);
  my_printf("\n");
  print_prompt(system->info);
  free(system->keypad->line);
  system->keypad->line = NULL;
  system->keypad->index = 0;
}
