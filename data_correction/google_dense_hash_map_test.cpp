#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <inttypes.h>
#include <sys/time.h>
#include <sys/types.h>
#include <time.h>

#include <google/dense_hash_map>
#include <functional>

#define MAXMIZE 5000000

int64_t hashing_func(int64_t key)
{
	return key%10;
}

bool key_equal_fn(int64_t t1, int64_t t2)
{
	return t1 == t2;
}

double get_time(void)
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return tv.tv_sec + (tv.tv_usec / 1000000.0);
}

//typedef google::dense_hash_map<int64_t, int64_t>::size_type hash_s;
//typedef google::dense_hash_map<int64_t, int64_t, std::function<int64_t(int64_t)>, std::function<bool(int64_t,int64_t)> > hash_t;

typedef google::dense_hash_map<int64_t, int64_t>::size_type hash_s;
typedef google::dense_hash_map<int64_t, int64_t> hash_t;

int main(int argc, char ** argv){
	int64_t* arr = (int64_t*) malloc(sizeof(int64_t) * MAXMIZE);
	for(int64_t i=0;i<MAXMIZE ;i+=1)
		arr[i] = i;
	int64_t arr_max = MAXMIZE;
	printf("%s\n",argv[0]);
	srand(time(0));
	int64_t count1 = 0;
	int64_t count2 = 0;
	hash_s n = 0;
//	hash_t hash(n, hashing_func, key_equal_fn);
	hash_t hash;
	hash.set_empty_key(-1);
	hash.set_deleted_key(-2);
	double before = get_time();
	double after;
	for(int64_t i=0 ; i<MAXMIZE; i+=1){
		int64_t r = rand()%arr_max;
		hash.insert(hash_t::value_type(arr[r], arr[r]));
		arr[r] = arr[arr_max-1];
		arr_max-=1;
	}
	after = get_time();
    printf("Insert : %f\n", after-before);
    before = after;
	hash_t::const_iterator it;
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

//load_factor = size / bucket_count