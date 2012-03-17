#include "mg.h"
#include "nrutil.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

// global variable that defines which relaxation scheme to use
// 1 : Red-Black Gauss-Siedel
// 2 : Gauss-Siedel
// 3 : Jacobi

int main(int argc, char **argv){
	relax_scheme = 2;
	FILE *outfile;
  double ***f;
  int n=257;
	int m = (n-1) / 2;
  int ncycle=2; // number of V cycles
	f = d3tensor(1,n,1,n,1,n);
	
	// initializes to gaussian + noise
	for( int i = 2; i < n; i++ )
		for( int j = 2; j < n; j++ )
			for( int k = 2; k < n; k++ )
			{
				f[i][j][k] = 500 * exp ( - ( pow( i-n/2, 2 ) + pow( j-n/2, 2) + pow( k-n/2, 2) ))
				             * ( 0.99 + ( rand()%3) / 100.0 );
			}
  
	
	// Clock and timing init.
	clock_t start, end;
	double cpu_time_used;
	start = clock();	
	
	// Running the FMA
	mglin(f,n,ncycle);
  
	// Clock and timing finish.
	end = clock();
	cpu_time_used = ( (double) (end-start) ) / CLOCKS_PER_SEC;
	printf("Time used: %lf seconds\n", cpu_time_used);
	
	outfile = fopen("soln.dat", "w");
  fwrite(&f[1][1][1],sizeof(double),n*n*n,outfile);
  fclose(outfile);
}
