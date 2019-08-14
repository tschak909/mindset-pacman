/**
 * Mindset PAC-MAN
 *
 * Font initialization to be used by BLT STRING calls
 */

#include <i86.h>
#include "libmindset_gfx.h"
#include "font.h"
#include "chars.h"

/**
 * Font color table for solid color output
 */
unsigned char font_color_table[16]=
  {
    0x00,
    0x11,
    0x22,
    0x33,
    0x44,
    0x55,
    0x66,
    0x77,
    0x88,
    0x99,
    0xAA,
    0xBB,
    0xCC,
    0xDD,
    0xEE,
    0xFF
  };

Font f;

/**
 * Set font pointer for BLT STRING calls
 */
void font_init(void)
{
  f.type=0;
  f.excess=0;
  f.nominal_width=8;
  f.nominal_height=8;
  f.byte_width=1024;
  f.addr=MK_FP(FP_SEG(fontdata),FP_OFF(fontdata));
  f.first=0x00;
  f.last=0xFF;

  mindset_gfx_set_font_pointer(&f);
}
