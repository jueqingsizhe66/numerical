#include "mg.h"
#include "nrutil.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>


int main(int argc, char **argv){
	
	// global variable that defines which relaxation scheme to use
	// 1 : Red-Black Gauss-Siedel
	// 2 : Gauss-Siedel
	// 3 : Jacobi
	relax_scheme = 3;

	if( relax_scheme == 1)
		printf("Red-Black Gauss-Siedel Sovler Selected...\n");
	else if( relax_scheme == 2 )
		printf("Regular Gauss-Siedel Solver Selected...\n");
	else
		printf("Jacobi Solver Selected...\n");

	// global variable to define how many timesteps to do
	// ( size of timestep, alpha, etc defined in header)
	num_timesteps = 100;
	printf("Program will simulate %d timestep(s)...\n", num_timesteps);
	
	FILE *outfile;
  double ***f;
  int n=33;
	printf("Problem size n^3, where n = %d\n", n-1);
	int m = (n-1) / 2;
  int ncycle=2; // number of V cycles
	printf("Each timestep uses %d V cycles.\n", ncycle);
	f = d3tensor(1,n,1,n,1,n);
	
	// initializes to gaussian + noise
	for( int i = 2; i < n; i++ )
		for( int j = 2; j < n; j++ )
			for( int k = 2; k < n; k++ )
			{
				f[i][j][k] = 500 * exp ( - ( pow( i-n/2, 2 ) + pow( j-n/2, 2) + pow( k-n/2, 2) ))
				             * ( 0.99 + ( rand()%3) / 100.0 );
			}
 
	// run program. timesteps handled in mglin.c	
	mglin(f,n,ncycle);

	inv(f,n);
	outfile = fopen("soln.dat", "w");
  fwrite(&f[1][1][1],sizeof(double),n*n*n,outfile);
  fclose(outfile);
}

