// 3D Heat DIffusion Equation Solver

#include "header.h"

using namespace std;

int main(void)
{
	// Domain boundaries, starting at (0,0,0)
	double l_x = 1;
	double l_y = 1;
	double l_z = 1;
	
	// Number of partitions, per direction
	int p_x = 100;
	int p_y = 100;
	int p_z = 100;

	// Resulting delta sizes, per direction
	double dx = l_x / p_x;
	double dy = l_y / p_y;
	double dz = l_z / p_z;
	
	// alpha for 340a Stainless Steel (m^2/s)
	double alpha = .001; //4.2E-6;

	// time step
	double dt = 0.00005;

	// number of iterations
	int nsteps = 100;

	Domain T (p_x, p_y, p_z );
	Domain Tnew (p_x, p_y, p_z);
	
	cout << "dx = dy = dz = " << dx << endl;
	for( int n = 0; n < nsteps; n++ )
	{
		double tmp;
		cout << "t = " << n << endl;
		cout << "T[50][50][50] = " << T.m[50][50][50] << endl;
		cout << "T[51][50][50] = " << T.m[51][50][50] << endl;
		cout << "T[49][50][50] = " << T.m[49][50][50] << endl;
		cout << "T[50][51][50] = " << T.m[50][51][50] << endl;
		cout << "T[50][49][50] = " << T.m[50][49][50] << endl;
		cout << "T[50][50][51] = " << T.m[50][50][51] << endl;
		cout << "T[50][50][49] = " << T.m[50][50][49] << endl;
		for( int i = 1; i <= p_x; i++ )
			for( int j = 1; j <= p_y; j++)
				for( int k = 1; k <= p_z; k++ )
					Tnew.m[i][j][k] = T.m[i][j][k] + alpha * dt *
				  	                (
					                  	( T.m[i+1][j][k] - 2*T.m[i][j][k] + T.m[i-1][j][k] ) / pow( dx, 2 ) +
						                  ( T.m[i][j+1][k] - 2*T.m[i][j][k] + T.m[i][j-1][k] ) / pow( dy, 2 ) +
					                  	( T.m[i][j][k+1] - 2*T.m[i][j][k] + T.m[i][j][k-1] ) / pow( dz, 2 )
					                  );
		for( int i = 1; i <= p_x; i++ )
			for( int j = 1; j <= p_y; j++)
				for( int k = 1; k <= p_z; k++ )
					T.m[i][j][k] = Tnew.m[i][j][k];
	}
}
