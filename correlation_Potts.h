//header for calculating and outputting the 2-pt correlation
//function of radius for 2D Ising lattice
//by Shane Carlson

void correlation(int i, int j, int ftc, long int corr[], long int pairs[]){

	for(int di=0; di<=L/2; di++){
		corr[di] += (s[i][j]==ftc)^(s[wrap(i,di)][j]==ftc) ? -1 : 1;
		pairs[di]++;
	}

	for(int di=-L/2; di<=L/2; di++){
		for(int dj=1; dj<=L/2; dj++){
			if(di*di+dj*dj<=L*L/4){
				corr[(int)sqrt(di*di+dj*dj)] += (s[i][j]==ftc)^(s[wrap(i,di)][wrap(j,dj)]==ftc) ? -1 : 1;
				pairs[(int)sqrt(di*di+dj*dj)]++;
			}
		}
	}
}

void record_correlation_fn(int par_sim, int par_pic){
	int ftc=first_top_color();
	double m2=(double)calculate_magnetization(ftc)/(L*L);
	m2=m2*m2;

	long int corr[(int)(L/2)+1]={0};
	long int pairs[(int)(L/2)+1]={0};
	double dcorr;

	for(int i=0; i<L; i++)
		for(int j=0; j<L; j++)
			correlation(i, j, ftc, corr, pairs);

	char name[64]; //filename for output

	sprintf(name, "corr_");
	spins_filename_instant_T0(name, L, par_sim, par_pic);
	FILE *a;
	a=fopen(name, "a");

	for(int r=0; r<=(int)(L/2); r++){
		if(pairs[r]>0){
			dcorr=((double)corr[r]/pairs[r]-m2)/(1.0-m2);
			fprintf(a,"%d\t%.20f\n", r, dcorr);
		}
	}

	fprintf(a,"\n\n");
	fclose(a);
}
