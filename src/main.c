/**
 * Mindset PAC-MAN(tm)
 *
 * Author: Thomas Cherryhomes
 *  <thom.cherryhomes@gmail.com>
 */

#include <conio.h>
#include <stdbool.h>
#include "libmindset_gfx.h"
#include "attract.h"
#include "palette.h"
#include "font.h"
#include "vblank.h"
#include "maze.h"
#include "score.h"
#include "lives.h"
#include "stage.h"
#include "dots.h"
#include "game.h"

bool bQuit=false;       // Quit program
extern bool frame_done;

int main(int argc, char* argv[])
{
  mindset_gfx_set_mode(2);
  mindset_gfx_set_palette(0,16,0,&palette);
  mindset_gfx_set_transfer_mode(0,0);
  vblank_init();
  font_init();

  // Temporary
  game_run();
  

  vblank_done();
  
  return 0;
}
