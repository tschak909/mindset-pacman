/**
 * Mindset PAC-MAN
 *
 * Main Game Code
 */

#ifndef GAME_H
#define GAME_H

/**
 * New game, reset everything
 */
void game_new(void);

/**
 * Run game
 */
void game_run(void);

/**
 * Display READY!
 */
void game_display_ready(bool display);

/**
 * Plot blitter objects
 */
void game_plot(void);

#endif /* GAME_H */
