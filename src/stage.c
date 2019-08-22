/**
 * Stage display
 */

#include <i86.h>

unsigned short stage_bp[50];

const unsigned char* stage_map[5];

#define STAGE_OFFSET_X_START 304
#define STAGE_OFFSET_X_SCOOT 16
#define STAGE_Y_OFFSET 128
#define BOB_X_SIZE 16
#define BOB_Y_SIZE 16

extern const unsigned char blank[];
extern const unsigned char cherry[];
extern const unsigned char strawberry[];
extern const unsigned char orange[];
extern const unsigned char bell[];
extern const unsigned char apple[];
extern const unsigned char melon[];
extern const unsigned char galaxian[];
extern const unsigned char key[];

/**
 * Display Current Stage
 */
void stage_display(unsigned char stage)
{
  unsigned short stage_x_offset=STAGE_OFFSET_X_START;
  union REGPACK regs;
  
  switch (stage)
    {
    case 0:
      stage_map[0]=cherry;
      stage_map[1]=&blank;
      stage_map[2]=&blank;
      stage_map[3]=&blank;
      stage_map[4]=&blank;
      break;
    case 1:
      stage_map[0]=&cherry;
      stage_map[1]=&strawberry;
      stage_map[2]=&blank;
      stage_map[3]=&blank;
      stage_map[4]=&blank;
      break;
    case 2:
      stage_map[0]=&cherry;
      stage_map[1]=&strawberry;
      stage_map[2]=&orange;
      stage_map[3]=&blank;
      stage_map[4]=&blank;
      break;
    case 3:
      stage_map[0]=&cherry;
      stage_map[1]=&strawberry;
      stage_map[2]=&orange;
      stage_map[3]=&orange;
      stage_map[4]=&blank;
      break;
    case 4:
      stage_map[0]=&cherry;
      stage_map[1]=&strawberry;
      stage_map[2]=&orange;
      stage_map[3]=&orange;
      stage_map[4]=&apple;
      break;
    case 5:
      stage_map[0]=&strawberry;
      stage_map[1]=&orange;
      stage_map[2]=&orange;
      stage_map[3]=&apple;
      stage_map[4]=&apple;
      break;
    case 6:
      stage_map[0]=&orange;
      stage_map[1]=&orange;
      stage_map[2]=&apple;
      stage_map[3]=&apple;
      stage_map[4]=&melon;
      break;      
    case 7:
      stage_map[0]=&orange;
      stage_map[1]=&apple;
      stage_map[2]=&apple;
      stage_map[3]=&melon;
      stage_map[4]=&melon;
      break;
    case 8:
      stage_map[0]=&apple;
      stage_map[1]=&apple;
      stage_map[2]=&melon;
      stage_map[3]=&melon;
      stage_map[4]=&galaxian;
      break;
    case 9:
      stage_map[0]=&apple;
      stage_map[1]=&melon;
      stage_map[2]=&melon;
      stage_map[3]=&galaxian;
      stage_map[4]=&galaxian;
      break;
    case 10:
      stage_map[0]=&melon;
      stage_map[1]=&melon;
      stage_map[2]=&galaxian;
      stage_map[3]=&galaxian;
      stage_map[4]=&bell;
      break;
    case 11:
      stage_map[0]=&melon;
      stage_map[1]=&galaxian;
      stage_map[2]=&galaxian;
      stage_map[3]=&bell;
      stage_map[4]=&bell;
      break;
    case 12:
      stage_map[0]=&galaxian;
      stage_map[1]=&galaxian;
      stage_map[2]=&bell;
      stage_map[3]=&bell;
      stage_map[4]=&key;
      break;
    case 13:
      stage_map[0]=&galaxian;
      stage_map[1]=&bell;
      stage_map[2]=&bell;
      stage_map[3]=&key;
      stage_map[4]=&key;
      break;
    case 14:
      stage_map[0]=&bell;
      stage_map[1]=&bell;
      stage_map[2]=&key;
      stage_map[3]=&key;
      stage_map[4]=&key;
      break;      
    case 15:
      stage_map[0]=&bell;
      stage_map[1]=&key;
      stage_map[2]=&key;
      stage_map[3]=&key;
      stage_map[4]=&key;
      break;      
    default:
      stage_map[0]=&key;
      stage_map[1]=&key;
      stage_map[2]=&key;
      stage_map[3]=&key;
      stage_map[4]=&key;
      break;
    }

  stage_bp[ 0]=FP_OFF(stage_map[0]);
  stage_bp[ 1]=FP_SEG(stage_map[0]);
  stage_bp[ 2]=8; // Stride size
  stage_bp[ 3]=0;
  stage_bp[ 4]=0;
  stage_bp[ 5]=stage_x_offset;
  stage_bp[ 6]=STAGE_Y_OFFSET;
  stage_bp[ 7]=BOB_X_SIZE;
  stage_bp[ 8]=BOB_Y_SIZE;
  stage_bp[ 9]=0xFFFF; // Write mask
  stage_x_offset-=STAGE_OFFSET_X_SCOOT;

  stage_bp[10]=FP_OFF(stage_map[1]);
  stage_bp[11]=FP_SEG(stage_map[1]);
  stage_bp[12]=8; // Stride size
  stage_bp[13]=0;
  stage_bp[14]=0;
  stage_bp[15]=stage_x_offset;
  stage_bp[16]=STAGE_Y_OFFSET;
  stage_bp[17]=BOB_X_SIZE;
  stage_bp[18]=BOB_Y_SIZE;
  stage_bp[19]=0xFFFF; // Write mask
  stage_x_offset-=STAGE_OFFSET_X_SCOOT;

  stage_bp[20]=FP_OFF(stage_map[2]);
  stage_bp[21]=FP_SEG(stage_map[2]);
  stage_bp[22]=8; // Stride size
  stage_bp[23]=0;
  stage_bp[24]=0;
  stage_bp[25]=stage_x_offset;
  stage_bp[26]=STAGE_Y_OFFSET;
  stage_bp[27]=BOB_X_SIZE;
  stage_bp[28]=BOB_Y_SIZE;
  stage_bp[29]=0xFFFF; // Write mask
  stage_x_offset-=STAGE_OFFSET_X_SCOOT;

  stage_bp[30]=FP_OFF(stage_map[3]);
  stage_bp[31]=FP_SEG(stage_map[3]);
  stage_bp[32]=8; // Stride size
  stage_bp[33]=0;
  stage_bp[34]=0;
  stage_bp[35]=stage_x_offset;
  stage_bp[36]=STAGE_Y_OFFSET;
  stage_bp[37]=BOB_X_SIZE;
  stage_bp[38]=BOB_Y_SIZE;
  stage_bp[39]=0xFFFF; // Write mask
  stage_x_offset-=STAGE_OFFSET_X_SCOOT;

  stage_bp[40]=FP_OFF(stage_map[4]);
  stage_bp[41]=FP_SEG(stage_map[4]);
  stage_bp[42]=8; // Stride size
  stage_bp[43]=0;
  stage_bp[44]=0;
  stage_bp[45]=stage_x_offset;
  stage_bp[46]=STAGE_Y_OFFSET;
  stage_bp[47]=BOB_X_SIZE;
  stage_bp[48]=BOB_Y_SIZE;
  stage_bp[49]=0xFFFF; // Write mask

  regs.h.ah=0x08;       // BLT copy
  regs.h.al=1;          // BLT id
  regs.w.cx=5;          // # of blits to do
  regs.w.dx=0;          // Top/bottom, left/right normal blit
  regs.w.si=0;          // X origin
  regs.w.di=0;          // Y origin
  regs.w.es=FP_SEG(stage_bp); // pointer to blitter params
  regs.w.bx=FP_OFF(stage_bp); // ""      "" 
  intr(0xEF,&regs);
}
