#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "component.h"
#include "power.h"
#include "resistance.h"

/*---------------------------------------------------------------------------*/
#define MAX_REPLACEMENT_RESISTORS 3

/*---------------------------------------------------------------------------*/
struct input_data_s
{
  int voltage;
  char connection_type;
  int no_of_resistors;
  float *resistors_p;
};

struct output_data_s
{
  float resistance;
  float power;
  int no_of_replacement_resistors;
  float *replacement_resistors_p;
};

/*---------------------------------------------------------------------------*/
static void get_data_from_user(struct input_data_s *input_data_p);
static void calculate_output_data(struct input_data_s *input_data_p,
				  struct output_data_s *output_data_p);
static void print_output_data(struct output_data_s *output_data);
static int  get_input_int(void);
static char get_input_char(void);
static float* query_resistors(int no_of_resistors);
static float get_input_float(void);
static void print_replacement_resistors(float* values_p);

/*---------------------------------------------------------------------------*/
int main(int argc, char *argv[])
{
  struct input_data_s input_data = {0, '\0', 0, NULL};
  struct output_data_s output_data = {0.0, 0.0, 0, NULL};
  output_data.replacement_resistors_p =
    malloc(MAX_REPLACEMENT_RESISTORS * sizeof(float));

  get_data_from_user(&input_data);
  calculate_output_data(&input_data, &output_data);
  print_output_data(&output_data);

  free(input_data.resistors_p);
  free(output_data.replacement_resistors_p);
  exit(EXIT_SUCCESS);
}

/*---------------------------------------------------------------------------*/
void get_data_from_user(struct input_data_s *input_data_p)
{
  printf("Ange sp\u00E4nningsk\u00E4lla i V: ");
  input_data_p->voltage = get_input_int();
  printf("Ange koppling[S | P]: ");
  input_data_p->connection_type = get_input_char();
  printf("Antal komponenter: ");
  input_data_p->no_of_resistors = get_input_int();
  input_data_p->resistors_p = query_resistors(input_data_p->no_of_resistors);
}

/*---------------------------------------------------------------------------*/
int get_input_int(void)
{
  int retval = 0;
  char ch = '\0';

  scanf("%d", &retval);
  while ((ch=getchar()) != EOF && ch != '\n')
    ;

  return retval;
}

/*---------------------------------------------------------------------------*/
char get_input_char(void)
{
  char retval = '\0';
  char ch = '\0';

  scanf("%c", &retval);
  while ((ch=getchar()) != EOF && ch != '\n')
    ;

  return retval;
}

/*---------------------------------------------------------------------------*/
float* query_resistors(int no_of_resistors)
{
  float* resistors_p = malloc(no_of_resistors * sizeof(float));
  int i = 0;
  for (i = 0; i < no_of_resistors; ++i)
  {
    printf("Komponent %d i ohm: ", i+1);
    resistors_p[i] = get_input_float();
  }

  return resistors_p;
}

/*---------------------------------------------------------------------------*/
float get_input_float(void)
{
  float retval = 0.0;
  char ch = '\0';

  scanf("%f", &retval);
  while ((ch=getchar()) != EOF && ch != '\n')
    ;

  return retval;
}

/*---------------------------------------------------------------------------*/
void calculate_output_data(struct input_data_s *input_data_p,
			   struct output_data_s *output_data_p)
{
  output_data_p->resistance = calc_resistance(
    input_data_p->no_of_resistors,
    input_data_p->connection_type,
    input_data_p->resistors_p
    );

  output_data_p->power = calc_power_r(
    input_data_p->voltage,
    output_data_p->resistance
    );

  output_data_p->no_of_replacement_resistors = e_resistance(
    output_data_p->resistance,
    output_data_p->replacement_resistors_p
    );

  if ((-1 == output_data_p->resistance) ||
      (-1 == output_data_p->power)      ||
      ( 0 == output_data_p->no_of_replacement_resistors))
  {
    fprintf(stderr, "FEL: Kunde inte beräkna utdata. "\
	    "Kontrollera inparametrarna.\nAvslutar programmet.\n");
    exit(EXIT_FAILURE);
  }
}

/*---------------------------------------------------------------------------*/
void print_output_data(struct output_data_s *output_data_p)
{
  printf("Ers\u00E4ttningsresistans: %.2f ohm\n", output_data_p->resistance);
  printf("Effekt: %.2f W\n", output_data_p->power);
  printf("Ers\u00E4ttningsresistanser i E12-serien kopplade i serie: ");
  print_replacement_resistors(
    output_data_p->replacement_resistors_p
    );
}

/*---------------------------------------------------------------------------*/
void print_replacement_resistors(float* values_p)
{
  int i = 0;
  for(i = 0; i < MAX_REPLACEMENT_RESISTORS; i++)
  {
    if (values_p[i] > 0)
    {
      printf("%.1f ", values_p[i]);
    }
  }
  printf("\n");
}
