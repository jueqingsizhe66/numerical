#include "header.h"

Domain FTCS( Domain T )
{
	Domain Tnew = T;
	Tnew.updateBC(0);
	T.updateBC(0);
	for( int n = 0; n < T.settings.nsteps; n++ )
	{
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
	}
	return T;
}
