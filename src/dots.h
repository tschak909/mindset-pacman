/**
 * Dot handling
 */

#ifndef DOTS_H
#define DOTS_H

#include <stdbool.h>

#define PIXEL_TO_DOT_X(x) (x/6)
#define PIXEL_TO_DOT_Y(y) (y/6)

/**
 * Reset dotmap (for e.g. new stage)
 */
void dots_new(unsigned char* dest);

/**
 * New game, initialize dotmap for player 1 and 2.
 */
void dots_new_game(void);

/**
 * Update a single dot position
 */
void dot_plot(unsigned char p, unsigned short d);

/**
 * plot all dots for given player
 */
void dots_plot(unsigned char p);

/**
 * Check for wall
 */
bool dot_check_wall(unsigned char p, unsigned char tx, unsigned char ty);

#endif /* DOTS_H*/
