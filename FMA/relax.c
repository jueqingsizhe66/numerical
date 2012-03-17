#include "mg.h"
#include <math.h>
#include <stdio.h>

void relax(double ***u, double ***rhs, int n)
/*
  Red-black Gauss-Seidel relaxation for model problem. Updates the current value of the solution
  u[1..n][1..n], using the right-hand side function rhs[1..n][1..n].
*/
{
  int i,ipass,isw,j,jsw=1;
  double h,h2;
  h=1.0/(n-1);
  h2=h*h;
  /* Red and black sweeps.*/
  /* jsw and isw toggle between 1 and 2 and
     determine starting row in each column
     for given pass 
  */

	// new variables for time dependence...
	double Cx = ( ALPHA * DT ) / ( DX * DX );
	double Cy = ( ALPHA * DT ) / ( DY * DY );
	double Cz = ( ALPHA * DT ) / ( DZ * DZ );


	// Different relaxation schemes are dependent on the global variable
	// relax_scheme.
	// 1 : Red-Black Gauss-Seidel
	// 2 : Gauss-Seidel
	// 3 : Jacobi

	// Red-Black Gauss-Seidel
	if( relax_scheme == 1 )
	{
		// My method is to do sweeps through each slice of the cube.
		int k;
		for (k=2;k<n;k++)
			for (ipass=1;ipass<=2;ipass++,jsw=3-jsw)
			{ 
				isw=jsw;
				for (j=2;j<n;j++,isw=3-isw)
					/*Gauss-Seidel formula.*/
					for (i=isw+1;i<n;i+=2) 
						u[i][j][k]=  Cx / ( 1 + 2*Cx + 2*Cy + 2*Cz ) * ( u[i+1][j][k] + u[i-1][j][k] )
											 + Cy / ( 1 + 2*Cx + 2*Cy + 2*Cz ) * ( u[i][j+1][k] + u[i][j-1][k] )
											 + Cz / ( 1 + 2*Cx + 2*Cy + 2*Cz ) * ( u[i][j][k+1] + u[i][j][k-1] )
											 - rhs[i][j][k] / (2 * ALPHA * DT *
											 ( 1/(DX * DX) + 1/(DY * DY) + 1/(DZ * DZ) ) + 1 )
											 + SOURCETERM ;
			}
	}

	// Regular Gauss-Seidel
	else if( relax_scheme == 2 )
	{
		int iter;
		double mean;
		for( iter = 1; i <= MAX_ITER; iter++)
		{
			double *** u_last = u;
			for( int i = 2; i < n; i++ )
				for( int j = 2; j < n; j++)
					for( int k = 2; k < n; k++ )
					{
						u[i][j][k]=  Cx / ( 1 + 2*Cx + 2*Cy + 2*Cz ) * ( u[i+1][j][k] + u[i-1][j][k] )
											 + Cy / ( 1 + 2*Cx + 2*Cy + 2*Cz ) * ( u[i][j+1][k] + u[i][j-1][k] )
											 + Cz / ( 1 + 2*Cx + 2*Cy + 2*Cz ) * ( u[i][j][k+1] + u[i][j][k-1] )
											 - rhs[i][j][k] / (2 * ALPHA * DT *
											 ( 1/(DX * DX) + 1/(DY * DY) + 1/(DZ * DZ) ) + 1 )
											 + SOURCETERM ;
					}
			
			// Calculating mean value
			mean = 0.0;
			for( int i = 2; i < n; i++ )
				for( int j = 2; j < n; j++)
					for( int k = 2; k < n; k++ )
						mean += fabs( u[i][j][k] - u_last[i][j][k] );
			mean = mean / ( n + n + n );

			// checking mean value, ending iterations if limit met
			if( mean < 1e-6)
			{
				break;
			}
		}
	}

	// Jacobi
	else
	{
		int iter;
		double mean;
		double *** u_new = u;
		double *** u_old = u;
		for( iter = 1; i <= MAX_ITER; iter++)
		{
			for( int i = 2; i < n; i++ )
				for( int j = 2; j < n; j++)
					for( int k = 2; k < n; k++ )
					{
						u[i][j][k]=  Cx / ( 1 + 2*Cx + 2*Cy + 2*Cz ) * ( u[i+1][j][k] + u[i-1][j][k] )
											 + Cy / ( 1 + 2*Cx + 2*Cy + 2*Cz ) * ( u[i][j+1][k] + u[i][j-1][k] )
											 + Cz / ( 1 + 2*Cx + 2*Cy + 2*Cz ) * ( u[i][j][k+1] + u[i][j][k-1] )
											 - rhs[i][j][k] / (2 * ALPHA * DT *
											 ( 1/(DX * DX) + 1/(DY * DY) + 1/(DZ * DZ) ) + 1 )
											 + SOURCETERM ;
					}
			
			// Calculating mean value
			mean = 0.0;
			for( int i = 2; i < n; i++ )
				for( int j = 2; j < n; j++)
					for( int k = 2; k < n; k++ )
						mean += fabs( u[i][j][k] - u_new[i][j][k] );
			mean = mean / ( n + n + n );

			// checking mean value, ending iterations if limit met
			if( mean < 1e-6)
			{
				break;
			}
			u = u_new;
		}
	}
}
