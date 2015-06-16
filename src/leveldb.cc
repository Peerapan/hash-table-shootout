#include <stdio.h>
#include "leveldb/db.h"
std::string kDBPath = "/tmp/leveldb";
leveldb::DB* db;
#define SETUP leveldb::Options options; options.create_if_missing = true; \
leveldb::DB::Open(options, kDBPath, &db);
#define INSERT_INT_INTO_HASH(key, value) db->Put(leveldb::WriteOptions(), std::to_string(key), std::to_string(value));
#define DELETE_INT_FROM_HASH(key) db->Delete(leveldb::WriteOptions(), std::to_string(key));
#define INSERT_STR_INTO_HASH(key, value) db->Put(leveldb::WriteOptions(), key, std::to_string(value));
#define DELETE_STR_FROM_HASH(key) db->Delete(leveldb::WriteOptions(), key);
#define CLEAR delete db;
static inline const char* InsertStrIntoHash(const char* key, int value)
{
    INSERT_STR_INTO_HASH(key, value);
    return key;
}
static inline int ExistsInIntHash(int key)
{
    std::string value;
    db->Get(leveldb::ReadOptions(), std::to_string(key), &value);
    
    if(value.c_str() == "")
    {
        return 0;
    }else{
        return 1;
    }
    
}
static inline int ExistsInStrHash(const char* key)
{
    std::string value;
    db->Get(leveldb::ReadOptions(), key, &value);
    
    if ( value.c_str() == ""){
        return 0;
    }else{
        return 1;
    }
}
static inline void SetIntIntoHash(int key, int value)
{
    INSERT_INT_INTO_HASH(key, value);
}
static inline void SetStringIntoHash(const char* key, int value, size_t length)
{
    INSERT_STR_INTO_HASH(key, value);
}

#include "template.c"