/**
 * Lives display
 */

#include <i86.h>

unsigned char num_lives;
unsigned short lives_bp[50];

#define MAX_LIVES 3

#define LIVES_Y_OFFSET 184
#define LIVES_X_OFFSET_START 304
#define LIVES_X_OFFSET_SCOOT 24

#define BOB_X_SIZE 16
#define BOB_Y_SIZE 16

extern const unsigned char blank[];
extern const unsigned char pacman_left_1[];

/**
 * Display number of lives
 */
void lives_display(void)
{
  union REGPACK regs;
  unsigned short lives_x_offset=LIVES_X_OFFSET_START;
  
  lives_bp[ 0]=(num_lives>1 ? FP_OFF(pacman_left_1) : FP_OFF(blank));
  lives_bp[ 1]=(num_lives>1 ? FP_SEG(pacman_left_1) : FP_SEG(blank));
  lives_bp[ 2]=8; // stride size
  lives_bp[ 3]=0;
  lives_bp[ 4]=0;
  lives_bp[ 5]=lives_x_offset;
  lives_bp[ 6]=LIVES_Y_OFFSET;
  lives_bp[ 7]=BOB_X_SIZE;
  lives_bp[ 8]=BOB_Y_SIZE;
  lives_bp[ 9]=0xFFFF; // write mask, all pixels.
  lives_x_offset-=LIVES_X_OFFSET_SCOOT;
  
  lives_bp[10]=(num_lives>2 ? FP_OFF(pacman_left_1) : FP_OFF(blank));
  lives_bp[11]=(num_lives>2 ? FP_SEG(pacman_left_1) : FP_SEG(blank));
  lives_bp[12]=8; // stride size
  lives_bp[13]=0;
  lives_bp[14]=0;
  lives_bp[15]=lives_x_offset;
  lives_bp[16]=LIVES_Y_OFFSET;
  lives_bp[17]=BOB_X_SIZE;
  lives_bp[18]=BOB_Y_SIZE;
  lives_bp[19]=0xFFFF; // write mask, all pixels.
  lives_x_offset-=LIVES_X_OFFSET_SCOOT;

  lives_bp[20]=(num_lives>3 ? FP_OFF(pacman_left_1) : FP_OFF(blank));
  lives_bp[21]=(num_lives>3 ? FP_SEG(pacman_left_1) : FP_SEG(blank));
  lives_bp[22]=8; // stride size
  lives_bp[23]=0;
  lives_bp[24]=0;
  lives_bp[25]=lives_x_offset;
  lives_bp[26]=LIVES_Y_OFFSET;
  lives_bp[27]=BOB_X_SIZE;
  lives_bp[28]=BOB_Y_SIZE;
  lives_bp[29]=0xFFFF; // write mask, all pixels.
  lives_x_offset-=LIVES_X_OFFSET_SCOOT;
  
  lives_bp[30]=(num_lives>4 ? FP_OFF(pacman_left_1) : FP_OFF(blank));
  lives_bp[31]=(num_lives>4 ? FP_SEG(pacman_left_1) : FP_SEG(blank));
  lives_bp[32]=8; // stride size
  lives_bp[33]=0;
  lives_bp[34]=0;
  lives_bp[35]=lives_x_offset;
  lives_bp[36]=LIVES_Y_OFFSET;
  lives_bp[37]=BOB_X_SIZE;
  lives_bp[38]=BOB_Y_SIZE;
  lives_bp[39]=0xFFFF; // write mask, all pixels.
  lives_x_offset-=LIVES_X_OFFSET_SCOOT;

  regs.h.ah=0x08;       // BLT copy
  regs.h.al=1;          // BLT id
  regs.w.cx=4;          // # of blits to do
  regs.w.dx=0;          // Top/bottom, left/right normal blit
  regs.w.si=0;          // X origin
  regs.w.di=0;          // Y origin
  regs.w.es=FP_SEG(lives_bp); // pointer to blitter params
  regs.w.bx=FP_OFF(lives_bp); // ""      "" 
  intr(0xEF,&regs);
 
}

/**
 * Reset # of lives
 */
void lives_reset(void)
{
  num_lives=MAX_LIVES;
}
