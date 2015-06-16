#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define MAX 40000000

int main(){
	srand(time(0));
	FILE* f_ptr;
	f_ptr = fopen("random.dat","w");
	for(long long unsigned i=0; i<MAX; i+=1)
		fprintf(f_ptr,"%llu\n",rand()%MAX);
	fclose(f_ptr);
    
    return 0;
}