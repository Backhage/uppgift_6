float calc_power_r(float volt, float resistance)
{
 float p=0.0;
 if(resistance==0) return -1; //if resistance is 0, then we have a potential division by zero

 p=volt*volt/resistance;
 return(p);
}

float calc_power_i(float volt, float current)
{
 float p=0.0;
 p=volt*current;
 return(p);
}
