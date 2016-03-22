#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <mpi.h>

/*
Para compilar: mpicc -std=c99 -g -Wall -o aula exercicioaula.c -lm
Para executar: 
*/

int main(){
	double x,y;
	int h = 0;
	int h_local=0;
	long int n = 99999999998;//1000000000;
	int my_rank,comm_sz,n_local,source;
	double pi,euclidian;
	double r = 0.5;

 	MPI_Init(NULL, NULL);
	
	MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

	MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);

	n_local = n/comm_sz;
	
  srand(time(NULL));
	for(int i=0;i<n_local;i++){
		x = ((double) rand() / (RAND_MAX));
		y = ((double) rand() / (RAND_MAX));
		//printf("%lf %lf \n",x,y);
		euclidian = sqrt(pow((x-r),2)+pow((y-r),2));
		//printf("%lf",euclidian);
		if(euclidian <= r){
			h_local++;
		}	 
	}

	if(my_rank != 0){
		 MPI_Send(&h_local, 1, MPI_INT, 0, 0, MPI_COMM_WORLD); 
	}else{
		h = h_local;
		for(source=1;source<comm_sz;source++){
      MPI_Recv(&h_local, 1, MPI_INT, source, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
			h += h_local;	
		}
	}
	
	if(my_rank == 0){
		printf("h: %d n: %ld \n",h,n);
		pi = ((4*(double) h)/(double) n);
		printf("Valor estimado de pi: %lf \n",pi); 
	}

	MPI_Finalize();

	return 0;
}

