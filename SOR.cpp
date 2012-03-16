#include "header.h"

Domain SOR( Domain T )
{
	cout << endl << "Iterating domain using Successive Over-Relaxation method..."<<endl;

	double w = 1.65;

	int MAX_ITER = 1000;	
	cout << endl;
	cout << "t = " << 0 << endl;
	show_sample( T );	

	Domain Told = T;
	T.updateBC(0);
	Told.updateBC(0);
	
	double Cx = ( T.settings.alpha * T.settings.dt ) / pow( T.settings.dx, 2 );
	double Cy = ( T.settings.alpha * T.settings.dt ) / pow( T.settings.dy, 2 );
	double Cz = ( T.settings.alpha * T.settings.dt ) / pow( T.settings.dz, 2 );
	cout << "Cx, Cy, Cz = " << Cx<< " "<< Cy<< " "<< Cz<< endl;

	for( int n = 1; n < T.settings.nsteps; n++ )
	{
		// Starting timer...
		clock_t start, end;
		double cpu_time_used;
		start = clock();
		
		
		cout << endl<< "t = "<<n<<endl;
		T = Told;
		int iter;
		double mean;
		for( iter = 1; iter < MAX_ITER; iter++ )
		{
			Domain Tlast = T;
			for( int i = 1; i <= T.settings.p_x; i++ )
				for( int j = 1; j <= T.settings.p_y; j++)
					for( int k = 1; k <= T.settings.p_z; k++ )
						T.m[i][j][k] =  (1-w) * T.m[i][j][k]
						                + w * Cx / ( 2*Cx + 2*Cy + 2*Cz + 1 ) * ( T.m[i-1][j][k] + T.m[i+1][j][k] )
						                + w * Cy / ( 2*Cx + 2*Cy + 2*Cz + 1 ) * ( T.m[i][j-1][k] + T.m[i][j+1][k] )	
						                + w * Cz / ( 2*Cx + 2*Cy + 2*Cz + 1 ) * ( T.m[i][j][k-1] + T.m[i][j][k+1] )
						                + w * Told.m[i][j][k] / ( 2 * T.settings.alpha * T.settings.dt *
						                  ( 1/pow(T.settings.dx,2) + 1/pow(T.settings.dy,2) + 1/pow(T.settings.dz,2) )
						                  + 1 )
						                + sourceTerm( i, j, k );
			
			mean = 0;
			for( int i = 1; i <= T.settings.p_x; i++ )
				for( int j = 1; j <= T.settings.p_y; j++)
					for( int k = 1; k <= T.settings.p_z; k++ )
						mean += fabs( T.m[i][j][k] - Tlast.m[i][j][k] );
			mean = mean / ( T.settings.p_x + T.settings.p_y + T.settings.p_z );
			
			if( mean < 1e-6 )
				break;
		}
		cout << "iterations: "<<iter<<" error: "<<mean<<endl;
		Told = T;
		Told.updateBC(n);
		show_sample( T );
	
	
		// Ending timer...
		end = clock();
		cpu_time_used = ( (double) (end - start ) ) / CLOCKS_PER_SEC;
		cout << "Iterating Domain of dimension "<<T.settings.p_x<<"x";
		cout << T.settings.p_y<<"x"<<T.settings.p_z<<" took ";
		cout << cpu_time_used<<" seconds."<<endl;
	}


	return T;
}
