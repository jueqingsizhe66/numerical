#include "mg.h"

void slvsml(double ***u, double ***rhs)
/* 
   Solution of the model problem on the coarsest grid, where h = 1
   2 . The right-hand side is input
   in rhs[1..3][1..3] and the solution is returned in u[1..3][1..3].
*/

{
  void fill0(double ***u, int n);
  double h=0.5;
  fill0(u,3);
  u[2][2][2] = - rhs[2][2][2] / 
	             (2 * ALPHA * DT *
							 ( 1/(DX * DX) + 1/(DY * DY) + 1/(DZ * DZ) ) 
							 + 1 ) + SOURCETERM ;
}
