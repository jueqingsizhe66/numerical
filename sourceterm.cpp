#include "header.h"

// The user can define their own spatially
// dependent source term function in the
// sourceTerm() function below.

double sourceTerm( int i, int j, int k )
{
	return 0.01;
}
