/**
 * Mindset PAC-MAN
 * Maze Data and display routines
 *
 * Author: Thomas Cherryhomes <thom.cherryhomes@gmail.com>
 */

#include <i86.h>
#include "maze.h"
#include "maze_linedata.h"

#include "libmindset_gfx.h"

 
/**
 * Initialize Maze string data
 */
void maze_init(void)
{
}

/**
 * Draw the maze
 */
void maze_draw(void)
{
  union REGPACK regs;

  // Draw border
  
  regs.h.ah=0x0D;  // BLT POLYLINE
  regs.h.al=0x22;  // maze
  regs.w.cx=184;
  regs.h.dh=0x44; // Blue
  regs.h.dl=1;    // paired
  regs.w.si=0;
  regs.w.di=0;
  regs.w.es=FP_SEG(m1);
  regs.w.bx=FP_OFF(m1);
  intr(0xEF,&regs);

  // Draw first 10 maze features
  regs.h.ah=0x0D;  // BLT POLYLINE
  regs.h.al=0x22;  // maze
  regs.w.cx=214;
  regs.h.dh=0x44; // Blue
  regs.h.dl=1;    // paired
  regs.w.si=0;
  regs.w.di=0;
  regs.w.es=FP_SEG(m2);
  regs.w.bx=FP_OFF(m2);
  intr(0xEF,&regs);

  // Draw next 10 maze features
  regs.h.ah=0x0D;  // BLT POLYLINE
  regs.h.al=0x22;  // maze
  regs.w.cx=240;
  regs.h.dh=0x44; // Blue
  regs.h.dl=1;    // paired
  regs.w.si=0;
  regs.w.di=0;
  regs.w.es=FP_SEG(m3);
  regs.w.bx=FP_OFF(m3);
  intr(0xEF,&regs);
  
}
