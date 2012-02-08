#include "header.h"

Domain FTCS( Domain T )
{
	Domain Tnew = T;
	for( int n = 0; n < T.settings.nsteps; n++ )
	{
		cout << "t = " << n << endl;
		cout << "T[50][50][50] = " << T.m[50][50][50] << endl;
		cout << "T[51][50][50] = " << T.m[51][50][50] << endl;
		cout << "T[49][50][50] = " << T.m[49][50][50] << endl;
		cout << "T[50][51][50] = " << T.m[50][51][50] << endl;
		cout << "T[50][49][50] = " << T.m[50][49][50] << endl;
		cout << "T[50][50][51] = " << T.m[50][50][51] << endl;
		cout << "T[50][50][49] = " << T.m[50][50][49] << endl;
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
					                  );
		for( int i = 1; i <= T.settings.p_x; i++ )
			for( int j = 1; j <= T.settings.p_y; j++)
				for( int k = 1; k <= T.settings.p_z; k++ )
					T.m[i][j][k] = Tnew.m[i][j][k];
	}
	return T;
}