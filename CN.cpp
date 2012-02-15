#include "header.h"

Domain CN( Domain T )
{
	double C = T.settings.dt * T.settings.aplha / 2;
	double diag = 1 + 2*C / pow(T.settings.dx, 2) + 2*C / pow(T.settings.dy,2) + 2*C/pow(T.settings.dz,2);
	double xdiag = - C / pow(T.settings.dx,2);
	double ydiag = - C / pow(T.settings.dy,2);
	double zdiag = - C / pow(T.settings.dz,2);

	// First, we need to load our temperature domain into
	// a vector format for x.
	vector<double> x;
	int xs;
	int ys;
	int zs;
	int length = (T.settings.p_x + 2) * (T.settings.p_y+2) * (T.settings.p_z+2);
	for( int i = 1; i <= length ; i++ )
	{
		xs = i % p_x;
		ys = ( i / p_x ) % p_y;
		zs = ( ( i / p_x ) / p_y ) % p_z;
		x.push_back( T.m[xs][ys][zs] );
	}
	// x has been initialized

	// Now I need to make A.
	vector<vector<double> > A;
	for( int i = 1; i <= length; i++ )
	{
		for( int j = 1; j <= length; j++ )
		{
			if( i == j )
				A[i][j] = diag;
			else if( j == i - 7 || j == i + 7 ) // far back z (check on 7)
				A[i][j] = zdiag;
			else if( j == i - 3 || j == i + 3 ) // These don't take into account the 'sub-square' pattern effect
				A[i][j] == ydiag;
			else if( j == i - 1 || j == i + 1 ) // but I'll add that later...
				A[i][j] = xdiag;
			else
				A[i][j] = 0;
		}
	}
	// A has now been created.
	
	// Now I need to calculate the inital b.
	// Each entry is for the RHS of the respective AX=b equation.
	// I need my notes for this.

	vector<double> xnew;


	Domain Tnew = T;
	Tnew.updateBC(0);
	T.updateBC(0);
	for( int n = 0; n < T.settings.nsteps; n++ )
	{
		vector 
		T = Tnew;
	}
	return T;

}
