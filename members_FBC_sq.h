//N-fold square lattice header
//for the 2D Ising and Potts Models
//by Shane Carlson

void subtract_local_members(int i, int j){

	if(i<L-1)
		members[ sc[i+1][j  ] ]--; 
	if(j>0)
		members[ sc[i  ][j-1] ]--; 
	if(i>0)
		members[ sc[i-1][j  ] ]--;
	if(j<L-1)
		members[ sc[i  ][j+1] ]--;

	members[ sc[i][j] ]--;
}

void add_local_members(int i, int j){

	if(i<L-1)
		members[ sc[i+1][j  ] ]++; 
	if(j>0)
		members[ sc[i  ][j-1] ]++; 
	if(i>0)
		members[ sc[i-1][j  ] ]++;
	if(j<L-1)
		members[ sc[i  ][j+1] ]++;

	members[ sc[i][j] ]++;
}
