#include <stdio.h>
#include <pthread.h>

#define f(A) (4.0/(1.0 + A*A))
#define NUM_OF_THREADS 8

const long long n = 1000000000;
long long i;
double x, sum, pi;
double w = 1.0/n;

//problem here, it uses same function, they should use same logic,meaning different parameters
//we did not distribute the code
void* piFunction(void* data){
   for (i=0; i<n; i++){
      x = w * ((double)i + 0.5);
      sum = sum + f(x);
   }
}

int main(int argc, char* argv[]) {

  sum = 0.0;

  pthread_t thread[NUM_OF_THREADS];
  for (int j = 0;  j < NUM_OF_THREADS; j++)
	  pthread_create(&thread[j], NULL, piFunction, NULL);

  for (int j = 0;  j < NUM_OF_THREADS; j++)
	  pthread_join(thread[j], NULL);

  printf("pi = %.15f\n", w * sum);
  return 0;
}
