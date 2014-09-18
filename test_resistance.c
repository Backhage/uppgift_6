#include <assert.h>
#include <stdlib.h>
#include "resistance.h"

static void testErrorCountValueLessThan1();
static void testErrorConnNotSorP();
static void testErrorArrayNullPtr();
static void testSingleSerial100OhmResistor();
static void testSingleParallel100OhmResistor();
static void testTwoSerial100OhmResistors();
static void testTwoParallel100OhmResistors();
static void testParallelResistorsThatGivesDecimalValue();

/*---------------------------------------------------------------------------*/
int main()
{
  testErrorCountValueLessThan1();
  testErrorConnNotSorP();
  testErrorArrayNullPtr();
  testSingleSerial100OhmResistor();
  testSingleParallel100OhmResistor();
  testTwoSerial100OhmResistors();
  testTwoParallel100OhmResistors();
  testParallelResistorsThatGivesDecimalValue();

  exit(EXIT_SUCCESS);
}

/*---------------------------------------------------------------------------*/
void testErrorCountValueLessThan1()
{
  float resistors[1];
  assert(-1 == calc_resistance(0, 'S', resistors));
  assert(-1 == calc_resistance(-1, 'S', resistors));
}

/*---------------------------------------------------------------------------*/
void testErrorConnNotSorP()
{
  float resistors[1];
  assert(-1 == calc_resistance(1, 'A', resistors));
}

/*---------------------------------------------------------------------------*/
void testErrorArrayNullPtr()
{
  assert(-1 == calc_resistance(1, 'S', NULL));
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
  assert(200 == calc_resistance(2, 'S', resistors));
}

/*---------------------------------------------------------------------------*/
void testTwoParallel100OhmResistors()
{
  float resistors[2];
  resistors[0] = 100;
  resistors[1] = 100;
  assert(50 == calc_resistance(2, 'P', resistors));
}

/*---------------------------------------------------------------------------*/
void testParallelResistorsThatGivesDecimalValue()
{
  float resistors[2];
  resistors[0] = 25;
  resistors[1] = 25;
  assert(12.5 == calc_resistance(2, 'P', resistors));
}
