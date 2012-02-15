#include "header.h"

// Note - BC functions are only called on boundary
// points. i.e., the below functions will never
// receive a non-boundary point.

// The user can set their own spatially dependent
// dirichilet (constant) boundary condition in the
// dirichiletBC() function below.

double dirichiletBC( int x, int y, int z )
{
	return 0;
}

// The user can set their own spatially and temporally
// dependent periodic boundary condition in the 
// periodicBC() function below.

double periodicBC( int x, int y, int z, int n, double dt )
{
	return 1000*dt*n;
}
