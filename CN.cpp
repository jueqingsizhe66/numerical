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
	for( int i = 1; i < (T.settings.p_x + 2) * (T.settings.p_y+2) * (T.settings.p_z+2); i++ )
	{
		x.push_back( T.m[i%p_x][(i/p_x)%p_y][((i/p_x)%p_y)%p_z] );
	}
	
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
