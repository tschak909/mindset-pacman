/**
 * Mindset PAC-MAN
 *
 * VBlank Routines
 */

#include "libmindset_gfx.h"

/** 
 * Attach callback to vblank
 */
void vblank_init(void);

/**
 * Wait for rest of frame.
 */
void vblank_wait(void);

/**
 * Pause for X number of frames
 */
void vblank_pause(unsigned short f);

/**
 * Detach callback from vblank
 */
void vblank_done(void);
