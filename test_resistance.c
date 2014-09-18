#include <assert.h>
#include <stdlib.h>
#include "resistance.h"

static void testSingleSerial100OhmResistor();
static void testSingleParallel100OhmResistor();
static void testTwoSerial100OhmResistors();

/*---------------------------------------------------------------------------*/
int main()
{
  testSingleSerial100OhmResistor();
  testSingleParallel100OhmResistor();

  exit(EXIT_SUCCESS);
}

/*---------------------------------------------------------------------------*/
void testSingleSerial100OhmResistor()
{
  float resistors[1];
  resistors[0] = 100;
  assert(100 == calc_resistance(1, 'S', resistors));
}

/*---------------------------------------------------------------------------*/
void testSingleParallel100OhmResistor()
{
  float resistors[1];
  resistors[0] = 100;
  assert(100 == calc_resistance(1, 'P', resistors));
}

/*---------------------------------------------------------------------------*/
void testTwoSerial100OhmResistors()
{
  float resistors[2];
  resistors[0] = 100;
  resistors[1] = 100;
  assert(200 == calc_resistance(1, 'S', resistors));
}
