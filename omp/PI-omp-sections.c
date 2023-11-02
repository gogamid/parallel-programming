// gcc -fopenmp -O2 PI-omp-sections.c -o PI-omp-sections
// .time ./PI-omp-sections
#include <stdio.h>
#include <pthread.h>

#define f(A) (4.0/(1.0 + A*A))
#define NUM_OF_THREADS 8

const long long n = 1000000000;
double x, pi;
double w = 1.0/n;

typedef struct {
  long long start;
  long long end;
  double partSolution;
} input_t;

void* piFunction(void* _data){
  double sum = 0.0;
  input_t* inout  = (input_t*) _data;
  for (long long i=inout->start; i<inout->end; i++){
    x = w * ((double)i + 0.5);
    sum = sum + f(x);
  }
  inout->partSolution = sum;
  return NULL;
}

int main(int argc, char* argv[]) {
  //create threads and structs (same number of)
  long long stepWidth = n / NUM_OF_THREADS;
  input_t in[NUM_OF_THREADS];
  for (int j = 0;  j < NUM_OF_THREADS; j++){
    in[j].start = j * stepWidth;
    in[j].end = (j+1) * stepWidth;
  }
#pragma omp parallel 
{
 #pragma omp sections 
  {
	
    #pragma omp section
    {
	piFunction(&in[0]);
    }
    #pragma omp section
    {
	piFunction(&in[1]);
    }
    #pragma omp section
    {
	piFunction(&in[2]);
    }
    #pragma omp section
    {
	piFunction(&in[3]);
    }
    #pragma omp section
    {
	piFunction(&in[4]);
    }
    #pragma omp section
    {
	piFunction(&in[5]);
    }
    #pragma omp section
    {
	piFunction(&in[6]);
    }
    #pragma omp section
    {
	piFunction(&in[7]);
    }
 }
}
  
  double sum = 0.0;

  for (int j = 0;  j < NUM_OF_THREADS; j++)
    sum+=in[j].partSolution;

  printf("pi = %.15f\n", w * sum);
  return 0;
}
