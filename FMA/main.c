#include "mg.h"
#include "nrutil.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char **argv){
  //int i,j;
	FILE *outfile;
  double ***f;
  int n=257;
	int m = (n-1) / 2;
  int ncycle=2; // number of V cycles
	f = d3tensor(1,n,1,n,1,n);
  f[m][m][m]=1.0;
  //  for (i=2;i<n;++i)
  //  for (j=2;j<n;++j)
  //    f[i][j] = 2.0;
  
	
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
