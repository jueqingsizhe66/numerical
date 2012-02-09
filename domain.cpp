#include "header.h"

Domain::Domain ( Settings s )
{
	settings = s;
	p_x = settings.p_x;
	p_y = settings.p_y;
	p_z = settings.p_z;

	// Sets m size. The +2 is for the boundary conditions
  m.resize(p_x+2);
  for( int i = 0; i < p_x+2; i++ )
  {
    m[i].resize(p_y+2);
    for( int j = 0; j < p_y+2; j++ )
      m[i][j].resize(p_z+2);
	}

	// Initializes m to gaussian form + noise
	for( int i = 0; i < p_x+2; i++ )
		for( int j = 0; j < p_y+2; j++ )
			for( int k = 0; k < p_z+2; k++ )
				m[i][j][k] = 500*exp(-(
				                 pow(i-p_x/2,2)
				               + pow(j-p_y/2,2)
				               + pow(k-p_z/2,2)
										 )) + rand()%5;
	
	// Intiailizes Boundary Conditions to a default value of 0;
	// BC's will be set to their selected values when running
	// a solver function, FTCS or Crank Nicholson.
	for( int i = 0; i < p_x+2; i++ )
		for( int j = 0; j < p_y+2; j++ )
			for( int k = 0; k < p_z+2; k++ )
				if( i == 0 || j == 0 || k == 0 || i == p_x+1 || j == p_y+1 || k == p_z+1 )
					m[i][j][k] = 0;
}

void Domain::updateBC( int n )
{
	
	if(settings.dirichilet == false)
	{
		for( int i = 0; i < p_x+2; i++ )
			for( int j = 0; j < p_y+2; j++ )
				for( int k = 0; k < p_z+2; k++ )
				{
					if( i == 0 || j == 0 || k == 0 || i == p_x+1 || j == p_y+1 || k == p_z+1 )
					{	
						m[i][j][k] = periodicBC( i, j, k, n, settings.dt );
					}
				}
	}

	else if( n == 0 )
	{
		for( int i = 0; i < p_x+2; i++ )
			for( int j = 0; j < p_y+2; j++ )
				for( int k = 0; k < p_z+2; k++ )
				{	
					if( i == 0 || j == 0 || k == 0 || i == p_x+1 || j == p_y+1 || k == p_z+1 )
					{	
						m[i][j][k] = dirichiletBC(i, j, k );
					}
				}
	}
}	

void Domain::print( void )
{	
	cout << "Printing Domain" << endl;
	cout << "Domain has the following dimensions: (";
	cout << p_x << ", " << p_y << ", " << p_z << ")" << endl;
	for( int i = 0; i < p_x+2; i++ )
	{
		cout << "Slice x = " << i << endl;
		for( int j = 0; j < p_y+2; j++ )
		{
			for( int k = 0; k < p_z+2; k++ )
			{
				cout.precision(2);
				cout << scientific << m[i][j][k] << " ";
			}
			cout << endl;
		}
	}
}

Domain& Domain::operator= (const Domain& param)
{
	settings = param.settings;
	m = param.m;
	return *this;
}
