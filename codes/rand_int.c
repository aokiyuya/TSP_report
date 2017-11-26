/* random number generator */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

int main()
{

  int i;
  int min,max,nrnd;
  double rnd;

  srand((unsigned)time(NULL));

  min = 1;
  max = 6;
  
  for(i=0; i < 100; i++){
    nrnd = min + rand()%(max-min+1);
    printf("%d\n",nrnd);
  }


  return 0;
}









