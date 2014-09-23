#include <stdio.h>


        // orig_resistance ersätts med tre seriekopplade resistorer 

int e_resistance(float orig_resistance, float *res_array)
{
   int i,count=0,e=0;
   float e1=0,e2=0,e3=0,resistor2=0,resistor3=0;
   float resistor1=orig_resistance;
    
        
   
           // e12 serien 
 
   float e12[] = {1,1.2,1.5,1.8,2.2,2.7,3.3,3.9,4.7,5.6,6.8,8.2,10,12,15,18,22,27,33,39,47,56,68,82,100,120,150,
          180,220,270,330,390,470, 560,680,820,1000,1200,1500,1800,2200,2700,3300,3900,4700,5600,6800,
          8200,10000,12000,15000,18000,22000,27000,33000,39000,47000,56000,
          68000,82000,100000,120000,150000,180000,220000,270000,330000,390000,470000,
          560000,680000,820000,1000000};
  

    for(i=0;e1<resistor1;i++)                              //resistans för resistor ett 
        e1=e12[i];
          i-=4;
          e1=e12[i];
          if(e1>=1)
          {
          resistor1=e1;
          res_array[0]=e1;
          resistor2=orig_resistance-resistor1;
          }
          else
          {
          res_array[0]=0;
          resistor2=orig_resistance;
          }
 
	  for(i=0;(e2<resistor2)&(resistor2>=1);i++)                 //resistans för resistor två
	  e2=e12[i];
          i-=2;
          e2=e12[i];
          if(e2>=1)
          {
          resistor2=e2;
            if(!res_array[0])
                res_array[0]=resistor2;
            else
             res_array[1]=e2;
          resistor3=orig_resistance-resistor1-resistor2;
          }
          else
          {
          res_array[1]=0;
          resistor3=resistor2;
          }
    
    

	  for(i=0;(e3<resistor3)&(resistor3>=1);i++)              //resistans för resistor tre
        e3=e12[i];
          if(e3>=1)
            {
            resistor3=e3;
             if(!res_array[0])
               res_array[0]=resistor3;
             else if(!res_array[1])
               res_array[1]=resistor3;
             else  
               res_array[2]= resistor3; 
           }
          else
            res_array[2]=0;

   for(i=0;i<3;i++)                                 //antal resistorer som behövdes för att ersätta orig_resistance
      {
      e=res_array[i];
          if(e>=1)
            count++;
      }


 return count;    
}





