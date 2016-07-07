#define _GNU_SOURCE
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <sys/stat.h>
#include <unistd.h>

#include "critical_temperatures.h"
#include "parameters.h"
#include "filenames_T0.h"

#include "IM.h" // !
#include "Wolff_IM_PBC_sq.h" // !
#include "energies_PBC_sq.h"
#include "domain_size_PBC_sq.h"

#include "persistence.h"
#include "persistence_mass.h"
#include "correlation_IM.h" // !

#include "nfold_IM_glauber.h" // !
#include "class_PBC_sq.h"
#include "nfold.h"

#include "print_lattice_T0.h"


int main(int argc, char* argv[]){

	char name[64]="dir_";

	spins_foldername_T0(name, q, L);
	if(mkdir(name, S_IRWXU)==-1)
		printf("there were issues making the directory \'%s\'\n", name);
	if(chdir(name)==-1)
		printf("there were issues changing to the directory \'%s\'\n", name);

	// /*
	double QN;
	double time;
	double tic;
	int t_ind;

	double pic_tic; //actual time when the lattice shots are taken
	int pic, max_pics=0; //indexes the lattice shots for file handling
	double pic_tic_mult=7;

	FILE *t;
	t=fopen("rts.txt", "w"); //raw timeseries

	FILE *ticsfile;
	ticsfile=fopen("tics_key.txt", "w");
	// */

	FILE *tts;
	tts=fopen("therm.txt", "w");

	srand48(lrand48());

	//initialize_lattice_to_middle(); // !
	for(int sim=0; sim<samples; sim++){

		fprintf(ticsfile, "sim %d\n", sim+1);
		printf("sim %d of %d\n", sim+1, samples);
		 /*
		P_add=1-exp(-B_c_ising); // !
		//for(int swp=0; swp<therm || calculate_magnetization()!=0; swp++){ // !
		for(int swp=0; swp<therm; swp++){ //thermalization for finite T_i
			wolff_step();
			if(sim==0){
				calculate_energy();
				fprintf(tts, "%d\t%f\n", E, calculate_avg_domain_size());
			}
		}
		printf("1\n");

		// */
		initialize_lattice_up_w_prob(0.5);
		record_correlation_fn(samples, 0);
		if(sim==0)
			plot_bool_lattice(s, 128, 0, 0); // !
		// /* 
		printf("1\n");

		reset_persistence_lattice();
		printf("1\n");

		update_all_classes();
		printf("1\n");

		count_all_members();
		printf("1\n");

		set_flip_probabilities();
		printf("1\n");

		blocked_state=0;
		time=0.0;
		tic=tic_start;
		t_ind=0;
		pic_tic=1;
		pic=1;
		printf("1\n");

		while(tic<max_time && !blocked_state){
			printf("2\n");

			QN=calculate_QN();
			printf("2\n");

			time -= log(drand48())/QN; //time update for FOLLOWING step
			printf("2\n");

			if(time > tic){
				while(time > tic*tic_mult){
					printf("tic at %f skipped\n", tic);
					tic*=tic_mult;
					t_ind++;
				}
				printf("tic at %3.3f \n", tic);
				calculate_energy();
				fprintf(t, "%d\t%.20f\t%d\t%.20f\t%.20f\t%.20f\n",
					t_ind,
					tic,
					E,
					calculate_avg_domain_size(),
					(double)calculate_persistence()/(L*L),
					(double)members[0]/(L*L)
				); //timeseries
				tic*=tic_mult;
				t_ind++;
			}
			if(time > pic_tic){
				if(sim==0){
					plot_bool_lattice(s, 128, sim, pic); // !
					plot_int_lattice(p, 128, sim, pic);
					plot_int_lattice_01(p, 128, sim, pic);
				}
				record_correlation_fn(samples, pic);
				record_persistence_mass(samples, pic);
				fprintf(ticsfile, "%d\t%.20f\n", pic, pic_tic);
				pic_tic*=pic_tic_mult;
				pic++;
			}
			T0_nfold_step(QN);
		}
		if(blocked_state)
			printf("ended in a blocked state\n");
		fprintf(t, "\n\n");
		fprintf(ticsfile, "\n\n");

		if(sim==0){
			plot_bool_lattice(s, 128, sim, pic); //128x128 windows // !
			plot_int_lattice(p, 128, sim, pic);
			plot_int_lattice_01(p, 128, sim, pic);
			if(L>128){
				plot_bool_lattice(s, L, sim, pic); //full-sized lattices // !
				plot_int_lattice(p, L, sim, pic);
				plot_int_lattice_01(p, L, sim, pic);
			}
		}
		if(pic>max_pics)
			max_pics=pic;
	// */
	}
	FILE *numpicsfile;
	numpicsfile=fopen("num_pics.txt", "w");
	fprintf(numpicsfile, "%d\n", max_pics-1);

	fclose(t);
	fclose(tts);
	fclose(ticsfile);
	fclose(numpicsfile);

	return 0;
}
