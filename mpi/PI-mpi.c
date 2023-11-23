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

  if(rank == 0){
      printf("Hello World from Master %s. I am node %d of %d \n", hn, rank, size);

  }else {
     printf("Hello World from %s. I am node %d of %d \n", hn, rank, size);    
  }


  // MUST BE CALLED at the end
  MPI_Finalize();

  return 0;
}
