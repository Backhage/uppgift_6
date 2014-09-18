#include <stdlib.h>
#include "resistance.h"

/*---------------------------------------------------------------------------*/
static int invalidParamsSupplied(int count, char conn, float *array);
static float getSerialResistorValue(int count, float *resistors);
static float getParallelResistorValue(int count, float *resistors);

/*---------------------------------------------------------------------------*/
float calc_resistance(int count, char conn, float *array)
{
  const int ERROR_CODE = -1;
  float resistance = 0;
  int i = 0;

  if (invalidParamsSupplied(count, conn, array))
    {
      return ERROR_CODE;
    }

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
      return ERROR_CODE;
    }

  return resistance;
}

/*---------------------------------------------------------------------------*/
int invalidParamsSupplied(int count, char conn, float *array)
{
  const int INVALID = 1;
  const int VALID = 0;

  if (count <= 0)
    {
      return INVALID;
    }

  if (conn != 'S' && conn != 'P')
    {
      return INVALID;
    }

  if (array == NULL)
    {
      return INVALID;
    }

  return VALID;
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
