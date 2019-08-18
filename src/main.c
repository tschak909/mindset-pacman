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

bool bQuit=false;       // Quit program
extern bool frame_done;

int main(int argc, char* argv[])
{
  mindset_gfx_set_mode(2);
  mindset_gfx_set_palette(0,16,0,&palette);
  vblank_init();
  font_init();

  maze_draw();

  vblank_done();
  return 0;
}
