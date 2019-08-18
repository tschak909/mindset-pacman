/**
 * Score Routines
 */

#ifndef SCORE_H
#define SCORE_H

#include <stdbool.h>

/**
 * Display High Score Header
 */
void score_header_hi(void);

/**
 * Display 1UP header
 */
void score_header_1up(bool blink);

/**
 * Display 1UP score
 */
void score_display_1up(bool blink);

/**
 * Display 2UP header
 */
void score_header_1up(bool blink);

/**
 * Display 2UP score
 */
void score_display_1up(bool blink);

/**
 * Score Reset
 */
void score_reset(void);

#endif /* SCORE_H */
