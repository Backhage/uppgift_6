#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include "resistance.h"

/*---------------------------------------------------------------------------*/
static bool validParamsSupplied(int count, char conn, float *array);
static float getResistance(int count, char conn, float *array);
static float getSerialResistorValue(int count, float *resistors);
static float getParallelResistorValue(int count, float *resistors);

/*---------------------------------------------------------------------------*/
float calc_resistance(int count, char conn, float *array)
{
  const int ERROR_CODE = -1;

  if (!validParamsSupplied(count, conn, array))
  {
    return ERROR_CODE;
  }

  return getResistance(count, conn, array);
}

/*---------------------------------------------------------------------------*/
bool validParamsSupplied(int count, char conn, float *array)
{
  bool isValid = true;
  if (count <= 0)
  {
    isValid = false;
  }
  else if (conn != 'S' && conn != 'P')
  {
    isValid = false;
  }
  else if (array == NULL)
  {
    isValid = false;
  }

  return isValid;
}

/*---------------------------------------------------------------------------*/
float getResistance(int count, char conn, float *array)
{
  float resistance = 0.0;
  if ('S' == conn)
  {
    resistance = getSerialResistorValue(count, array);
  }
  else if ('P' == conn)
  {
    resistance = getParallelResistorValue(count, array);
  }
  else
  {
    /* If we get here there is a bug in the params check. Abort! */
    assert(false);
  }

  return resistance;
}

/*---------------------------------------------------------------------------*/
float getSerialResistorValue(int count, float *resistors)
{
  float resistance = 0;
  int i = 0;
  for (i = 0; i < count; ++i)
  {
    resistance += resistors[i];
  }

  return resistance;
}

/*---------------------------------------------------------------------------*/
float getParallelResistorValue(int count, float *resistors)
{
  float resistance = 0;
  int i = 0;
  for (i = 0; i < count; ++i)
  {
    if (0 == resistors[i])
    {
      return 0;
    }
    resistance += 1.0/resistors[i];
  }

  return 1.0/resistance;
}
