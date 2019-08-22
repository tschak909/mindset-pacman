/**
 * Dot handling
 */

#ifndef DOTS_H
#define DOTS_H

/**
 * Reset dotmap (for e.g. new stage)
 */
void dots_new(unsigned char* dest);

/**
 * New game, initialize dotmap for player 1 and 2.
 */
void dots_new_game(void);

/**
 * plot all dots for given player
 */
void dots_plot(unsigned char p);

#endif /* DOTS_H*/
