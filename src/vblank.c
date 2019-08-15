/**
 * Mindset PAC-MAN
 *
 * VBlank Routines
 */

#include <stdbool.h>
#include "libmindset_gfx.h"

unsigned short frame_cnt;          // Frame counter
bool frame_done;                   // Is frame done?

// Forward declaration for vblank handler.
void vblank_handler(void);

/** 
 * Attach callback to vblank
 */
void vblank_init(void)
{
  mindset_gfx_set_display_int_address(&vblank_handler);
}

/**
 * Detach callback from vblank
 */
void vblank_done(void)
{
  mindset_gfx_set_display_int_address(0);
}

/**
 * Wait for rest of frame.
 */
void vblank_wait(void)
{
  frame_done=false;
  while (frame_done==false) {}
}

/**
 * Pause for X number of frames
 */
void vblank_pause(unsigned short f)
{
  unsigned short i;
  for (i=0; i<f; i++)
    {
      vblank_wait();
    }
}

/**
 * Called once every vblank (60x sec)
 * Because the Mindset BIOS calls this from far, we have to
 * handle the entry and exit from this routine, ourselves.
 */
void vblank_handler(void)
{
  _asm("pushad");

  frame_cnt++;
  frame_done=true;
  
  _asm("popad; leave; retf");

}
