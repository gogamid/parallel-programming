#include <stdio.h>
#include <pthread.h>

#define f(A) (4.0/(1.0 + A*A))
#define NUM_OF_THREADS 8

const long long n = 1000000000;
long long i;
double x, sum, pi;
double w = 1.0/n;

//better solution for distribution
typedef struct {
 long long start;
 long long end;
} input_t;

void* piFunction(void* _data){
   input_t* in  = (input_t*) _data;
   for (i=in->start; i<in->end; i++){
      x = w * ((double)i + 0.5);
      //one thread overrites of the another one. no syncchronistion
      //somehow we have to synchronise
      sum = sum + f(x);
   }
   return NULL;
}

int main(int argc, char* argv[]) {
  pthread_t thread[NUM_OF_THREADS];
  input_t in[NUM_OF_THREADS];
  long stepWidth = n / NUM_OF_THREADS;
  for (int j = 0;  j < NUM_OF_THREADS; j++){
	  in[j].start = j * stepWidth;
  	  in[j].end = (j+1) * stepWidth;
	  pthread_create(&thread[j], NULL, piFunction, &in[j]);
  }

  for (int j = 0;  j < NUM_OF_THREADS; j++)
	  pthread_join(thread[j], NULL);

  printf("pi = %.15f\n", w * sum);
  return 0;
}
