/* random number generator */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

int main()
{

  int i;
  double rnd;

  srand((unsigned)time(NULL));
  
  for(i=0; i < 100; i++){
    rnd = (double)rand()/RAND_MAX;
    printf("%lf\n",rnd);
  }
  
  
  return 0;
}









