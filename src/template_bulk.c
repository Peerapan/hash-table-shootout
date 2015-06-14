#include <sys/time.h>
#include <sys/types.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <math.h>

double get_time(void)
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return tv.tv_sec + (tv.tv_usec / 1000000.0);
}

char * new_string_from_integer(int num)
{
    int ndigits = num == 0 ? 1 : (int)log10(num) + 1;
    char * str = (char *)malloc(ndigits + 1);
    sprintf(str, "%d", num);
    return str;
}

int main(int argc, char ** argv)
{
    int num_keys = atoi(argv[1]);
    int i, j, value = 0;
    
    int BULK_NO = atoi(argv[3]);
    
    if(argc <= 2)
        return 1;
    
    SETUP
    
    double before = get_time();
    
    if(!strcmp(argv[2], "sequential"))
    {
        for(i = 0; i < num_keys; ){
            int setIntKey[BULK_NO], setIntValue[BULK_NO];
            for(j = 0; j < BULK_NO && i < num_keys; j++, i++){
                setIntKey[j] = i;
                setIntValue[j] = value;
            }
            BulkInsertIntIntoHash(setIntKey, setIntValue, j);
            //INSERT_INT_INTO_HASH(i, value);
        }
    }
    
    else if(!strcmp(argv[2], "random"))
    {
        srandom(1); // for a fair/deterministic comparison
        for(i = 0; i < num_keys; ){
            int setIntKey[BULK_NO], setIntValue[BULK_NO];
            for(j = 0; j < BULK_NO && i < num_keys; j++, i++){
                setIntKey[j] = (int)random();
                setIntValue[j] = value;
            }
            BulkInsertIntIntoHash(setIntKey, setIntValue, j);
            //INSERT_INT_INTO_HASH((int)random(), value);
        }
    }
    
    else if(!strcmp(argv[2], "delete"))
    {
        {
            int setIntKey[num_keys], setIntValue[num_keys];
            // Use Bulk Insert
            for(i = 0; i < num_keys; i++){
                setIntKey[i] = i;
                setIntValue[i] = value;
            }
            BulkInsertIntIntoHash(setIntKey, setIntValue, i);
        }
        
        before = get_time();
        for(i = 0; i < num_keys; ){
            int setIntKey[BULK_NO];
            for(j = 0; j < BULK_NO && i < num_keys; j++, i++){
                setIntKey[j] = i;
            }
            BulkDeleteIntFromHash(setIntKey, j);
            //DELETE_INT_FROM_HASH(i);
        }
    }
    
    else if(!strcmp(argv[2], "sequentialstring"))
    {
        for(i = 0; i < num_keys; ){
            char* setStrKey[BULK_NO];
            int setIntValue[BULK_NO];
            for(j = 0; j < BULK_NO && i < num_keys; j++, i++){
                setStrKey[j] = new_string_from_integer(i);
                setIntValue[j] = value;
            }
            BulkInsertStrIntoHash(setStrKey, setIntValue, j);
            //INSERT_STR_INTO_HASH(new_string_from_integer(i), value);
        }
    }
    
    else if(!strcmp(argv[2], "randomstring"))
    {
        srandom(1); // for a fair/deterministic comparison
        for(i = 0; i < num_keys; ){
            char* setStrKey[BULK_NO];
            int setIntValue[BULK_NO];
            for(j = 0; j < BULK_NO && i < num_keys; j++, i++){
                setStrKey[j] = new_string_from_integer((int)random());
                setIntValue[j] = value;
            }
            BulkInsertStrIntoHash(setStrKey, setIntValue, j);
            //INSERT_STR_INTO_HASH(new_string_from_integer((int)random()), value);
        }
    }
    
    else if(!strcmp(argv[2], "deletestring"))
    {
        {
            char* setStrKey[num_keys];
            int setIntValue[num_keys];
            // Use Bulk insert
            for(i = 0; i < num_keys; i++){
                setStrKey[i] = new_string_from_integer(i);
                setIntValue[i] = value;
            }
            BulkInsertStrIntoHash(setStrKey, setIntValue, i);
        }
        
        before = get_time();
        for(i = 0; i < num_keys; ){
            char* setStrKey[BULK_NO];
            for(j = 0; j < BULK_NO && i < num_keys; j++, i++){
                setStrKey[j] = new_string_from_integer((int)random());
            }
            BulkDeleteStrFromHash(setStrKey, j);
            //DELETE_STR_FROM_HASH(new_string_from_integer(i));
        }
        
    }
    
    double after = get_time();
    printf("%f\n", after-before);
    fflush(stdout);
    CLEAR
    sleep(1000000);
}
