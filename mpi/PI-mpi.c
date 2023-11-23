//mpicc *.c
//mpirun -n 4 --hostfile hostfile.txt --pernode ./a.out  
//
//mpirun -n 512 --npernode 24 --oversubscribe --hostfile hostfile.txt ./a.out
//512 processes 24 for each node. you # of hosts must be more than 512/24 = 21
//--oversubscribe basically reuses the process
//
#include <mpi.h>
#include <stdio.h>
#include <unistd.h>

#define f(A) (4.0/(1.0 + A*A))
const long long n = 1000000000;

double piFunction(long long start, long long end){
   long long i;
   double x, sum, pi;
   double w = 1.0/n;
   for (i=start; i<end; i++){
      x = w * ((double)i + 0.5);
      sum = sum + f(x);
   }
   return sum;
}

int main(int argc, char* argv[]) {
  MPI_Init(NULL, NULL);
  int size, rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);

  long stepWidth = n / size;
  long long start = rank * stepWidth;
  long long end = (rank+1) * stepWidth;
  double part = piFunction(start, end);

  if(rank == 0){
      double buf = 0.0;
      //for loop is for receiveing exactly size times mpi recv in any order, therefore MPI_ANY_SOURCE instead of j
      for(int j = 1; j < size; j++){
	  MPI_Recv(&buf, 1, MPI_DOUBLE, MPI_ANY_SOURCE, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
	  part += buf;
      }
      printf("Pi is %lf\n", part/n);
  }else {
     MPI_Ssend(&part, 1, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD);
  }
  MPI_Finalize();

  return 0;
}
