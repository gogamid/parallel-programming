//mpicc *.c
//mpirun -n 4 --hostfile hostfile.txt --pernode ./a.out  
#include <mpi.h>
#include <stdio.h>
#include <unistd.h>

#define f(A) (4.0/(1.0 + A*A))

const long long n = 1000000000;

int main(int argc, char* argv[]) {
 
  int size = 0, rank = 0;
  char hn[128];
  gethostname(hn, 128);

  // MUST BE CALLED at first
  MPI_Init(NULL, NULL);

  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);

  int number;
  if(rank == 0){
      printf("Hello World from Master %s. I am node %d of %d \n", hn, rank, size);
      MPI_Recv(&number, 1, MPI_INT, 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
      printf("Process 1 received number %d from process 0\n",
           number);
  }else {
     number = -1;
     MPI_Send(&number, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
     printf("Hello World from %s. I am node %d of %d \n", hn, rank, size);    
  }

  // MUST BE CALLED at the end
  MPI_Finalize();

  return 0;
}
