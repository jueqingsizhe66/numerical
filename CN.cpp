#include "header.h"

Domain CN( Domain T )
{
	for( int it = 0; it < T.settings.nsteps; it++)
	{
		T.updateBC( it );
		cout << endl;
		cout << "t = " << it << endl;
		show_sample( T );	
		
		double C = T.settings.dt * T.settings.alpha / 2;
		double diag = 1 + 2*C / pow(T.settings.dx, 2) + 2*C / pow(T.settings.dy,2) + 2*C/pow(T.settings.dz,2);
		double xdiag = - C / pow(T.settings.dx,2);
		double ydiag = - C / pow(T.settings.dy,2);
		double zdiag = - C / pow(T.settings.dz,2);
		int xs;
		int ys;
		int zs;
		int length = (T.settings.p_x) * (T.settings.p_y) * (T.settings.p_z);
		
		// Creation of A
		vector<vector<double> > A;
		A.resize(length);
		for( int i = 0; i < length; i++ )
		{
			A[i].resize(length);
			for( int j = 0; j < length; j++ )
			{
				// Main diagonal
				if( i == j )
					A[i][j] = diag;
				
				// Z diagonals
				else if( j == i - 9 )
				{
					if( i < T.settings.p_x * T.settings.p_y )	
						A[i][j] = 0;
					else
						A[i][j] = zdiag;
				}
				else if( j == i + 9 )
				{
					if( i > length - T.settings.p_z )
						A[i][j] = 0;
					else
						A[i][j] = zdiag;
				}
				
				// Y diagonals
				else if( j == i - 3 )
				{
					if( ( i / T.settings.p_x ) % T.settings.p_y == 0 )
						A[i][j] = 0;
					else
						A[i][j] = ydiag;
				}
				else if( j == i + 3 )
				{
					if( ( i / T.settings.p_x ) % T.settings.p_y == T.settings.p_y - 1 )
						A[i][j] = 0 ;
					else
						A[i][j] = ydiag;	
				}
				
				// X diagonals
				else if( j == i - 1 )
				{	
					if( i % T.settings.p_x == 0 )
						A[i][j] = 0;
					else
						A[i][j] = xdiag;
				}
				else if( j == i + 1 )
				{
					if( i % T.settings.p_x == T.settings.p_x - 1 )
						A[i][j] = 0;
					else
						A[i][j] = xdiag;
				}

				else
					A[i][j] = 0;
			}
		}
		

		// Initialization of x	
		vector<double> x;
		x.resize(length);
		
/*		
		// print upper left of A
		for( int i = 0; i < 20; i++ )
		{
			if( i % 10 == 0)
				cout << endl;	
			for( int j = 0; j < 20; j++ )
			{
				if( j % 10 == 0 )
					cout << "  ";
				cout << setw(9) <<  A[i][j] <<" ";		
			}
			cout << endl;
		}
*/
		// Initialization / Update of b
		vector<double> b;
		b.resize(length+1);

		for( int i = 0; i < length; i++ )
		{
			xs = i % T.settings.p_x + 1;
			ys = ( i / T.settings.p_x ) % T.settings.p_y + 1;
			zs = ( ( i / T.settings.p_x ) / T.settings.p_y ) % T.settings.p_z + 1;
			
			double term1 = C / pow(T.settings.dx,2) * (T.m[xs+1][ys][zs] - 2*T.m[xs][ys][zs] + T.m[xs-1][ys][zs]);
			double term2 = C / pow(T.settings.dy,2) * (T.m[xs][ys+1][zs] - 2*T.m[xs][ys][zs] + T.m[xs][ys-1][zs]);
			double term3 = C / pow(T.settings.dz,2) * (T.m[xs][ys][zs+1] - 2*T.m[xs][ys][zs] + T.m[xs][ys][zs-1]);
			b[i] = T.m[xs][ys][zs] + term1 + term2 + term3 + sourceTerm(xs, ys, zs);
		}

		// GAUSSIAN ELIMINATION
		
		// GE - upper-triangulate
		double scale;
		for (int j=0;j<length;++j)           /* loop over columns */
			for (int i=j+1;i<length;++i)      /* loop over rows beneath pivot */
			{
				if (A[i][j] != 0)
				{
					scale = A[i][j]/A[j][j];  /* zero out based on pivot */
					for (int k=0;k<length;++k)
						A[i][k] = A[i][k] - A[j][k]*scale;
					b[i] = b[i] - b[j]*scale; /* same for b */
				}
			}
		
		// GE - Back substitution
		x[length-1] = b[length-1]/A[length-1][length-1];
		for (int i=length-2;i>=0;--i)
		{
			x[i] = b[i];
			for (int j=i+1;j<length;++j)
			{
				x[i] -= A[i][j]*x[j];
			}
			x[i]/=A[i][i];
		}

		// SOLUTION CALCULATED - stored in x vector.
		
		// loads solution vector (x) back into the 3-D Domain
		for( int i = 0; i < length ; i++ )
		{
			xs = i % T.settings.p_x + 1;
			ys = ( i / T.settings.p_x ) % T.settings.p_y + 1;
			zs = ( ( i / T.settings.p_x ) / T.settings.p_y ) % T.settings.p_z + 1;
			T.m[xs][ys][zs] = x[i];
		}

	}
	return T;
}
