#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <inttypes.h>
#include <sys/time.h>
#include <sys/types.h>
#include <time.h>

#include <google/sparse_hash_map>

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
	google::sparse_hash_map<int64_t, int64_t> hash;
	hash.set_deleted_key(-1);
	double before = get_time();
	double after;
	for(int64_t i=0 ; i<MAXMIZE; i+=1){
		int64_t r = rand()%arr_max;
		hash.insert(google::sparse_hash_map<int64_t, int64_t>::value_type(arr[r], arr[r]));
		arr[r] = arr[arr_max-1];
		arr_max-=1;
	}
	after = get_time();
    printf("Insert : %f\n", after-before);
    before = after;
	google::sparse_hash_map<int64_t, int64_t>::const_iterator it;
	int64_t m;
	for(int64_t i=0 ; i<MAXMIZE; i+=1){
		m = rand()%MAXMIZE;
		it = hash.find(m);
		if( it->second == m){
			count1 += 1;
		}else{
			count2 += 1;
		}
	}
	std::cout << "Correct : " << count1 << ", Wrong : " << count2 << std::endl;
    after = get_time();
    printf("Find : %f\n", after-before);
	free(arr);
	return 0;
}