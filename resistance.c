#include "resistance.h"

float calc_resistance(int count, char conn, float *array)
{
  float resistance = 0;
  int i = 0;
  for (i = 0; i < count; ++i)
    {
      resistance += array[i];
    }
  return resistance;
}
