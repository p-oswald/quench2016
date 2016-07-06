//single-cluster (a.k.a. Wolff) Monte Carlo simulation header 
//for the 2D Ising Model - square with periodic boundary conditions
//by Shane Carlson

#define P_add_c_IM (1.0/(1.0+1.0/sqrt(2))); //$P_{add,c}$ for Ising model

bool cluster_state; //original cluster state
int cluster_size; //number of spins currently in cluster
double P_add; //$P_{add}$=1-e$^{-2\beta}$

void cluster(int i, int j, int from){

	if(s[i][j]==cluster_state){
		if(from==8 || drand48()<P_add){
			cluster_size++;
			s[i][j] ^= 1; //flips the spin
			if(from!=0) //right
				cluster(inc(i), j     , 2);
			if(from!=1) //down
				cluster(i     , dec(j), 3);
			if(from!=2) //left
				cluster(dec(i), j     , 0);
			if(from!=3) //up
				cluster(i     , inc(j), 1);
		}
	}
}

void wolff_step(){

	cluster_size=0;
	int i = (int)(drand48()*L); // rand. int. 0 through L-1
	int j = (int)(drand48()*L);
	cluster_state=s[i][j];
	cluster(i, j, 8);
}
