//mpicc *.c
//mpirun -n 4 --hostfile hostfile.txt --pernode ./a.out  
//
//mpirun -n 512 --npernode 24 --oversubscribe --hostfile hostfile.txt ./a.out
//512 processes 24 for each node. you # of hosts must be more than 512/24 = 21
//--oversubscribe basically reuses the process
//
//
#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define REPS 10
#define MSIZE 10 * 1024 * 1024
#define KIB 1024
#define MIB (1024 * KIB)

int main(int argc, char* argv[]) {
  MPI_Init(NULL, NULL);
  int size, rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);
  int MaxSize = 10 * MIB;
  char* msg10mb = (char *)malloc(MaxSize);
  int startSize = KIB;
  

  if(rank == 0){
    for(int j = startSize; j <= MaxSize; j=j*2){
      double start = MPI_Wtime();
      for(int i = 0; i < REPS; i ++){
	  MPI_Ssend(msg10mb, j , MPI_CHAR, 1, 17, MPI_COMM_WORLD);
      }
      double end = MPI_Wtime();
      double latency = end - start;
      //printf("Latency is %lf nsec \n", ((end - start)) * 1E9);
      printf("Bandwidth for %d is %lf MB/sec \n",j, (((j * REPS) / latency)) /(1024 * 1024));
    }
  } else if (rank == 1){
    for(int j = startSize; j <= MaxSize; j=j*2){
      for(int i = 0; i < REPS; i ++){
	  MPI_Recv(msg10mb, j, MPI_CHAR, 0, 17, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
      }
    }
  } else {}
  free(msg10mb);
  MPI_Finalize();
  return 0;
}
