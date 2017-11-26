/* traveling_salesman */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define MAXCITY 200000

int main(int argc,char *argv[])
{
	int ncity;                    /* the total number of cities you must visit*/
	double x[MAXCITY],y[MAXCITY]; /* array for position data */
	int nroute[MAXCITY]={0};      /* array for route data */
	double dis_tot;               /* total distance */

	/* local variables */ 
	FILE *input, *output;
	int i,j,ii,jj, nrnd;
	double rx,ry,rr;
	clock_t cpu_time1,cpu_time2;


	/* Output how to use this program*/
	if(argc!=2){
		printf("usage:./a.out filename\n");
		exit(1);
	}


	/* Error output (check City data name) */
	input = fopen(argv[1], "r");
	if(input==NULL){
		printf("no such file or directory\n");
		exit(1);
	}


	/* Read City data */
	fscanf(input,"%d", &ncity);
	for(i = 0; i < ncity; i++){
		fscanf(input,"%lf %lf",&x[i],&y[i]);
	}
	fclose(input);


	/* Output City data (for Check) */
	printf("ncity\n");
	printf("%d\n",ncity);
	if(ncity > MAXCITY){
		printf("ncity is too large\n");
		exit(1);
	}
	printf("Initial City Position:\n");
	for(i = 0; i < ncity; i++){
		printf("%d,%lf,%lf\n",i,x[i],y[i]);
	}


	/* Stop Watch START*/
	cpu_time1 = clock();


	/*
	   ----------------------------------------
	   !!
	   !! Nearest Neighbor algorithm START!
	   !!
	   ----------------------------------------
	   */
	printf("-------------------------------\n");
	printf("Route Search Algorithm START\n");
	printf("-------------------------------\n");


	/* set initial route*/
	for (i=0; i < ncity; i++){
		nroute[i] = i;
	}

	/* generate random number */
	/*srand((unsigned)time(NULL));

	  for(i=0; i < 100; i++){
	  nrnd = rand()%(ncity);
	  printf("%d\n",nrnd);
	  } */

	printf("-------------------------------\n");
	printf("Route Search Algorithm END\n");
	printf("-------------------------------\n");

	/*
	   !!---------------------------------------
	   !!
	   !! Nearest Neighbor algorithm END!
	   !!
	   !!---------------------------------------
	   */

	/* Stop Watch END */
	cpu_time2 = clock();


	/* Output City Data */
	printf("Optimized Route\n");
	for (i=0 ; i < ncity ; i++){
		j= nroute[i];
		printf("%d,%lf,%lf\n",j,x[j],y[j]);
	}


	/* Output Distance */
	printf("\n");
	printf("Total Distance!\n");
	dis_tot = 0.0;
	for(i=0; i < ncity-1; i++){
		ii = nroute[i];
		jj = nroute[i+1];
		rx = x[ii] - x[jj];
		ry = y[ii] - y[jj];
		rr = sqrt(rx*rx + ry*ry);
		dis_tot = dis_tot + rr;
	}
	ii = nroute[ncity-1];
	jj = nroute[0];
	rx = x[ii] - x[jj];
	ry = y[ii] - y[jj];
	rr = sqrt(rx*rx + ry*ry);
	dis_tot = dis_tot + rr;
	printf("%lf\n",dis_tot);


	/* Output GNUPLOT data */
	output = fopen("route.dat","w");
	fprintf(output,"%lf\n",dis_tot);
	fprintf(output,"%20.14f\n",(double)(cpu_time2-cpu_time1)/(double)CLOCKS_PER_SEC);
	for(i = 0; i < ncity; i++){
		j = nroute[i];
		fprintf(output,"%d %lf %lf\n",j,x[j],y[j]);
	}
	j = nroute[0];
	fprintf(output,"%d %lf %lf\n",j,x[j],y[j]);
	fclose(output);


	/* Output Computational Time */
	printf("\n");
	printf("Elapsed Time: %20.14f sec\n",(double)(cpu_time2-cpu_time1)/(double)CLOCKS_PER_SEC);

	return 0;
}









