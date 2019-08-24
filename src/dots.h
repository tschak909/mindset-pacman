/**
 * Dot handling
 */

#ifndef DOTS_H
#define DOTS_H

#define PIXEL_TO_DOT(x,y) ((y+2)/6)+((x+4)/6)

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

#endif /* DOTS_H*/
