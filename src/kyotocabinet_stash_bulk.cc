#include <kcstashdb.h>
#include <string>
#include <map>
#include <vector>

typedef kyotocabinet::StashDB hash_t;
typedef kyotocabinet::StashDB str_hash_t;
hash_t hash;
str_hash_t str_hash;
#define SETUP hash.open("*", hash_t::OWRITER | hash_t::OCREATE); str_hash.open("*", str_hash_t::OWRITER | str_hash_t::OCREATE);
#define INSERT_INT_INTO_HASH(key, value) hash.set(std::to_string(key), std::to_string(value))
#define DELETE_INT_FROM_HASH(key) hash.remove(std::to_string(key))
#define INSERT_STR_INTO_HASH(key, value) str_hash.set( key, std::to_string(value))
#define DELETE_STR_FROM_HASH(key) str_hash.remove(key)
#define CLEAR

void BulkInsertIntIntoHash(int setIntKey[],int setIntValue[],int BULK_NO){
    std::map<std::string, std::string> bulkData;
    int i;
    
    for(i = 0; i < BULK_NO; i++){
        bulkData[std::to_string(setIntKey[i])] = std::to_string(setIntValue[i]);
    }
    
    hash.set_bulk(bulkData);
}

void BulkDeleteIntFromHash(int setIntKey[], int BULK_NO){
    std::vector<std::string> bulkRemover;
    int i;
    
    for(i = 0; i < BULK_NO; i++){
        bulkRemover.push_back(std::to_string(setIntKey[i]));
    }
    
    hash.remove_bulk(bulkRemover);
}

void BulkInsertStrIntoHash(char* setStrKey[],int setIntValue[],int BULK_NO){
    std::map<std::string, std::string> bulkData;
    int i;
    
    for(i = 0; i < BULK_NO; i++){
        bulkData[setStrKey[i]] = std::to_string(setIntValue[i]);
    }
    
    hash.set_bulk(bulkData);
}

void BulkDeleteStrFromHash(char* setStrKey[], int BULK_NO){
    std::vector<std::string> bulkRemover;
    int i;
    
    for(i = 0; i < BULK_NO; i++){
        bulkRemover.push_back(setStrKey[i]);
    }
    
    hash.remove_bulk(bulkRemover);
}

#include "template_bulk.c"