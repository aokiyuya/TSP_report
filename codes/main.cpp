// Author: Yuya Aoki
//
// メモ 焼き鈍し法: アニーリング法
// DP のプログラムを書く

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>

#define MAXCITY 200000
// to finish number for iterative improvement
#define FINISH_COUNT 100000

// temperature for annealing
#define T 0.5
// order for annealing
#define MAX_LOOP 10000000

int count = 0;

long double factorial(int a){

	// ans = 1;
	// for(int i = 1 ; i <= a; i++){
	// 	ans = ans * i;
	// }
	// return ans;

	if(a == 1) return 1;
	return factorial(a - 1) * a;
}

void shuffle_integer(int size, int array[size]){
	int j, k;
	srand((unsigned) time(NULL));
	for(int i = 0; i < size; i++){
		j = rand() % size;
		k = array[i];
		array[i] = array[j];
		array[j] = k;
	}
}

//solve distance between a and b
double distance(int a, int b, double *x, double *y){
	double dist_x, dist_y;
	dist_x = x[a] - x[b];
	dist_y = y[a] - y[b];
	return sqrt(dist_x * dist_x + dist_y * dist_y);
}

double total_distance(int size, int nroute[size], double x[size], double y[size]){
	int i, ii, jj;
	double rx, ry, rr, dis_tot;

	dis_tot = 0.0;

	for(i=0; i < size; i++){
		ii = nroute[i];
		if(i + 1 != size) jj = nroute[i + 1];
		if(i + 1 == size) jj = nroute[0];

		rx = x[ii] - x[jj];
		ry = y[ii] - y[jj];
		rr = sqrt(rx * rx + ry * ry);
		dis_tot += rr;
	}
	return dis_tot;
}


void copy_route(int *route_a, int *route_b, int size){
	for(int i = 0; i < size; i++) route_b[i] = route_a[i];
}


void simulated_annealing(int size, double x[size], double y[size], int nroute[size]){
	// printf("温度T:%lf", T);
	// int max_loop = int(sqrt(factorial(size)));
	srand((unsigned) time(NULL));
	bool no_use[size];
	int j, k, tmp, not_improved_count = 0;
	int best_route[size];
	double best_dist;
	double old_dist, new_dist, annea_rand, bolt_p;
	bool improved = true;
	printf("焼き鈍し法\n");
	for(int i = 0; i < size; i++) no_use[i] = true;
	for(int i = 0; i < size; i++){
		nroute[i] = i;
	}
	shuffle_integer(size, nroute);
	best_dist = total_distance(size, nroute, x, y);
	copy_route(nroute, best_route, size);
	while(improved){
		count += 1;
		old_dist = total_distance(size, nroute, x, y);
		j = rand() % size;
		k = rand() % size;
		while(k == j){
			k = rand() % size;
		}
		tmp = nroute[j];
		nroute[j] = nroute[k];
		nroute[k] = tmp;
		new_dist = total_distance(size, nroute, x, y);
		if(new_dist < old_dist){
			// not_improved_count = 0;
			if(new_dist < best_dist){
				copy_route(nroute, best_route, size);
				best_dist = new_dist;
				// printf("count:%d, best_dist:%lf\n", not_improved_count, best_dist);
				not_improved_count = 0;
			}
		}else{
			annea_rand = (double)rand() / RAND_MAX;
			bolt_p = exp( - (new_dist - old_dist) / T);
			// printf("persent:%lf, %lf\n", annea_rand, bolt_p);
			if(annea_rand < bolt_p){
			}else{
				tmp = nroute[j];
				nroute[j] = nroute[k];
				nroute[k] = tmp;
			}
		}
		not_improved_count += 1;
		// printf("%d:%d\n", not_improved_count, FINISH_COUNT);
		if(not_improved_count > FINISH_COUNT){
			improved = false;
		}
	}
	copy_route(best_route, nroute, size);
	printf("計算回数%d\n", count);
	printf("Total Distance\n");
	printf("%lf\n", total_distance(size, best_route, x, y));
}

void construction_method(int size, double x[size], double y[size], int nroute[size]){
	srand((unsigned) time(NULL));
	double min_dist =99999, dist;
	int min_dic = 999;
	bool no_use[size];
	printf("構築法\n");
	for(int i = 0; i < size; i++) no_use[i] = true;
	nroute[0] = rand() % size;
	no_use[nroute[0]] = false;
	for(int i = 1; i < size; i++){
		for(int j = 0; j < size; j++){
			count += 1;
			if(no_use[j]){
				dist = distance(i, j, x, y);
				if(dist < min_dist){
					min_dist = dist;
					min_dic = j;
				}
			}
		}
		nroute[i] = min_dic;
		min_dist = 999;
	}
	printf("計算回数%d\n", count);
	printf("Total Distance\n");
	printf("%lf\n", total_distance(size, nroute, x, y));
}


void iterative_improvement(int size, double x[size], double y[size], int nroute[size]){
	int j, k, tmp, not_improved_count = 0;
	double old_dist, new_dist;
	bool improved = true;
	srand((unsigned) time(NULL));
	printf("逐次改善法\n");
	for(int i = 0; i < size; i++){
		nroute[i] = i;
	}
	shuffle_integer(size, nroute);
	/* Output City Data */
	while(improved){
		count += 1;
		old_dist = total_distance(size, nroute, x, y);
		j = rand() % size;
		k = rand() % size;
		while(k == j){
			k = rand() % size;
		}
		tmp = nroute[j];
		nroute[j] = nroute[k];
		nroute[k] = tmp;
		new_dist = total_distance(size, nroute, x, y);
		if(new_dist < old_dist){
			not_improved_count = 0;
		}else{
			tmp = nroute[j];
			nroute[j] = nroute[k];
			nroute[k] = tmp;
			not_improved_count += 1;
		}
		if(not_improved_count > FINISH_COUNT){
			improved = false;
			break;
		}
	}
	printf("計算回数%d\n", count);
	printf("Total Distance\n");
	printf("%lf\n", total_distance(size, nroute, x, y));
}


int main(int argc, char *argv[]){
	const int FILENAME = 1;
	const int ALGORITHM = 2;
	FILE *input;
	int size;
	clock_t cpu_time1, cpu_time2;
	// int j;
	/* Output how to use this program*/
	if(argc!=3){
		printf("usage:./a.out filename Algorithm\n");
		exit(1);
	}
	/* Error output (check City data name) */
	input = fopen(argv[FILENAME], "r");
	if(input==NULL){
		printf("no such file or directory\n");
		exit(1);
	}
	/* Read City data */
	fscanf(input,"%d", &size);
	printf("size = %d\n", size);
	double x[size], y[size];
	int nroute[size];
	for(int i = 0; i < size; i++){
		fscanf(input,"%lf %lf",&x[i],&y[i]);
	}
	fclose(input);
	// printf("全探索の場合: O(n!) = %LF\n", factorial(size));
	// printf("O(n^2 * 2^n) = %lf\n", size * size * pow(2, double(size)));

	/* Stop Watch START*/
	cpu_time1 = clock();
	// printf("-------------------------------\n");
	// printf("Route Search Algorithm START\n");
	// printf("-------------------------------\n");

	/// some Algorithm
	if(strcmp(argv[ALGORITHM], "II") == 0){
		iterative_improvement(size, x, y, nroute);
	}
	else if(strcmp(argv[ALGORITHM], "CM") == 0){
		construction_method(size, x, y, nroute);
	}
	else if(strcmp(argv[ALGORITHM], "SA") == 0){
		simulated_annealing(size, x, y, nroute);
	}
	else{
		printf("Algorithms are SA, CM and II.");
		exit(1);
	}

	// printf("-------------------------------\n");
	// printf("Route Search Algorithm END\n");
	// printf("-------------------------------\n");
	cpu_time2 = clock();

	/* Output City Data */
	// printf("Optimized Route\n");
	// for (int i=0 ; i < size ; i++){
	// 	j = nroute[i];
	// 	printf("%d,%lf,%lf\n",j,x[j],y[j]);
	// }

	/* Output Distance */
	// printf("\n");
	// printf("Total Distance!\n");
	// printf("%lf\n", total_distance(size, nroute, x, y));


	/* Output Computational Time */
	printf("\n");
	printf("Elapsed Time: %20.14f sec\n",(double)(cpu_time2-cpu_time1)/(double)CLOCKS_PER_SEC);

	FILE *output;
	char str[30] = "outputs/route_";
	strcat(str, argv[ALGORITHM]);
	strcat(str, argv[FILENAME]);
	output = fopen(str, "w");
	fprintf(output,"%lf\n", total_distance(size, nroute, x, y));
	fprintf(output,"%20.14f\n",(double)(cpu_time2-cpu_time1)/(double)CLOCKS_PER_SEC);
	fprintf(output, "%d\n", count);
	int j;
	for(int i = 0; i < size; i++){
		j = nroute[i];
		fprintf(output,"%d %lf %lf\n",j,x[j],y[j]);
	}
	fclose(output);

	return 0;
}
/* vim:set foldmethod=marker: */
