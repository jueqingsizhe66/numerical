#include "header.h"

Domain CN( Domain T )
{
	Domain Tnew = T;
	Tnew.updateBC(0);
	T.updateBC(0);

	// I'm pretty sure Crank Nicolson doesn't work in 2-D or 3-D systems.

	return T;
}
