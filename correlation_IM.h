//header for calculating and outputting the 2-pt correlation
//function of radius for 2D Ising lattice
//by Shane Carlson

void correlation(int i, int j, long int corr[], long int pairs[]){
	int r_index;

	for(int di=1; di<L/2; di++){
		corr[di] += s[i][j]==s[wrap(i,di)][j] ? 1 : -1;
		pairs[di]++;
	}

	for(int di=-L/2+1; di<L/2; di++)
		for(int dj=1; dj<L/2; dj++)
			if(di*di+dj*dj<L*L/4){
				r_index=(int)(sqrt(di*di+dj*dj)-0.5)+1;
				corr[r_index] += s[i][j]==s[wrap(i,di)][wrap(j,dj)] ? 1 : -1;
				pairs[r_index]++;
			}
}

void record_correlation_fn(int par_sim, int par_pic){
	double m2=(double)calculate_magnetization()/(L*L);
	m2=m2*m2;

	long int corr[(int)(L/2)+1];
	long int pairs[(int)(L/2)+1];
	double dcorr;

	for(int r=0; r<=(int)(L/2); r++)
		corr[r]=pairs[r]=0;

	for(int i=0; i<L; i++)
		for(int j=0; j<L; j++)
			correlation(i, j, corr, pairs);

	char name[64]; //filename for output

	sprintf(name, "corr_raw_");
	spins_filename_instant_T0(name, L, par_sim, par_pic);
	FILE *a;
	a=fopen(name, "a");

	sprintf(name, "corr_sub_");
	spins_filename_instant_T0(name, L, par_sim, par_pic);
	FILE *b;
	b=fopen(name, "a");

	fprintf(a,"%d\t%.20f\n", 0, 1.0);
	for(int r=1; r<=L/2; r++){
		if(pairs[r]>0){
			dcorr=(double)corr[r]/pairs[r];
			fprintf(a,"%d\t%.20f\n", r, dcorr);
			fprintf(b,"%d\t%.20f\n", r, (dcorr-m2)/(1.0-m2));
		}
	}

	fprintf(a,"\n\n");
	fprintf(b,"\n\n");

	fclose(a);
	fclose(b);
}
