/**
 * Mindset PAC-MAN(tm)
 *
 * Author: Thomas Cherryhomes
 *  <thom.cherryhomes@gmail.com>
 */

#include <stdbool.h>
#include "libmindset_gfx.h"
#include "attract.h"
#include "palette.h"
#include "font.h"

bool bQuit=false;       // Quit program

int main(int argc, char* argv[])
{
  mindset_gfx_set_mode(2);
  mindset_gfx_set_palette(0,16,0,&palette);
  /* vblank_init(); */
  font_init();
  
  
  while (bQuit==false)
    {
      attract();
    }
  return 0;
}
