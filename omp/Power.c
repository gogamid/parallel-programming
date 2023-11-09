#include <stdio.h>

long myPower(long n, long p){
    long res = n;
    for(long i=1; i=p; i++){
	res*=n;
    }
    return res;
}

int main(int argc, char* argv[]) {
    printf("%ld\n", myPower(3, 494975));
    return 0;
}
