#include <stdlib.h>
#include "resistance.h"

float calc_resistance(int count, char conn, float *array)
{
  const int ERROR_CODE = -1;
  float resistance = 0;
  int i = 0;

  if (count <= 0)
    {
      return ERROR_CODE;
    }

  if (conn != 'S' && conn != 'P')
    {
      return ERROR_CODE;
    }

  if (array == NULL)
    {
      return ERROR_CODE;
    }

  for (i = 0; i < count; ++i)
    {
      resistance += array[i];
    }
  return resistance;
}
