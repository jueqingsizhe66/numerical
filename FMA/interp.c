void interp(double ***uf, double ***uc, int nf)
/*
  Coarse-to-fine prolongation by bilinear interpolation. nf is the fine-grid dimension. The coarsegrid
  solution is input as uc[1..nc][1..nc], where nc = nf/2 + 1. The fine-grid solution is
  returned in uf[1..nf][1..nf].
*/
{
  int ic,iif,jc,jf,kc,kf,nc;
  nc=nf/2+1;
	// my interpolation method basically just does 2-D interpolation for each slice of the cube.
	// This seems like a reasonable methodology to me.
	for (kc=1,kf=1;kc<=nc;kc++,kf+=2)
  {
		/* Do elements that are copies.*/
		for (jc=1,jf=1;jc<=nc;jc++,jf+=2) 
			for (ic=1;ic<=nc;ic++) 
				uf[2*ic-1][jf][kf]=uc[ic][jc][kc];
		/* Do odd-numbered columns, interpolating vertically.*/
		for (jf=1;jf<=nf;jf+=2) 
			for (iif=2;iif<nf;iif+=2) 
				uf[iif][jf][kf] = 0.5*(uf[iif+1][jf][kf]+uf[iif-1][jf][kf]);
		/*Do even-numbered columns, interpolating horizontally.*/
		for (jf=2;jf<nf;jf+=2) 
			for (iif=1;iif <= nf;iif++) 
				uf[iif][jf][kf]=0.5*(uf[iif][jf+1][kf]+uf[iif][jf-1][kf]);
	}
}
