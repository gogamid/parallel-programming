#include <stdio.h>

#define f(A) (4.0/(1.0 + A*A))

const long long n = 100000000;
//omp is shared memory model, it is okay when we just read shared variable
//shared variable duptlicated for each thread
//here sum shared unintendently, be careful with that => race condition -> use synchronisiation
//clause is data scope
//firstprivate = beginning private then shared
//lastprivate other way around
//copyin = copy from two places
//reduction
//
//compiler directives
//#pragma
//
//conditional
//#ifdef _OPENMP
//	do something
//#endif
//example: include omp.h if _OPENMP is available
//
//
//for loop should be in canonical form
//
//nowait for the results that we need later
//
//this works only for for loop, it is a short form for 
/*
 
#pragma omp parallel
{
    #pragma omp parallel for
    for loop
}

 */
int main(int argc, char* argv[]) {
    long long i;
    double x, sum, pi;
    double w = 1.0/n;

    sum = 0.0;

    #pragma omp parallel for schedule(static,5)
    for (int i = 0; i<n; i++){
	x = w * ((double)i + 0.5);
        #pragma omp critical
	sum = sum + f(x);
    }
    printf("pi = %.15f\n", w*sum);
    return 0;
}
