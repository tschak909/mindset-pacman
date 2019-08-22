/**
 * Mindset PAC-MAN
 *
 * Main Game Code
 */

#include <i86.h>
#include "libmindset_gfx.h"
#include "game.h"
#include "score.h"
#include "stage.h"
#include "dots.h"
#include "lives.h"
#include "maze.h"

unsigned char current_player;

extern unsigned long score_hi, score_1up, score_2up;   // scores

/**
 * New game, reset everything
 */
void game_new(void)
{
  lives_reset();
  score_new_game();
  stage_cherry();
  dots_new_game();
  stage_display(current_player);
  lives_display(current_player);
  maze_draw();
}

/**
 * Run game
 */
void game_run(void)
{
  game_new();
}
