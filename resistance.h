#ifndef __RESISTANCE_H__
#define __RESISTANCE_H__

/* Returns the total resistance of either serial or parallel connected resistors.
 * count: The number of resistors (must be at least 1).
 * conn: 'S' (serial) or 'P' (parallel)
 * array: Pointer to an array of resistor values.
 *
 * Returns -1 in case of errors due to invalid parameters given.
 */
float calc_resistance(int count, char conn, float *array);

#endif /* __RESISTANCE_H__ */
