/**
 * Mindset PAC-MAN
 *
 * Main Game Code
 */

#ifndef GAME_H
#define GAME_H

typedef enum _direction
  {
    RIGHT,
    DOWN,
    LEFT,
    UP,
  } Direction;


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

/**
 * Display READY!
 */
void game_display_game_over(bool display);

/**
 * Game frame loop
 */
void game_loop(void);

/**
 * Move objects according to their dx/dy
 */
void game_move_objects(void);

/**
 * Check for maze collision
 * Returns dx and dy values
 */
void game_check_maze_collision(unsigned short x, unsigned short y, Direction d, unsigned char* dx, unsigned char* dy);

/**
 * Check pac-man's collisions
 */
void game_check_collisions_pacman(void);

/**
 * Check for collisions (software)
 */
void game_check_collisions(void);

#endif /* GAME_H */
