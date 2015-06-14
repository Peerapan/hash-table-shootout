#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <inttypes.h>
#include <sys/time.h>
#include <sys/types.h>
#include <time.h>

#include <glib.h>

#define MAXMIZE 40000000

double get_time(void)
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return tv.tv_sec + (tv.tv_usec / 1000000.0);
}

int main(int argc, char ** argv){
	int64_t* arr = (int64_t*) malloc(sizeof(int64_t) * MAXMIZE);
	for(int64_t i=0;i<MAXMIZE ;i+=1)
		arr[i] = i;
	int64_t arr_max = MAXMIZE;
	printf("%s\n",argv[0]);
	srand(time(0));
	int64_t count1 = 0;
	int64_t count2 = 0;
	GHashTable * hash;
	hash = g_hash_table_new(g_direct_hash, g_direct_equal);
	double before = get_time();
	double after;
	int64_t* a = (int64_t*) malloc(sizeof(int64_t) * MAXMIZE);
	for(int64_t i=0 ; i<MAXMIZE; i+=1){
		int64_t r = rand()%arr_max;
		a[arr[r]] = arr[r];
		g_hash_table_insert(hash, GINT_TO_POINTER(arr[r]), &a[arr[r]]);
		arr[r] = arr[arr_max-1];
		arr_max-=1;
	}
	after = get_time();
    printf("Insert : %f\n", after-before);
    before = after;
	int64_t m;
	for(int64_t i=0 ; i<MAXMIZE; i+=1){
		m = rand()%MAXMIZE;
		gpointer num = g_hash_table_lookup (hash, GINT_TO_POINTER(m));
		if(num && m == *(int64_t *)num){
			count1 += 1;
		}else{
			count2 += 1;
		}
	}
	std::cout << "Correct : " << count1 << ", Wrong : " << count2 << std::endl;
    after = get_time();
    printf("Find : %f\n", after-before);
	free(a);
	free(arr);
	return 0;
}