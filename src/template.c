#include <time.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <math.h>
#include <limits.h>
#include <sys/time.h>
#include <sys/types.h>

typedef struct StringContainer{
    size_t stringLength;
    const char* keyOriginal;
    const char* keyInternalized;
} StringContainer;

int* g_intKeyArray = NULL;
int* g_intBadKeyArray = NULL;
StringContainer* g_charKeyArray = NULL;
StringContainer* g_charBadKeyArray = NULL;

double get_time(void){
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return tv.tv_sec + (tv.tv_usec / 1000000.0);
}

char * new_string_from_integer(int num){
    int ndigits = num == 0 ? 1 : (int)log10(num) + 1;
    char * str = (char *)malloc(ndigits + 1);
    sprintf(str, "%d", num);
    return str;
}

int random_in_range (unsigned int min, unsigned int max){
    int base_random = rand();
    if (RAND_MAX == base_random) return random_in_range(min, max);
    int range       = max - min,
    remainder   = RAND_MAX % range,
    bucket      = RAND_MAX / range;
    if (base_random < RAND_MAX - remainder) {
        return min + base_random/bucket;
    } else {
        return random_in_range (min, max);
    }
}

#define CONVERT_INT_AND_INSERT_STR_INTO_HASH(key, value) do { \
int ndigits = key == 0 ? 1 : (int)log10(key) + 1; \
int buffer_size = ndigits+1; \
char str[buffer_size]; \
snprintf(str, buffer_size, "%d", key); \
INSERT_STR_INTO_HASH(str, value); \
} while(0)

#define CONVERT_INT_AND_DELETE_STR_FROM_HASH(key) do { \
int ndigits = key == 0 ? 1 : (int)log10(key) + 1; \
int buffer_size = ndigits+1; \
char str[buffer_size]; \
snprintf(str, buffer_size, "%d", key); \
DELETE_STR_FROM_HASH(str); \
} while(0)

void InitInts(int num_keys){
    int i;
    g_intKeyArray = (int*)calloc(num_keys,sizeof(int));
    g_intBadKeyArray = (int*)calloc(num_keys,sizeof(int));
    size_t current_key_index = 0;
    size_t current_badkey_index = 0;
    for(i = 0; i < num_keys*2; i+=1){
        int key;
        int which_case = i % 4;
        int should_insert;
        switch(which_case){
            case 0:
            {
                key = random_in_range(0,INT_MAX/4);
                should_insert = 1;
                break;
            }
            case 1:
            {
                key = random_in_range(INT_MAX/4+1,INT_MAX/4*2);
                should_insert = 0;
                break;
            }
            case 2:
            {
                key = random_in_range(INT_MAX/4*2+1,INT_MAX/4*3);
                should_insert = 1;
                break;
            }
            case 3:
            {
                key = random_in_range(INT_MAX/4*3+1,INT_MAX);
                should_insert = 0;
                break;
            }
        }
        if(should_insert){
            g_intKeyArray[current_key_index] = key;
            current_key_index+=1;
        }else{
            g_intBadKeyArray[current_badkey_index] = key;
            current_badkey_index+=1;
        }
    }
    int val = 1;
    for(i = 0; i < num_keys; i+=1){
        INSERT_INT_INTO_HASH(g_intKeyArray[i], val);
    }
}

void InitStrings(int num_keys){
    int i;
    g_charKeyArray = (StringContainer*)malloc(num_keys*sizeof(StringContainer));
    g_charBadKeyArray = (StringContainer*)malloc(num_keys*sizeof(StringContainer));
    size_t current_key_index = 0;
    size_t current_badkey_index = 0;
    for(i = 0; i < num_keys*2; i+=1){
        int key;
        int which_case = i % 4;
        int should_insert;
        switch(which_case)
        {
            case 0:
            {
                key = random_in_range(0,INT_MAX/4);
                should_insert = 1;
                break;
            }
            case 1:
            {
                key = random_in_range(INT_MAX/4+1,INT_MAX/4*2);
                should_insert = 0;
                break;
            }
            case 2:
            {
                key = random_in_range(INT_MAX/4*2+1,INT_MAX/4*3);
                should_insert = 1;
                break;
            }
            case 3:
            {
                key = random_in_range(INT_MAX/4*3+1,INT_MAX);
                should_insert = 0;
                break;
            }
            default:
            {
                fprintf(stderr, "Unexpected case\n");
                break;
            }
        }
        int ndigits = key == 0 ? 1 : (int)log10(key) + 1;
        int buffer_size = ndigits+1;
        char str[buffer_size];
        snprintf(str, buffer_size, "%d", key);
        if(should_insert){
            g_charKeyArray[current_key_index].keyOriginal = strdup(str);
            g_charKeyArray[current_key_index].stringLength = strlen(str);
            current_key_index+=1;
        }else{
            g_charBadKeyArray[current_badkey_index].keyOriginal = strdup(str);
            g_charBadKeyArray[current_badkey_index].stringLength = strlen(str);
            current_badkey_index+=1;
        }
    }
    for(i = 0; i < num_keys; i+=1){
        g_charKeyArray[i].keyInternalized = InsertStrIntoHash(g_charKeyArray[i].keyOriginal, 1);
    }
}

#define NUM_ITERATIONS_MULTIPLE 1

int main(int argc, char ** argv)
{
    int num_keys = atoi(argv[1]);
    int i, value = 0;
    
    if(argc <= 2)
        return 1;
    
    SETUP(num_keys);
    srand(1);
    
    if(!strcmp(argv[2], "randomgetgood")){
        InitInts(num_keys);
    }else if(!strcmp(argv[2], "randomstringgetgood")){
        InitStrings(num_keys);
    }else if(!strcmp(argv[2], "randomgetbad")){
        InitInts(num_keys);
    }else if(!strcmp(argv[2], "randomstringgetbad")){
        InitStrings(num_keys);
    }else if(!strcmp(argv[2], "randomset")){
        InitInts(num_keys);
    }else if(!strcmp(argv[2], "randomstringsetbest")){
        InitStrings(num_keys);
    }else{
        fprintf(stderr, "Test name not implemented. Bailing...\n");
        return 1;
    }
    
    double before = get_time();
    
    if(!strcmp(argv[2], "sequential")){
        for(i = 0; i < num_keys; i+=1){
            INSERT_INT_INTO_HASH(i, value);
        }
    }else if(!strcmp(argv[2], "random")){
        srandom(1);
        for(i = 0; i < num_keys; i+=1){
            INSERT_INT_INTO_HASH((int)random(), value);
        }
    }else if(!strcmp(argv[2], "delete")){
        for(i = 0; i < num_keys; i+=1){
            INSERT_INT_INTO_HASH(i, value);
        }
        before = get_time();
        for(i = 0; i < num_keys; i+=1){
            DELETE_INT_FROM_HASH(i);
        }
    }else if(!strcmp(argv[2], "sequentialstring")){
        for(i = 0; i < num_keys; i+=1){
            INSERT_STR_INTO_HASH(new_string_from_integer(i), value);
        }
    }else if(!strcmp(argv[2], "randomstring")){
        srandom(1);
        for(i = 0; i < num_keys; i+=1){
            INSERT_STR_INTO_HASH(new_string_from_integer((int)random()), value);
        }
    }else if(!strcmp(argv[2], "deletestring")){
        for(i = 0; i < num_keys; i+=1){
            INSERT_STR_INTO_HASH(new_string_from_integer(i), value);
        }
        before = get_time();
        for(i = 0; i < num_keys; i+=1){
            DELETE_STR_FROM_HASH(new_string_from_integer(i));
        }
    }else if(!strcmp(argv[2], "randomgetgood")){
        for(i = 0; i < num_keys * NUM_ITERATIONS_MULTIPLE; i+=1){
            int random_index = random_in_range(0, num_keys-1);
            int key = g_intKeyArray[random_index];
            int exists = ExistsInIntHash(key);
            if(!exists){
                fprintf(stderr, "Warning: expected to find value for key: %d\n", key);
            }
        }
    }else if(!strcmp(argv[2], "randomstringgetgood")){
        for(i = 0; i < num_keys * NUM_ITERATIONS_MULTIPLE; i+=1){
            int random_index = random_in_range(0, num_keys-1);
            const char* key = g_charKeyArray[random_index].keyOriginal;
            int exists = ExistsInStrHash(key);
            if(!exists){
                fprintf(stderr, "Warning: expected to find value for key: %s\n", key);
            }
        }
    }else if(!strcmp(argv[2], "randomgetbad")){
        for(i = 0; i < num_keys * NUM_ITERATIONS_MULTIPLE; i+=1){
            int random_index = random_in_range(0, num_keys-1);
            int key = g_intBadKeyArray[random_index];
            int exists = ExistsInIntHash(key);
            if(exists){
                fprintf(stderr, "Warning: didn't expect to find value for key: %d\n", key);
            }
        }
    }else if(!strcmp(argv[2], "randomstringgetbad")){
        for(i = 0; i < num_keys * NUM_ITERATIONS_MULTIPLE; i+=1){
            int random_index = random_in_range(0, num_keys-1);
            const char* key = g_charBadKeyArray[random_index].keyOriginal;
            int exists = ExistsInStrHash(key);
            if(exists){
                fprintf(stderr, "Warning: didn't expect to find value for key: %s\n", key);
            }
        }
    }else if(!strcmp(argv[2], "randomset")){
        for(i = 0; i < num_keys * NUM_ITERATIONS_MULTIPLE; i+=1){
            int random_index = random_in_range(0, num_keys-1);
            int key = g_intKeyArray[random_index];
            SetIntIntoHash(key, i);
        }
    }else if(!strcmp(argv[2], "randomstringsetbest")){
        for(i = 0; i < num_keys * NUM_ITERATIONS_MULTIPLE; i+=1){
            int random_index = random_in_range(0, num_keys-1);
            const char* key = g_charKeyArray[random_index].keyInternalized;
            size_t length = g_charKeyArray[random_index].stringLength;
            SetStringIntoHash(key, i, length);
        }
    }
    
    double after = get_time();
    printf("%f\n", after-before);
    fflush(stdout);
    sleep(1000000);
}
