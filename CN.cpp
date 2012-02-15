#include "header.h"

Domain CN( Domain T )
{
	for( int it = 0; it < T.settings.nsteps; it++)
	{
		cout << "beginning iteration # " << it << endl;
		T.updateBC( it );
		cout << "BC updated..." << endl;
		double C = T.settings.dt * T.settings.alpha / 2;
		double diag = 1 + 2*C / pow(T.settings.dx, 2) + 2*C / pow(T.settings.dy,2) + 2*C/pow(T.settings.dz,2);
		double xdiag = - C / pow(T.settings.dx,2);
		double ydiag = - C / pow(T.settings.dy,2);
		double zdiag = - C / pow(T.settings.dz,2);
		
		cout << "C and diags calculated..." << endl;

		// First, we need to load our temperature domain into
		// a vector format for x.
		vector<double> x;
		int xs;
		int ys;
		int zs;
		int length = (T.settings.p_x) * (T.settings.p_y) * (T.settings.p_z);
		for( int i = 0; i < length ; i++ )
		{
			xs = i % T.settings.p_x + 1;
			ys = ( i / T.settings.p_x ) % T.settings.p_y + 1;
			zs = ( ( i / T.settings.p_x ) / T.settings.p_y ) % T.settings.p_z + 1;
			x.push_back( T.m[xs][ys][zs] );
		}
		// x has been initialized
		cout << "x initalized..." << endl;
		// Now I need to make A.
		vector<vector<double> > A;
		A.resize(length + 1);
		for( int i = 1; i <= length; i++ )
		{
			A[i].resize(length+1);
			for( int j = 1; j <= length; j++ )
			{
				if( i == j )
					A[i][j] = diag;
				else if( j == i - 9 || j == i + 9 ) // far back z (check on 7)
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
		cout << "A created..." << endl;		
		// Now I need to calculate the inital b.
		// Each entry is for the RHS of the respective AX=b equation.
		// I need my notes for this.

		vector<double> b; // to initialize it to the right size
		b.resize(length+1);

		for( int i = 0; i < length; i++ )
		{
			xs = i % T.settings.p_x + 1;
			ys = ( i / T.settings.p_x ) % T.settings.p_y + 1;
			zs = ( ( i / T.settings.p_x ) / T.settings.p_y ) % T.settings.p_z + 1;
			
			double term1 = C / pow(T.settings.dx,2) * (T.m[xs+1][ys][zs] - 2*T.m[xs][ys][zs] + T.m[xs-1][ys][zs]);
			double term2 = C / pow(T.settings.dy,2) * (T.m[xs][ys+1][zs] - 2*T.m[xs][ys][zs] + T.m[xs][ys-1][zs]);
			double term3 = C / pow(T.settings.dz,2) * (T.m[xs][ys][zs+1] - 2*T.m[xs][ys][zs] + T.m[xs][ys][zs-1]);
			b[i] = T.m[xs][ys][zs] + term1 + term2 + term3;
		}
		// b has been initialized.
		cout << "b has been initialized" << endl;
		// Now I need to run gaussian elimination to determine the new x vector.


	// GAUSSIAN ELIMINATION

	//upper-triangulate -- NEED TO CHECK THE # OF ITERATIONS...
		double scale;
		for (int j=0;j<length;++j)           /* loop over columns */
			for (int i=j+1;i<length;++i)      /* loop over rows beneath pivot */
			{
				for( int l = i+1; l < length; l++ ) // loop checks if there's a bigger pivot
					if( A[i][j] < A[l][j] )      // and swaps rows if there is.
					{	
						for( int k = 0; k < length; k++ )
						{
							// swaps rows
							double tmp = A[i][k];
							A[i][k] = A[l][k];
							A[l][k] = tmp;
						}
						l = i;
					}
				if (A[i][j] != 0)
				{
					scale = A[i][j]/A[j][j];  /* zero out based on pivot */
					for (int k=0;k<length;++k)
						A[i][k] = A[i][k] - A[j][k]*scale;
					b[i] = b[i] - b[j]*scale; /* same for b */
				}
			}
	cout << "Upper Triangulate complete..." << endl;		
	// Back substitution
		x[length-1] = b[length-1]/A[length-1][length-1];
		cout << "starting backsub..." << endl;
		for (int i=length-2;i>0;--i)
		{
			cout << "i = " << i << endl;
			x[i] = b[i];
			for (int j=i+1;j<length;++j)
			{
				x[i] -= A[i][j]*x[j];
			}
			x[i]/=A[i][i];
		}
		cout << "backsub complete..." << endl;
		// After elimination, xnew vector must be fed into next iteration.

		// loads solution vector (x) back into the Domain object
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
