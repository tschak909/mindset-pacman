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
#include "bobs.h"
#include "vblank.h"

extern bool bQuit;

#define CHARACTER_X 48
#define NICKNAME_X  136
#define PTS_X       CHARACTER_X+24;
#define GHOST_Y     28

// Originally 32 16 and 8
#define PAUSE_LONG   64
#define PAUSE_MEDIUM 32
#define PAUSE_SHORT  16

// Initial position for PAC-MAN
#define PACMAN_X_INITIAL 272

#define ATTRACT_Y 120

const char* char_text="CHARACTER : NICKNAME";
const char* shad_text=";SHADOW";
const char* blin_text="&BLINKY&";
const char* spee_text=";SPEEDY";
const char* pink_text="&PINKY&";
const char* bash_text=";BASHFUL";
const char* inky_text="&INKY&";
const char* poke_text=";POKEY";
const char* clyd_text="&CLYDE&";
const char* tenp_text="\x10 10 \x5d\x5e\x5f";   // . 10 pts
const char* fift_text="\x14 50 \x5d\x5e\x5f";   // O 50 pts
const char* copy_text="\x5c 1980 MIDWAY MFG$ CO$";
const char* attract_dot_0=" ";
const char* attract_dot_1="\x14";
const char* attract_little_dot="\x10";

static unsigned short tp[5];  // Text params
static unsigned short tpd[10]; // Text params for Two big dots.
static unsigned short bp[10]; // blt params
static unsigned short bpa[100]; // animation blt params for 10 objects

extern unsigned short frame_cnt;
extern bool frame_done;

/**
 * Blit a bob for attract mode
 */
void attract_blt_bob(short x, short y, const unsigned char* data)
{
  union REGPACK regs;
  bp[0]=FP_OFF(data);
  bp[1]=FP_SEG(data);
  bp[2]=8;
  bp[3]=0;
  bp[4]=0;
  bp[5]=x;
  bp[6]=y;
  bp[7]=16;
  bp[8]=16;
  bp[9]=0xFFFF;

  regs.h.ah=0x08;       // BLT copy
  regs.h.al=1;          // BLT id
  regs.w.cx=1;          // # of blits to do
  regs.w.dx=0;          // Top/bottom, left/right normal blit
  regs.w.si=0;          // X origin
  regs.w.di=0;          // Y origin
  regs.w.es=FP_SEG(bp); // pointer to blitter params
  regs.w.bx=FP_OFF(bp); // ""      "" 
  intr(0xEF,&regs);
}

/**
 * Run attract
 * a note about this routine, yes, everything is inline.
 * it's literally because of the alignment sensitivity of the ROM BIOS routines.
 * The text routines simply would refuse to work if I moved the text calls to a function -Thom
 */
void attract(void)
{
  union REGPACK regs;
  unsigned short pacman_lx, blinky_lx, pinky_lx, inky_lx, clyde_lx;
  unsigned short pacman_x, blinky_x, pinky_x, inky_x, clyde_x;
  unsigned short pacman_frame_cnt, blinky_frame_cnt, pinky_frame_cnt, inky_frame_cnt, clyde_frame_cnt;
  unsigned short dot_frame_cnt;
  
  // Set initial sprite positions
  pacman_x=pacman_lx=PACMAN_X_INITIAL;
  blinky_x=blinky_lx=pacman_x+32;
  pinky_x=pinky_lx=blinky_x+16;
  inky_x=pinky_lx=pinky_x+16;
  clyde_x=clyde_lx=inky_x+16;

  // Set clipping rectangle to 256x200
  mindset_gfx_set_clip_rectangle(0,256,0,199);
  
  // Set up text string call
  regs.h.ah=0x21;       // BLT STRING
  regs.h.al=1;          // BLT ID 1
  regs.h.ch=1;          // # of text pointer structs
  regs.h.cl=0;          // # of text chars to ignore at beginning of string (none)
  regs.h.dh=0;          // draw left to right
  regs.h.dl=0x33;       // color
  regs.w.si=0;          // X origin
  regs.w.di=0;          // Y origin
  regs.w.es=FP_SEG(tp); // Text pointer (seg)
  regs.w.bx=FP_OFF(tp); // Text pointer (off)
  intr(0xEF,&regs);

  // CHARACTER / NICKNAME
  
  tp[0]=CHARACTER_X;
  tp[1]=16;
  tp[2]=20;
  tp[3]=FP_OFF(char_text);
  tp[4]=FP_SEG(char_text);
  intr(0xEF,&regs);

  // SHADOW / PINKY
  attract_blt_bob(CHARACTER_X-24,GHOST_Y,&blinky_1_right);
  vblank_pause(PAUSE_LONG);
  
  tp[0]=CHARACTER_X;
  tp[1]=32;
  tp[2]=7;
  tp[3]=FP_OFF(shad_text);
  tp[4]=FP_SEG(shad_text);
  regs.h.dl=0x22;
  intr(0xEF,&regs);
  vblank_pause(PAUSE_MEDIUM);
  
  tp[0]=NICKNAME_X;
  tp[1]=32;
  tp[2]=8;
  tp[3]=FP_OFF(blin_text);
  tp[4]=FP_SEG(blin_text);
  intr(0xEF,&regs);
  vblank_pause(PAUSE_SHORT);

  // SPEEDY / PINKY
  attract_blt_bob(CHARACTER_X-24,GHOST_Y+24,&pinky_1_right);
  vblank_pause(PAUSE_LONG);
  
  tp[0]=CHARACTER_X;
  tp[1]+=24;
  tp[2]=7;
  tp[3]=FP_OFF(spee_text);
  tp[4]=FP_SEG(spee_text);
  regs.h.dl=0x55;
  intr(0xEF,&regs);
  vblank_pause(PAUSE_MEDIUM);
  
  tp[0]=NICKNAME_X;
  tp[3]=FP_OFF(pink_text);
  tp[4]=FP_SEG(pink_text);
  intr(0xEF,&regs);
  vblank_pause(PAUSE_SHORT);

  // BASHFUL / INKY
  attract_blt_bob(CHARACTER_X-24,GHOST_Y+48,&inky_1_right);
  vblank_pause(PAUSE_LONG);
  
  regs.h.dl=0x66;
  tp[0]=CHARACTER_X;
  tp[1]+=24;
  tp[2]=8;
  tp[3]=FP_OFF(bash_text);
  tp[4]=FP_SEG(bash_text);
  intr(0xEF,&regs);
  vblank_pause(PAUSE_MEDIUM);

  tp[0]=NICKNAME_X;
  tp[2]=6;
  tp[3]=FP_OFF(inky_text);
  tp[4]=FP_SEG(inky_text);
  intr(0xEF,&regs);
  vblank_pause(PAUSE_SHORT);

  // POKEY / CLYDE
  attract_blt_bob(CHARACTER_X-24,GHOST_Y+72,&clyde_1_right);
  vblank_pause(PAUSE_LONG);
  
  regs.h.dl=0x77;
  tp[0]=CHARACTER_X;
  tp[1]+=24;
  tp[2]=6;
  tp[3]=FP_OFF(poke_text);
  tp[4]=FP_SEG(poke_text);
  intr(0xEF,&regs);
  vblank_pause(PAUSE_MEDIUM);

  tp[0]=NICKNAME_X;
  tp[2]=7;
  tp[3]=FP_OFF(clyd_text);
  tp[4]=FP_SEG(clyd_text);
  intr(0xEF,&regs);
  vblank_pause(PAUSE_SHORT);

  // 10/50 PTS 
  vblank_pause(PAUSE_LONG);
  regs.h.dl=0x33;
  tp[0]=PTS_X;
  tp[1]+=40;
  tp[2]=8;
  tp[3]=FP_OFF(tenp_text);
  tp[4]=FP_SEG(tenp_text);
  intr(0xEF,&regs);

  tp[1]+=16;
  tp[3]=FP_OFF(fift_text);
  tp[4]=FP_SEG(fift_text);
  intr(0xEF,&regs);

  // Fix the little dot
  tp[1]-=16;
  tp[2]=1;
  tp[3]=FP_OFF(attract_little_dot);
  tp[4]=FP_SEG(attract_little_dot);
  regs.h.dl=0xAA;
  intr(0xEF,&regs);
  
  // (c) 1980 MIDWAY MFG. CO.
  vblank_pause(PAUSE_MEDIUM);
  regs.h.dl=0x55;
  tp[0]=24;
  tp[1]=192;
  tp[2]=22;
  tp[3]=FP_OFF(copy_text);
  tp[4]=FP_SEG(copy_text);
  intr(0xEF,&regs);

  // Now do Pacman + ghosts moving left
  while (pacman_x>16)
    {
      frame_done=false;

      pacman_lx=pacman_x;
      blinky_lx=blinky_x;
      pinky_lx=pinky_x;
      inky_lx=inky_x;
      clyde_lx=clyde_x;
      
      // Scoot pacman and blinky every other frame
      // Also adjust pac-man's frame every other frame
      if ((frame_cnt&1)==0)
	{
	  // Mouth pac-man
	  if (pacman_frame_cnt>3)
	    pacman_frame_cnt=0;
	  else
	    pacman_frame_cnt++;
	  
	  // Scoot pac-man and Ghosts
	  pacman_x-=2;
	  blinky_x-=2;
	  pinky_x-=2;
	  inky_x-=2;
	  clyde_x-=2;
	}
      
      // Adjust blinky animation frame every 4 frames
      if ((frame_cnt&3)==0)
	{
	  blinky_frame_cnt=((blinky_frame_cnt==0) ? 1 : 0);
	  pinky_frame_cnt=((pinky_frame_cnt==0) ? 1 : 0);
	  inky_frame_cnt=((inky_frame_cnt==0) ? 1 : 0);
	  clyde_frame_cnt=((clyde_frame_cnt==0) ? 1 : 0);
	}

      // Make pac-man creep up a bit more...
      if ((frame_cnt&7)==0)
      	{
      	  dot_frame_cnt=((dot_frame_cnt==0) ? 1 : 0);
      	}

      // Scoot ghosts a bit more.
      if ((frame_cnt&0x0f)==0)
	{
      	  blinky_x--;
	  pinky_x--;
	  inky_x--;
	  clyde_x--;
	}

      // Plot the big dots /////////////////////////////////////////////
      
      tpd[0]=PTS_X;
      tpd[1]=160;
      tpd[2]=1;
      tpd[3]=FP_OFF((dot_frame_cnt==0) ? attract_dot_0 : attract_dot_1);
      tpd[4]=FP_SEG((dot_frame_cnt==0) ? attract_dot_0 : attract_dot_1);
      tpd[5]=16;
      tpd[6]=ATTRACT_Y+4;
      tpd[7]=1;
      tpd[8]=FP_OFF((dot_frame_cnt==0) ? attract_dot_0 : attract_dot_1);
      tpd[9]=FP_SEG((dot_frame_cnt==0) ? attract_dot_0 : attract_dot_1);
      
      // Set up text string call
      regs.h.ah=0x21;       // BLT STRING
      regs.h.al=2;          // BLT ID 1
      regs.h.ch=2;          // # of text pointer structs
      regs.h.cl=0;          // # of text chars to ignore at beginning of string (none)
      regs.h.dh=0;          // draw left to right
      regs.h.dl=0xAA;       // color
      regs.w.si=0;          // X origin
      regs.w.di=0;          // Y origin
      regs.w.es=FP_SEG(tpd); // Text pointer (seg)
      regs.w.bx=FP_OFF(tpd); // Text pointer (off)
      intr(0xEF,&regs);
    
      // Set up BLT transaction ////////////////////////////////////

      // PAC-MAN BLANK
      bpa[ 0]=FP_OFF(blank);
      bpa[ 1]=FP_SEG(blank);
      bpa[ 2]=8;
      bpa[ 3]=0;
      bpa[ 4]=0;
      bpa[ 5]=pacman_lx;
      bpa[ 6]=ATTRACT_Y;
      bpa[ 7]=16;
      bpa[ 8]=16;
      bpa[ 9]=0xFFFF;

      // BLINKY BLANK
      bpa[10]=FP_OFF(blank);
      bpa[11]=FP_SEG(blank);
      bpa[12]=8;
      bpa[13]=0;
      bpa[14]=0;
      bpa[15]=blinky_lx;
      bpa[16]=ATTRACT_Y;
      bpa[17]=16;
      bpa[18]=16;
      bpa[19]=0xFFFF;

      // PINKY BLANK
      bpa[20]=FP_OFF(blank);
      bpa[21]=FP_SEG(blank);
      bpa[22]=8;
      bpa[23]=0;
      bpa[24]=0;
      bpa[25]=pinky_lx;
      bpa[26]=ATTRACT_Y;
      bpa[27]=16;
      bpa[28]=16;
      bpa[29]=0xFFFF;

      // INKY BLANK
      bpa[30]=FP_OFF(blank);
      bpa[31]=FP_SEG(blank);
      bpa[32]=8;
      bpa[33]=0;
      bpa[34]=0;
      bpa[35]=inky_lx;
      bpa[36]=ATTRACT_Y;
      bpa[37]=16;
      bpa[38]=16;
      bpa[39]=0xFFFF;

      // CLYDE BLANK
      bpa[40]=FP_OFF(blank);
      bpa[41]=FP_SEG(blank);
      bpa[42]=8;
      bpa[43]=0;
      bpa[44]=0;
      bpa[45]=clyde_lx;
      bpa[46]=ATTRACT_Y;
      bpa[47]=16;
      bpa[48]=16;
      bpa[49]=0xFFFF;

      // PACMAN
      bpa[50]=FP_OFF(pacman_left_frames[pacman_frame_cnt]);
      bpa[51]=FP_SEG(pacman_left_frames[pacman_frame_cnt]);
      bpa[52]=8;
      bpa[53]=0;
      bpa[54]=0;
      bpa[55]=pacman_x;
      bpa[56]=ATTRACT_Y;
      bpa[57]=16;
      bpa[58]=16;
      bpa[59]=0xFFFF;

      // BLINKY
      bpa[60]=FP_OFF(blinky_left_frames[blinky_frame_cnt]);
      bpa[61]=FP_SEG(blinky_left_frames[blinky_frame_cnt]);
      bpa[62]=8;
      bpa[63]=0;
      bpa[64]=0;
      bpa[65]=blinky_x;
      bpa[66]=ATTRACT_Y;
      bpa[67]=16;
      bpa[68]=16;
      bpa[69]=0xFFFF;

      // PINKY
      bpa[70]=FP_OFF(pinky_left_frames[pinky_frame_cnt]);
      bpa[71]=FP_SEG(pinky_left_frames[pinky_frame_cnt]);
      bpa[72]=8;
      bpa[73]=0;
      bpa[74]=0;
      bpa[75]=pinky_x;
      bpa[76]=ATTRACT_Y;
      bpa[77]=16;
      bpa[78]=16;
      bpa[79]=0xFFFF;

      // INKY
      bpa[80]=FP_OFF(inky_left_frames[inky_frame_cnt]);
      bpa[81]=FP_SEG(inky_left_frames[inky_frame_cnt]);
      bpa[82]=8;
      bpa[83]=0;
      bpa[84]=0;
      bpa[85]=inky_x;
      bpa[86]=ATTRACT_Y;
      bpa[87]=16;
      bpa[88]=16;
      bpa[89]=0xFFFF;

      // CLYDE
      bpa[90]=FP_OFF(clyde_left_frames[clyde_frame_cnt]);
      bpa[91]=FP_SEG(clyde_left_frames[clyde_frame_cnt]);
      bpa[92]=8;
      bpa[93]=0;
      bpa[94]=0;
      bpa[95]=clyde_x;
      bpa[96]=ATTRACT_Y;
      bpa[97]=16;
      bpa[98]=16;
      bpa[99]=0xFFFF;

      // Set up the BLT COPY
      regs.h.ah=0x08;       // BLT copy
      regs.h.al=1;          // BLT id
      regs.w.cx=10;         // # of blits to do
      regs.w.dx=0;          // Top/bottom, left/right normal blit
      regs.w.si=0;          // X origin
      regs.w.di=0;          // Y origin
      regs.w.es=FP_SEG(bpa); // pointer to blitter params
      regs.w.bx=FP_OFF(bpa); // ""      "" 
      intr(0xEF,&regs);

      vblank_wait();
    }

  // And now pac-man in beast mode
  while (pacman_x<272)
    {
      frame_done=false;

      pacman_lx=pacman_x;
      blinky_lx=blinky_x;
      pinky_lx=pinky_x;
      inky_lx=inky_x;
      clyde_lx=clyde_x;
      
      // Scoot pacman and blinky every other frame
      // Also adjust pac-man's frame every other frame
      if ((frame_cnt&1)==0)
	{
	  // Mouth pac-man
	  if (pacman_frame_cnt>3)
	    pacman_frame_cnt=0;
	  else
	    pacman_frame_cnt++;
	  
	  // Scoot pac-man and Ghosts
	  pacman_x+=2;
	  blinky_x+=2;
	  pinky_x+=2;
	  inky_x+=2;
	  clyde_x+=2;
	}
      
      // Adjust blinky animation frame every 4 frames
      if ((frame_cnt&3)==0)
	{
	  blinky_frame_cnt=((blinky_frame_cnt==0) ? 1 : 0);
	  pinky_frame_cnt=((pinky_frame_cnt==0) ? 1 : 0);
	  inky_frame_cnt=((inky_frame_cnt==0) ? 1 : 0);
	  clyde_frame_cnt=((clyde_frame_cnt==0) ? 1 : 0);
	}

      // Make pac-man creep up a bit more...
      if ((frame_cnt&7)==0)
	{
	  dot_frame_cnt=((dot_frame_cnt==0) ? 1 : 0);	  
	  blinky_x--;
	  pinky_x--;
	  inky_x--;
	  clyde_x--;
	  pacman_x++;
	}

      // Plot the big dots /////////////////////////////////////////////
      
      tpd[0]=PTS_X;
      tpd[1]=160;
      tpd[2]=1;
      tpd[3]=FP_OFF((dot_frame_cnt==0) ? attract_dot_0 : attract_dot_1);
      tpd[4]=FP_SEG((dot_frame_cnt==0) ? attract_dot_0 : attract_dot_1);
      tpd[5]=16;
      tpd[6]=ATTRACT_Y+4;
      tpd[7]=1;
      tpd[8]=FP_OFF((dot_frame_cnt==0) ? attract_dot_0 : attract_dot_1);
      tpd[9]=FP_SEG((dot_frame_cnt==0) ? attract_dot_0 : attract_dot_1);
      
      // Set up text string call
      regs.h.ah=0x21;       // BLT STRING
      regs.h.al=2;          // BLT ID 1
      regs.h.ch=2;          // # of text pointer structs
      regs.h.cl=0;          // # of text chars to ignore at beginning of string (none)
      regs.h.dh=0;          // draw left to right
      regs.h.dl=0xAA;       // color
      regs.w.si=0;          // X origin
      regs.w.di=0;          // Y origin
      regs.w.es=FP_SEG(tpd); // Text pointer (seg)
      regs.w.bx=FP_OFF(tpd); // Text pointer (off)
      intr(0xEF,&regs);
    
      // Set up BLT transaction ////////////////////////////////////

      // PAC-MAN BLANK
      bpa[ 0]=FP_OFF(blank);
      bpa[ 1]=FP_SEG(blank);
      bpa[ 2]=8;
      bpa[ 3]=0;
      bpa[ 4]=0;
      bpa[ 5]=pacman_lx;
      bpa[ 6]=ATTRACT_Y;
      bpa[ 7]=16;
      bpa[ 8]=16;
      bpa[ 9]=0xFFFF;

      // BLINKY BLANK
      bpa[10]=FP_OFF(blank);
      bpa[11]=FP_SEG(blank);
      bpa[12]=8;
      bpa[13]=0;
      bpa[14]=0;
      bpa[15]=blinky_lx;
      bpa[16]=ATTRACT_Y;
      bpa[17]=16;
      bpa[18]=16;
      bpa[19]=0xFFFF;

      // PINKY BLANK
      bpa[20]=FP_OFF(blank);
      bpa[21]=FP_SEG(blank);
      bpa[22]=8;
      bpa[23]=0;
      bpa[24]=0;
      bpa[25]=pinky_lx;
      bpa[26]=ATTRACT_Y;
      bpa[27]=16;
      bpa[28]=16;
      bpa[29]=0xFFFF;

      // INKY BLANK
      bpa[30]=FP_OFF(blank);
      bpa[31]=FP_SEG(blank);
      bpa[32]=8;
      bpa[33]=0;
      bpa[34]=0;
      bpa[35]=inky_lx;
      bpa[36]=ATTRACT_Y;
      bpa[37]=16;
      bpa[38]=16;
      bpa[39]=0xFFFF;

      // CLYDE BLANK
      bpa[40]=FP_OFF(blank);
      bpa[41]=FP_SEG(blank);
      bpa[42]=8;
      bpa[43]=0;
      bpa[44]=0;
      bpa[45]=clyde_lx;
      bpa[46]=ATTRACT_Y;
      bpa[47]=16;
      bpa[48]=16;
      bpa[49]=0xFFFF;

      // PACMAN
      bpa[50]=FP_OFF(pacman_right_frames[pacman_frame_cnt]);
      bpa[51]=FP_SEG(pacman_right_frames[pacman_frame_cnt]);
      bpa[52]=8;
      bpa[53]=0;
      bpa[54]=0;
      bpa[55]=pacman_x;
      bpa[56]=ATTRACT_Y;
      bpa[57]=16;
      bpa[58]=16;
      bpa[59]=0xFFFF;

      // BLINKY
      bpa[60]=FP_OFF(blinkyblue_frames[blinky_frame_cnt]);
      bpa[61]=FP_SEG(blinkyblue_frames[blinky_frame_cnt]);
      bpa[62]=8;
      bpa[63]=0;
      bpa[64]=0;
      bpa[65]=blinky_x;
      bpa[66]=ATTRACT_Y;
      bpa[67]=16;
      bpa[68]=16;
      bpa[69]=0xFFFF;

      // PINKY
      bpa[70]=FP_OFF(blinkyblue_frames[pinky_frame_cnt]);
      bpa[71]=FP_SEG(blinkyblue_frames[pinky_frame_cnt]);
      bpa[72]=8;
      bpa[73]=0;
      bpa[74]=0;
      bpa[75]=pinky_x;
      bpa[76]=ATTRACT_Y;
      bpa[77]=16;
      bpa[78]=16;
      bpa[79]=0xFFFF;

      // INKY
      bpa[80]=FP_OFF(blinkyblue_frames[inky_frame_cnt]);
      bpa[81]=FP_SEG(blinkyblue_frames[inky_frame_cnt]);
      bpa[82]=8;
      bpa[83]=0;
      bpa[84]=0;
      bpa[85]=inky_x;
      bpa[86]=ATTRACT_Y;
      bpa[87]=16;
      bpa[88]=16;
      bpa[89]=0xFFFF;

      // CLYDE
      bpa[90]=FP_OFF(blinkyblue_frames[clyde_frame_cnt]);
      bpa[91]=FP_SEG(blinkyblue_frames[clyde_frame_cnt]);
      bpa[92]=8;
      bpa[93]=0;
      bpa[94]=0;
      bpa[95]=clyde_x;
      bpa[96]=ATTRACT_Y;
      bpa[97]=16;
      bpa[98]=16;
      bpa[99]=0xFFFF;

      // Set up the BLT COPY
      regs.h.ah=0x08;       // BLT copy
      regs.h.al=1;          // BLT id
      regs.w.cx=10;         // # of blits to do
      regs.w.dx=0;          // Top/bottom, left/right normal blit
      regs.w.si=0;          // X origin
      regs.w.di=0;          // Y origin
      regs.w.es=FP_SEG(bpa); // pointer to blitter params
      regs.w.bx=FP_OFF(bpa); // ""      "" 
      intr(0xEF,&regs);      
      
      vblank_wait();
    }
  
  bQuit=true;
}
