#include "header.h"

Domain FTCS( Domain T )
{
	cout << endl << "Iterating domain using FTCS method..." << endl;
	Domain Tnew = T;
	Tnew.updateBC(0);
	T.updateBC(0);
	for( int n = 0; n < T.settings.nsteps; n++ )
	{
		// Starting timer...
		clock_t start, end;
		double cpu_time_used;
		start = clock();

		T.updateBC(n);
		cout << endl;
		cout << "t = " << n << endl;
		show_sample( T );
		
		for( int i = 1; i <= T.settings.p_x; i++ )
			for( int j = 1; j <= T.settings.p_y; j++)
				for( int k = 1; k <= T.settings.p_z; k++ )
					Tnew.m[i][j][k] = T.m[i][j][k] + T.settings.alpha * T.settings.dt *
					                (
					                	( T.m[i+1][j][k] - 2*T.m[i][j][k] + T.m[i-1][j][k] )
					                		/ pow( T.settings.dx, 2 ) +
					                	( T.m[i][j+1][k] - 2*T.m[i][j][k] + T.m[i][j-1][k] )
					                		/ pow( T.settings.dy, 2 ) +
					                	( T.m[i][j][k+1] - 2*T.m[i][j][k] + T.m[i][j][k-1] )
					                		/ pow( T.settings.dz, 2 )
					                )
					                + sourceTerm( i, j, k );

		T = Tnew;
		
		// Ending timer...
		end = clock();
		cpu_time_used = ( (double) (end - start ) ) / CLOCKS_PER_SEC;
		cout << "Iterating Domain of dimension "<<T.settings.p_x<<"x";
		cout << T.settings.p_y<<"x"<<T.settings.p_z<<" took ";
		cout << cpu_time_used<<" seconds."<<endl;
	}
	return T;
}
