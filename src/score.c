/**
 * Score routines
 */

#include <i86.h>
#include <string.h>
#include <stdlib.h>
#include "score.h"

static unsigned short score_tp[5];
static const char* header_hiscore_text="HI SCORE ";
static const char* header_1up_text="1UP ";
static const char* header_2up_text="2UP ";
static const char* header_xup_blank_text="    ";

static char score_1up_text[10];
static char score_2up_text[10];
static char score_hi_text[10];
static char score_temp[10];

unsigned long score_hi, score_1up, score_2up;

#define SCORE_HEADER_HISCORE_X_OFFSET   248
#define SCORE_HEADER_XUP_X_OFFSET       288
#define SCORE_DISPLAY_X_OFFSET          240

#define SCORE_HEADER_HISCORE_Y_OFFSET   0
#define SCORE_DISPLAY_HISCORE_Y_OFFSET  8
#define SCORE_HEADER_1UP_Y_OFFSET       24
#define SCORE_DISPLAY_1UP_Y_OFFSET      32
#define SCORE_HEADER_2UP_Y_OFFSET       48
#define SCORE_DISPLAY_2UP_Y_OFFSET      56

#define SCORE_LEN_DISPLAY               10
#define SCORE_LEN_HEADER_HISCORE        9
#define SCORE_LEN_HEADER_XUP            4

/**
 * Print score right justified to variable, with
 * 00 for 0 points.
 */
void score_set(long new_score, char* dest)
{
  int o; // Score offset.
  if (new_score==0)
    {
      strcpy(dest,"        00");
      return;
    }

  itoa(new_score,score_temp,10);

  o=10-strlen(score_temp);
  strncpy(&dest[o],score_temp,strlen(score_temp));
}

/**
 * Display High Score Header
 */
void score_header_hi(void)
{
  union REGPACK regs;

  score_tp[0]=SCORE_HEADER_HISCORE_X_OFFSET;
  score_tp[1]=SCORE_HEADER_HISCORE_Y_OFFSET;
  score_tp[2]=SCORE_LEN_HEADER_HISCORE;
  score_tp[3]=FP_OFF(header_hiscore_text);
  score_tp[4]=FP_SEG(header_hiscore_text);
  
  regs.h.ah=0x21;       // BLT STRING
  regs.h.al=32;          // BLT ID 1
  regs.h.ch=1;          // # of text pointer structs
  regs.h.cl=0;          // # of text chars to ignore at beginning of string (none)
  regs.h.dh=0;          // draw left to right
  regs.h.dl=0xFF;       // color
  regs.w.si=0;          // X origin
  regs.w.di=0;          // Y origin
  regs.w.es=FP_SEG(score_tp); // Text pointer (seg)
  regs.w.bx=FP_OFF(score_tp); // Text pointer (off)
  intr(0xEF,&regs);
}

/**
 * Display Hi-Score
 */
void score_display_hi(void)
{
  union REGPACK regs;

  score_tp[0]=SCORE_DISPLAY_X_OFFSET;
  score_tp[1]=SCORE_DISPLAY_HISCORE_Y_OFFSET;
  score_tp[2]=SCORE_LEN_DISPLAY;
  score_tp[3]=FP_OFF(score_hi_text);
  score_tp[4]=FP_SEG(score_hi_text);
  
  regs.h.ah=0x21;       // BLT STRING
  regs.h.al=32;          // BLT ID 1
  regs.h.ch=1;          // # of text pointer structs
  regs.h.cl=0;          // # of text chars to ignore at beginning of string (none)
  regs.h.dh=0;          // draw left to right
  regs.h.dl=0xFF;       // color
  regs.w.si=0;          // X origin
  regs.w.di=0;          // Y origin
  regs.w.es=FP_SEG(score_tp); // Text pointer (seg)
  regs.w.bx=FP_OFF(score_tp); // Text pointer (off)
  intr(0xEF,&regs);
}

/**
 * Display 1UP header
 */
void score_header_1up(bool blink)
{
  union REGPACK regs;

  score_tp[0]=SCORE_HEADER_XUP_X_OFFSET;
  score_tp[1]=SCORE_HEADER_1UP_Y_OFFSET;
  score_tp[2]=SCORE_LEN_HEADER_XUP;
  score_tp[3]=(blink==true ? FP_OFF(header_xup_blank_text) : FP_OFF(header_1up_text));
  score_tp[4]=(blink==true ? FP_SEG(header_xup_blank_text) : FP_SEG(header_1up_text));
  
  regs.h.ah=0x21;       // BLT STRING
  regs.h.al=32;          // BLT ID 1
  regs.h.ch=1;          // # of text pointer structs
  regs.h.cl=0;          // # of text chars to ignore at beginning of string (none)
  regs.h.dh=0;          // draw left to right
  regs.h.dl=0xFF;       // color
  regs.w.si=0;          // X origin
  regs.w.di=0;          // Y origin
  regs.w.es=FP_SEG(score_tp); // Text pointer (seg)
  regs.w.bx=FP_OFF(score_tp); // Text pointer (off)
  intr(0xEF,&regs);
}

/**
 * Display 1UP score
 */
void score_display_1up(void)
{
  union REGPACK regs;

  score_tp[0]=SCORE_DISPLAY_X_OFFSET;
  score_tp[1]=SCORE_DISPLAY_1UP_Y_OFFSET;
  score_tp[2]=SCORE_LEN_DISPLAY;
  score_tp[3]=FP_OFF(score_1up_text);
  score_tp[4]=FP_SEG(score_1up_text);

  regs.h.ah=0x21;       // BLT STRING
  regs.h.al=32;         // BLT ID 1
  regs.h.ch=1;          // # of text pointer structs
  regs.h.cl=0;          // # of text chars to ignore at beginning of string (none)
  regs.h.dh=0;          // draw left to right
  regs.h.dl=0xFF;       // color
  regs.w.si=0;          // X origin
  regs.w.di=0;          // Y origin
  regs.w.es=FP_SEG(score_tp); // Text pointer (seg)
  regs.w.bx=FP_OFF(score_tp); // Text pointer (off)
  intr(0xEF,&regs);
}

/**
 * Display 2UP header
 */
void score_header_2up(bool blink)
{
  union REGPACK regs;

  score_tp[0]=SCORE_HEADER_XUP_X_OFFSET;
  score_tp[1]=SCORE_HEADER_2UP_Y_OFFSET;
  score_tp[2]=SCORE_LEN_HEADER_XUP;
  score_tp[3]=(blink==true ? FP_OFF(header_xup_blank_text) : FP_OFF(header_2up_text));
  score_tp[4]=(blink==true ? FP_SEG(header_xup_blank_text) : FP_SEG(header_2up_text));

  regs.h.ah=0x21;       // BLT STRING
  regs.h.al=32;          // BLT ID 1
  regs.h.ch=1;          // # of text pointer structs
  regs.h.cl=0;          // # of text chars to ignore at beginning of string (none)
  regs.h.dh=0;          // draw left to right
  regs.h.dl=0xFF;       // color
  regs.w.si=0;          // X origin
  regs.w.di=0;          // Y origin
  regs.w.es=FP_SEG(score_tp); // Text pointer (seg)
  regs.w.bx=FP_OFF(score_tp); // Text pointer (off)
  intr(0xEF,&regs);
}

/**
 * Display 2UP score
 */
void score_display_2up(void)
{
  union REGPACK regs;

  score_tp[0]=SCORE_DISPLAY_X_OFFSET;
  score_tp[1]=SCORE_DISPLAY_2UP_Y_OFFSET;
  score_tp[2]=SCORE_LEN_DISPLAY;
  score_tp[3]=FP_OFF(score_2up_text);
  score_tp[4]=FP_SEG(score_2up_text);

  regs.h.ah=0x21;       // BLT STRING
  regs.h.al=32;          // BLT ID 1
  regs.h.ch=1;          // # of text pointer structs
  regs.h.cl=0;          // # of text chars to ignore at beginning of string (none)
  regs.h.dh=0;          // draw left to right
  regs.h.dl=0xFF;       // color
  regs.w.si=0;          // X origin
  regs.w.di=0;          // Y origin
  regs.w.es=FP_SEG(score_tp); // Text pointer (seg)
  regs.w.bx=FP_OFF(score_tp); // Text pointer (off)
  intr(0xEF,&regs);
}

/**
 * Score Reset
 */
void score_reset(void)
{
  score_hi=score_1up=score_2up=0;
  score_set(score_hi,&score_hi_text);
  score_set(score_1up,&score_1up_text);
  score_set(score_2up,&score_2up_text);
}
