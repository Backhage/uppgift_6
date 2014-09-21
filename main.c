#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "resistance.h"
#include "power.h"
#include "component.h"

/*---------------------------------------------------------------------------*/
#define INPUT_BUFFER_SIZE 1024
#define MAX_REPLACEMENT_RESISTORS 3

/*---------------------------------------------------------------------------*/
static int   query_user_int(char *user_query_p);
static char  query_user_char(char *user_query_p);
static char *query_user(char *user_query_p);
static void  get_resistor_values(int no_of_resistors, float *values_p);
static void  print_replacement_resistors(int no_of_resistors, float* values_p);

/*---------------------------------------------------------------------------*/
int main(int argc, char *argv[])
{
  int voltage = 0;
  char connection_type = '\0';
  int no_of_resistors = 0;
  float *resistors_p = NULL;
  float resistance = 0;
  float power = 0;
  int no_of_replacement_resistors = 0;
  float *replacement_resistors_p = 
    malloc(MAX_REPLACEMENT_RESISTORS * sizeof(float));

  voltage = query_user_int("Ange spänningskälla i V: ");
  connection_type = query_user_char("Ange koppling[S | P]: ");
  no_of_resistors = query_user_int("Antal komponenter: ");

  resistors_p = malloc(no_of_resistors * sizeof(float));
  get_resistor_values(no_of_resistors, resistors_p);

  resistance = calc_resistance(
    no_of_resistors,
    connection_type,
    resistors_p
    );
  power = calc_power_r(voltage, resistance);
  no_of_replacement_resistors = e_resistance(
    resistance,
    replacement_resistors_p
    );

#ifdef _MAIN_DEBUG__
  printf("Antal ersättningsresistanser: %d",
	 no_of_replacement_resistors);
#endif

  printf("Ersättningsresistans: %.2f ohm\n", resistance);
  printf("Effekt: %.2f W\n", power);
  printf("Ersättningsresistanser i E12-serien kopplade i serie: ");
  print_replacement_resistors(
    no_of_replacement_resistors,
    replacement_resistors_p
    );

#ifdef _MAIN_DEBUG__
  int i = 0;
  for(i = 0; i < no_of_resistors; i++)
  {
    printf("Komponent %d: %.2f\n", i, resistors_p[i]);
  }
  printf("Vald koppling: %c\n", connection_type);
#endif

  free(resistors_p);
  free(replacement_resistors_p);

  return 0;
}
/*---------------------------------------------------------------------------*/
void print_replacement_resistors(int no_of_resistors, float* values_p)
{
  int i = 0;
  for(i = 0; i < no_of_resistors; i++)
  {
    printf("%.0f ", values_p[i]);
  }
  printf("\n");
}

/*---------------------------------------------------------------------------*/
void get_resistor_values(int no_of_resistors, float *values_p)
{
  int i = 0;
  char *user_input_p = malloc(INPUT_BUFFER_SIZE);

  for (i = 0; i < no_of_resistors; i++)
  {
    snprintf(user_input_p, INPUT_BUFFER_SIZE, "Komponent %d i ohm: ", i+1);
    values_p[i] = query_user_int(user_input_p);
  }
  free(user_input_p);
}

/*---------------------------------------------------------------------------*/
int query_user_int(char *user_query_p)
{
  int result = 0;
  char *buffer = NULL;
  buffer = query_user(user_query_p);
  if (NULL == buffer)
  {
    return(-1);
  }
  result = atoi(buffer);
  free(buffer);

  return(result);
}

/*---------------------------------------------------------------------------*/
char query_user_char(char *user_query_p)
{
  char *buffer = NULL;
  char result = '\0';
  buffer = query_user(user_query_p);
  if (NULL == buffer)
  {
    return(-1);
  }
  result = buffer[0];
  free(buffer);

  return(result);
}

/*---------------------------------------------------------------------------*/
char *query_user(char *user_query_p)
{
  char *input_buffer = malloc(INPUT_BUFFER_SIZE);
  printf("%s", user_query_p);
  fgets(input_buffer, INPUT_BUFFER_SIZE, stdin);

  if (strlen(input_buffer) < 1)
  {
    free(input_buffer);
    return(NULL);
  }

  return(input_buffer);
}
