#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "resistance.h"
#include "power.h"
#include "e_resistance.h"

char *get_input(char *s)
{
 char *inpbuff;
 inpbuff=malloc(1024);
 printf(s);
 fgets(inpbuff,1024,stdin);

 if(strlen(inpbuff)<1)
 {
  free(inpbuff);
  return(NULL);
 }
 return(inpbuff);
}

int get_int(char *s)
{
 int result;
 char *buff;
 buff=get_input(s);
 if(buff==NULL) return(-1);
 result=atoi(buff);
 free(buff);
 return(result);
}

char get_char(char *s)
{
 char *buff,result;
 buff=get_input(s);
 if(buff==NULL) return(-1);
 result=buff[0];
 free(buff);
 return(result);
}

int main(int argc, char *argv)
{
 int components,i,volt,count;
 char *question,conn;
 float *array,resistance,power,*res_array;
 question=malloc(1024);
 res_array=malloc(sizeof(float)*3);

 volt=get_int("Ange spänningskälla i V: ");
 conn=get_char("Ange koppling[S | P]: ");
 components=get_int("Antal komponenter: ");
 array=malloc(sizeof(float)*components);
 for(i=0;i<components;i++)
 {
  snprintf(question,1024,"Komponent %d i ohm: ",i+1);
  array[i]=get_int(question);
 }
 resistance=calc_resistance(components,conn,array);
 printf("Ersättningsresistans: %.2f ohm\n",resistance);
 power=calc_power_r(volt,resistance);
 printf("Effekt: %.2f W\n",power);
 count=e_resistance(resistance,res_array);
#ifdef _MAIN_DEBUG__
 printf("Ersättningsresistance (%d):",count);
#else
 printf("Ersättningsresistancer i E12-serien kopplade i serie: ");
#endif
 for(i=0;i<count;i++)
 {
  printf("%.0f ",res_array[i]);
 }
 printf("\n");

#ifdef _MAIN_DEBUG__
 for(i=0;i<components;i++)
 {
  printf("Komponent %d: %.2f\n",i,array[i]);
 }
 printf("Vald koppling: %c\n",conn);
#endif
 free(question);
 free(array);
 free(res_array);
}
