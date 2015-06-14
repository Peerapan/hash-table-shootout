#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int main(){
	srand(time(0));
	FILE* f_ptr;
	f_ptr = fopen("random.dat","w");
	for(long long unsigned i=0; i<40000000; i+=1)
		fprintf(f_ptr,"%llu\n",rand()%40000000;);
	fclose(f_ptr);
}