#include "header.h"

vector<double> mat_mult( vector<vector<double> > A, vector<double> b )
{
	vector<double> r = b; // Resulting matrix
	int l = b.size();
	
	if( b.size() != A[0].size() )
	{	
		cout << "Error. Matrixes not the same size" << endl;
		return b;
	}

	for( int i = 0; i < l; i++ )
	{
		r[i] = 0;
		for( int delta = 0; delta < l; delta++ )
			r[i] += A[i][delta] * b[delta];
	}
	
	return r;
}

vector<vector<double> > mat_mat_mult( vector<vector<double> > A, vector<vector<double> > B )
{
	vector<vector<double> > R = A;
	int size = A.size();
	for( int rows = 0; rows < size; rows++ )
		for( int cols = 0; cols < size; cols++ )
		{
			R[rows][cols] = 0;
			for( int delta = 0; delta < size; delta++ )
				R[rows][cols] += A[rows][delta] * B[delta][cols];
		}
	return R;
}

vector<vector<double> > mat_sub( vector<vector<double> > A, vector<vector<double> > B )
{
	vector<vector<double> > r = A; // Resulting matrix
	int length = A.size();
	
	for( int i = 0; i < length; i++ )
		for( int j = 0; j < length; j++ )
			r[i][j] = A[i][j] + B[i][j];
	
	return r;
}

vector<double> vec_add( vector<double> a, vector<double> b )
{
	vector<double> r = a;
	for( int i = 0; i < a.size(); i++ )
		r[i] = a[i] + b[i];
	return r;
}
