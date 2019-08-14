/**
 * Mindset PAC-MAN
 *
 * Attract mode
 */

#include <i86.h>
#include <stdbool.h>
#include <conio.h>
#include "libmindset_gfx.h"
#include "attract.h"

extern bool bQuit;
extern unsigned short font_color_table[];

char* test="PAC-MAN";
Text t;
unsigned char c;

/**
 * Run Attract mode screen
 */
void attract(void)
{
  t.x=0x0040;
  t.y=0x0040;
  t.len=7;
  t.off=FP_OFF(test);
  t.seg=FP_SEG(test);
   
  mindset_gfx_blt_string(0,1,0,0,0xFF,0,0,&t);

  while (!kbhit())
    {
      t.x=rand()&0xFF;
      t.y=rand()&0x7F;
      c=font_color_table[rand()&0x0F];
      mindset_gfx_blt_string(0,1,0,0,c,0,0,&t);
    }

  bQuit=true;
}

