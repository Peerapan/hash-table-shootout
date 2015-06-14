#include <inttypes.h>
#include <google/sparse_hash_map>
typedef google::sparse_hash_map<int64_t, int64_t> hash_t;
typedef google::sparse_hash_map<const char *, int64_t> str_hash_t;
hash_t hash;
str_hash_t str_hash;
#define SETUP hash.set_deleted_key(-1); str_hash.set_deleted_key("");
#define INSERT_INT_INTO_HASH(key, value) hash.insert(hash_t::value_type(key, value))
#define DELETE_INT_FROM_HASH(key) hash.erase(key)
#define INSERT_STR_INTO_HASH(key, value) str_hash.insert(str_hash_t::value_type(key, value))
#define DELETE_STR_FROM_HASH(key) str_hash.erase(key)
#define CLEAR

void BulkInsertIntIntoHash(int key[],int value[],int BULK_NO){
    
    for(int i=0; i<BULK_NO; i++)
    {
        INSERT_INT_INTO_HASH(key[i], value[i]);
    }
}

void BulkDeleteIntFromHash(int key[], int BULK_NO){
    
    for(int i=0; i<BULK_NO; i++) {
        DELETE_INT_FROM_HASH(key[i]);
    }
}

void BulkInsertStrIntoHash(char* key[],int value[],int BULK_NO){
    
    for(int i=0; i<BULK_NO; i++) {
        INSERT_STR_INTO_HASH(key[i], value[i]);
    }
}

void BulkDeleteStrFromHash(char* key[], int BULK_NO){
    
    for(int i=0; i<BULK_NO; i++) {
        DELETE_STR_FROM_HASH(key[i]);
    }
}

#include "template_bulk.c"
