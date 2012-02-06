#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

double BC( int x, int y, int z );

class Domain
{
	public:
		int p_x, p_y, p_z;
		vector<vector<vector<double> > > m;
		Domain( int x, int y, int z );
		void print( void );
};
