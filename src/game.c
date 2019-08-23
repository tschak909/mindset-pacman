/**
 * Mindset PAC-MAN
 *
 * Main Game Code
 */

#include <i86.h>
#include <stdbool.h>
#include "libmindset_gfx.h"
#include "game.h"
#include "score.h"
#include "stage.h"
#include "dots.h"
#include "lives.h"
#include "maze.h"
#include "vblank.h"

#define NUM_OBJECTS 1
#define BP_SIZE 10*NUM_OBJECTS

#define READY_X 72
#define READY_Y 105

#define GAME_OVER_X 56
#define GAME_OVER_Y 105

unsigned char current_player;
unsigned short game_bp[BP_SIZE];

extern const unsigned short dot_to_pixel_x[];
extern const unsigned short dot_to_pixel_y[];

unsigned char pacman_x,pacman_lx;
unsigned char pacman_y,pacman_ly;
Direction pacman_direction, pacman_direction_last=LEFT;
unsigned char pacman_dx,pacman_dy;
unsigned char pacman_frame_cnt;

extern unsigned long score_hi, score_1up, score_2up;   // scores
extern const unsigned char pacman_13_left_0[];
extern const unsigned char inky_1_right[];

extern const unsigned short pixel_to_dot_x[];
extern const unsigned short pixel_to_dot_y[];

extern const unsigned char dotmap[1024];

extern unsigned char frame_done;
extern unsigned short frame_cnt;

const char* ready="READY[";       // READY!
const char* ready_blank="      "; // blank
const char* game_over="GAME OVER"; // GAME OVER
const char* game_over_blank="         "; // blank

unsigned short ready_tp[5]={READY_X,READY_Y,6,0,0};
unsigned short game_over_tp[5]={GAME_OVER_X,GAME_OVER_Y,9,0,0};

/**
 * New game, reset everything
 */
void game_new(void)
{
  // Test fixture // remove
  pacman_x=pacman_lx=dot_to_pixel_x[27];
  pacman_y=pacman_ly=dot_to_pixel_y[1];
  
  lives_reset();
  score_new_game();
  stage_cherry();
  dots_new_game();
  stage_display(current_player);
  lives_display(current_player);
  maze_draw();
  dots_plot(current_player);
}

/**
 * Run game
 */
void game_run(void)
{
  game_new();
  while(true)
    {
      game_loop();
    }
}

/**
 * Display READY!
 */
void game_display_ready(bool display)
{
  union REGPACK regs;
  ready_tp[3]=(display==true ? FP_OFF(ready) : FP_OFF(ready_blank));
  ready_tp[4]=(display==true ? FP_SEG(ready) : FP_OFF(ready_blank));

  // Set up text string call
  regs.h.ah=0x21;       // BLT STRING
  regs.h.al=1;          // BLT ID 1
  regs.h.ch=1;          // # of text pointer structs
  regs.h.cl=0;          // # of text chars to ignore at beginning of string (none)
  regs.h.dh=0;          // draw left to right
  regs.h.dl=0x11;       // color
  regs.w.si=0;          // X origin
  regs.w.di=0;          // Y origin
  regs.w.es=FP_SEG(ready_tp); // Text pointer (seg)
  regs.w.bx=FP_OFF(ready_tp); // Text pointer (off)
  intr(0xEF,&regs);
}

/**
 * Display READY!
 */
void game_display_game_over(bool display)
{
  union REGPACK regs;
  game_over_tp[3]=(display==true ? FP_OFF(game_over) : FP_OFF(game_over_blank));
  game_over_tp[4]=(display==true ? FP_SEG(game_over) : FP_OFF(game_over_blank));

  // Set up text string call
  regs.h.ah=0x21;       // BLT STRING
  regs.h.al=1;          // BLT ID 1
  regs.h.ch=1;          // # of text pointer structs
  regs.h.cl=0;          // # of text chars to ignore at beginning of string (none)
  regs.h.dh=0;          // draw left to right
  regs.h.dl=0x22;       // color
  regs.w.si=0;          // X origin
  regs.w.di=0;          // Y origin
  regs.w.es=FP_SEG(game_over_tp); // Text pointer (seg)
  regs.w.bx=FP_OFF(game_over_tp); // Text pointer (off)
  intr(0xEF,&regs);
}

/**
 * Plot blitter objects
 */
void game_plot(void)
{
  union REGPACK regs;
  // PAC-MAN
  game_bp[0]=FP_OFF(pacman_13_left_0);
  game_bp[1]=FP_SEG(pacman_13_left_0);
  game_bp[2]=8;
  game_bp[3]=0;
  game_bp[4]=0;
  game_bp[5]=pacman_x;
  game_bp[6]=pacman_y;
  game_bp[7]=13;
  game_bp[8]=11;
  game_bp[9]=0xFFFF;

  // Set up the BLT COPY
  regs.h.ah=0x08;       // BLT copy
  regs.h.al=1;          // BLT id
  regs.w.cx=1;         // # of blits to do
  regs.w.dx=0;          // Top/bottom, left/right normal blit
  regs.w.si=-6;          // X origin
  regs.w.di=-3;          // Y origin
  regs.w.es=FP_SEG(game_bp); // pointer to blitter params
  regs.w.bx=FP_OFF(game_bp); // ""      "" 
  intr(0xEF,&regs);  
}

/**
 * Check for maze collision
 * Returns dx and dy values
 */
void game_check_maze_collision(unsigned short x, unsigned short y, Direction d, unsigned char* dx, unsigned char* dy)
{
  unsigned short tx=pixel_to_dot_x[x]; // Tile positions
  unsigned short ty=pixel_to_dot_y[y];

  // derive adjacent tile
  switch(d)
    {
    case RIGHT:
      tx++;
      break;
    case DOWN:
      ty++;
      break;
    case LEFT:
      tx--;
      break;
    case UP:
      ty--;
      break;
    }

  if (dotmap[ty+tx]>0xFC)
    {
      // We hit a wall, zero out dx/dy
      dx=dy=0;
    }
}

/**
 * Check pac-man's collisions
 */
void game_check_collisions_pacman(void)
{
  game_check_maze_collision(pacman_x,pacman_y,pacman_direction,&pacman_dx,&pacman_dy);
}

/**
 * Check for collisions (software)
 */
void game_check_collisions(void)
{
  game_check_collisions_pacman();
}

/**
 * Animate objects according to frame count
 */
void game_animate_objects(void)
{
  // Stuff that happens every other frame.
  if (frame_cnt&1==0)
    {
      if ((pacman_dx==0) && (pacman_dy==0))
	pacman_frame_cnt=0;
      else if (pacman_frame_cnt>3)
	pacman_frame_cnt=0;
      else
	pacman_frame_cnt++;
    }
}

/**
 * Move objects according to their dx/dy
 */
void game_move_objects(void)
{
  pacman_lx=pacman_x;
  pacman_ly=pacman_y;
  pacman_x+=pacman_dx;
  pacman_y+=pacman_dy;
}

/**
 * Game frame loop
 */
void game_loop(void)
{
  frame_done=false;

  game_check_collisions();
  game_move_objects();
  game_plot();
  
  vblank_wait();
}
