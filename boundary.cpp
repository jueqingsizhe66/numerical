#include "header.h"

double dirichiletBC( int x, int y, int z )
{
	return 100;
}

double periodicBC( int x, int y, int z, int n, double dt )
{
	return 1000*dt*n;
}
