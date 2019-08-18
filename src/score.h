/**
 * Score Routines
 */

#ifndef SCORE_H
#define SCORE_H

#include <stdbool.h>

/**
 * Print score right justified to variable, with
 * 00 for 0 points.
 */
void score_set(long new_score, char* dest);

/**
 * Display High Score Header
 */
void score_header_hi(void);

/**
 * Display Hi-Score
 */
void score_display_hi(void);

/**
 * Display 1UP header
 */
void score_header_1up(bool blink);

/**
 * Display 1UP score
 */
void score_display_1up(void);

/**
 * Display 2UP header
 */
void score_header_2up(bool blink);

/**
 * Display 2UP score
 */
void score_display_2up(void);

/**
 * Score Reset
 */
void score_reset(void);

#endif /* SCORE_H */
