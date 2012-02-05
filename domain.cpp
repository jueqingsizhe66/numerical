#include<iostream>
#include<vector>

using namespace std;

class Domain
{
	public:
		int p_x, p_y, p_z;
		vector<vector<vector<double> > > domain;
		Domain( int x, int y, int z );
		void circshift( int xs, int ys, int zs );
		void print_domain( void );
};

Domain::Domain ( int x, int y, int z )
{
	p_x = x;
	p_y = y;
	p_z = z;

	// Sets domain size
  domain.resize(p_x);
  for( int i = 0; i < p_x; i++ )
  {
    domain[i].resize(p_y);
    for( int j = 0; j < p_y; j++ )
      domain[i][j].resize(p_z);
	}

	// Intializes all values to 0
	for( int i = 0; i < p_x; i++ )
		for( int j = 0; j < p_y; j++ )
			for( int k = 0; k < p_z; k++ )
				domain[i][j][k] = 0;
}

void circshift( int xs, int ys, int zs )
{
}

void Domain::print_domain( void )
{
	cout << "Printing Domain" << endl;
	cout << "Domain has the following dimensions: (";
	cout << p_x << ", " << p_y << ", " << p_z << ")" << endl;
	for( int i = 0; i < p_x; i++ )
	{
		cout << "Slice x = " << i << endl;
		for( int j = 0; j < p_y; j++ )
		{
			for( int k = 0; k < p_z; k++ )
			{
				cout.precision(2);
				cout << scientific << domain[i][j][k] << " ";
			}
			cout << endl;
		}
	}
}


int main(void)
{
	Domain T (3, 6, 2);
	T.domain[1][1][1] = 2.43E-4;
	T.print_domain();
	return 0;
}
