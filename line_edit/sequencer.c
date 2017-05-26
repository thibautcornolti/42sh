/*
** sequencer.c for 42sh in /home/cedric/delivery/PSU/PSU_2016_42sh
** 
** Made by Cédric THOMAS
** Login   <cedric.thomas@epitech.eu>
** 
** Started on  Sat May 20 11:04:00 2017 Cédric THOMAS
** Last update Sun May 21 15:55:43 2017 Thibaut Cornolti
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

static void	std_key(t_keypad_fct *keys)
{
  keys[0].sequence = "\n";
  keys[0].fct = &enter;
  keys[1].sequence = tigetstr("kcub1");
  keys[1].fct = &left_arrow;
  keys[2].sequence = tigetstr("kcuf1");
  keys[2].fct = &right_arrow;
  keys[3].sequence = "\004";
  keys[3].fct = &end_of_file;
  keys[4].sequence = tigetstr("kbs");
  keys[4].fct = &delete_char;
  keys[5].sequence = tigetstr("kdch1");
  keys[5].fct = &suppr_char;
  keys[6].sequence = tigetstr("khome");
  keys[6].fct = &go_start;
  keys[7].sequence = tigetstr("kend");
  keys[7].fct = &go_end;
}

static void	advanced_key(t_keypad_fct *keys)
{
  keys[8].sequence = "\f";
  keys[8].fct = &bind_clear;
  keys[9].sequence = "\t";
  keys[9].fct = &auto_complete;
  keys[10].sequence = tigetstr("kcuu1");
  keys[10].fct = &up_arrow;
  keys[11].sequence = tigetstr("kcud1");
  keys[11].fct = &down_arrow;
  keys[12].sequence = "\v";
  keys[12].fct = &bind_copy;
  keys[13].sequence = "\031";
  keys[13].fct = &bind_paste;
  keys[14].sequence = "\025";
  keys[14].fct = &bind_copy_all;
  keys[15].sequence = "\033[1;5D";
  keys[15].fct = &ctrl_left_arrow;
  keys[16].sequence = "\033[1;5C";
  keys[16].fct = &ctrl_right_arrow;
  keys[17].sequence = "\006";
  keys[17].fct = &switch_mod;
}

void	sequencer(t_keypad_fct *keys)
{
  std_key(keys);
  advanced_key(keys);
}
