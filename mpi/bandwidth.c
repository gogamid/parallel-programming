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
#include <unistd.h>
#define REPS 100

int main(int argc, char* argv[]) {
  MPI_Init(NULL, NULL);
  int size, rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);
  float msg = 1.0f;

  if(rank == 0){
      double start = MPI_Wtime();
      for (int i = 0; i < REPS; i++){
	  MPI_Ssend(&msg, 1, MPI_FLOAT, 1, 17, MPI_COMM_WORLD);
	  MPI_Recv(&msg, 1, MPI_FLOAT, 1, 23, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
      }
      double end = MPI_Wtime();
      printf("Latency is %lf nsec \n", ((end - start)/(2 * REPS)) * 1E9);
  } else if (rank == 1){
      for (int i = 0; i < REPS; i++){
	  MPI_Recv(&msg, 1, MPI_FLOAT, 0, 17, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
	  MPI_Ssend(&msg, 1, MPI_FLOAT, 0, 23, MPI_COMM_WORLD);
      }
  } else {}
  MPI_Finalize();
  return 0;
}
