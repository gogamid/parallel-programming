#include <stdio.h>
#include <pthread.h>

#define f(A) (4.0/(1.0 + A*A))

const long long n = 1000000000;
long long i;
double x, sum, pi;
double w = 1.0/n;

void* piFunction(void* data){
   for (i=0; i<n; i++){
      x = w * ((double)i + 0.5);
      sum = sum + f(x);
   }
}

int main(int argc, char* argv[]) {

  sum = 0.0;

  pthread_t  thread;
  pthread_create(&thread, NULL, piFunction, NULL);
  pthread_join(thread, NULL);

  printf("pi = %.15f\n", w*sum);
  return 0;
}
