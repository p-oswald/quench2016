//Potts model lattice header
//for the 2D Potts Model
//by Shane Carlson

double drand48();

int s[L_max][L_max]; //array of spins s(x,y)
int s_proposed; //proposed color for a flip

int E; //current energy
int EC; //energy contribution

static inline int inc(int k){
	return k<L-1 ? k+1 : 0;
}

static inline int dec(int k){
	return k>0 ? k-1 : L-1;
}

static inline int wrap(int k, int dk){

	if(dk>0){
		if(k+dk>L-1)
			return k+dk-L;
		else
			return k+dk;
	}
	if(dk<0){
		if(k+dk<0)
			return k+dk+L;
		else
			return k+dk;
	}
	else
		return k;
}

static inline int bond(int spin1, int spin2){
	return spin1==spin2 ? -1 : 0;
}

void initialize_lattice_to_middle(){
	int color=(int)((float)q/2.0);

	for(int i=0;i<L;i++)
		for(int j=0;j<L;j++)
			s[i][j]=color;
}

void initialize_lattice_random(){

	for(int i=0;i<L;i++)
		for(int j=0;j<L;j++)
			s[i][j] = (int)(drand48()*q); //random int from 0 to q
}

int first_top_color(){
	int count[q];
	int max_count=0;

	for(int col=0; col<q; col++)
		count[col]=0;

	for(int i=0;i<L;i++)
		for(int j=0;j<L;j++)
			count[s[i][j]]++;

	for(int col=0; col<q; col++)
		if(count[col]>max_count)
			max_count=count[col];

	for(int col=0; col<q; col++)
		if(count[col]==max_count)
			return col;
}


int calculate_magnetization(int resp_color){
	int M=0;

	for(int i=0;i<L;i++)
		for(int j=0;j<L;j++)
			M += s[i][j]==resp_color ? 1 : -1;
	return M;
}
