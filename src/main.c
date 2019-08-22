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

bool bQuit=false;       // Quit program
extern bool frame_done;

int main(int argc, char* argv[])
{
  mindset_gfx_set_mode(2);
  mindset_gfx_set_palette(0,16,0,&palette);
  vblank_init();
  font_init();
  score_reset();
  
  maze_draw();

  // Temporary
  lives_reset();
  lives_display();
  score_reset();
  score_header_hi();
  score_display_hi();
  score_header_1up(false);
  score_display_1up();
  score_header_2up(false);
  score_display_2up();
  stage_display(4);
  dots_plot();
  vblank_done();

  while (!kbhit()) {}
  
  return 0;
}
