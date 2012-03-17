#include "mg.h"

void resid(double ***res, double ***u, double ***rhs, int n)
/*
Returns minus the residual for the model problem. Input quantities are u[1..n][1..n] and
rhs[1..n][1..n], while res[1..n][1..n] is returned.
*/
{
  int i,j,k;
  double h,h2i;
  h=1.0/(n-1);
  h2i=1.0/(h*h);
	// new variables for time dependence...
	double Cx = ( ALPHA * DT ) / ( DX * DX );
	double Cy = ( ALPHA * DT ) / ( DY * DY );
	double Cz = ( ALPHA * DT ) / ( DZ * DZ );
  /* Interior points.*/
  
	// For G-s and RB G-S
	if( relax_scheme == 1 || relax_scheme == 2 )
	{
		for (k=2;k<n;k++)
			for (j=2;j<n;j++) 
				for (i=2;i<n;i++)
					res[i][j][k] = Cx / ( 1 + 2*Cx + 2*Cy + 2*Cz ) * ( u[i+1][j][k] + u[i-1][j][k] )
											 + Cy / ( 1 + 2*Cx + 2*Cy + 2*Cz ) * ( u[i][j+1][k] + u[i][j-1][k] )
											 + Cz / ( 1 + 2*Cx + 2*Cy + 2*Cz ) * ( u[i][j][k+1] + u[i][j][k-1] )
											 - rhs[i][j][k] / (2 * ALPHA * DT *
											 ( 1/(DX * DX) + 1/(DY * DY) + 1/(DZ * DZ) ) + 1 )
											 + SOURCETERM ;
  }
	// For Jacobi
	else
	{
		for (k=2;k<n;k++)
			for (j=2;j<n;j++) 
				for (i=2;i<n;i++)
					res[i][j][k] = Cx / ( 1 + 2*Cx + 2*Cy + 2*Cz ) * ( u[i+1][j][k] + u[i-1][j][k] )
											 + Cy / ( 1 + 2*Cx + 2*Cy + 2*Cz ) * ( u[i][j+1][k] + u[i][j-1][k] )
											 + Cz / ( 1 + 2*Cx + 2*Cy + 2*Cz ) * ( u[i][j][k+1] + u[i][j][k-1] )
											 - rhs[i][j][k] / (2 * ALPHA * DT *
											 ( 1/(DX * DX) + 1/(DY * DY) + 1/(DZ * DZ) ) + 1 )
											 + SOURCETERM ;

	}
	
	/* Boundary points.*/
  for (j=1;j<=n;j++)
		for (i=1;i<=n;i++) 
			res[1][i][j]=res[n][i][j]=res[i][1][j]=res[i][n][j]=res[i][j][1]=res[i][j][n]=0.0;
}
