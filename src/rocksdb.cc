#include <string>
#include "rocksdb/db.h"
#include "rocksdb/slice.h"
#include "rocksdb/options.h"
std::string kDBPath = "/mnt/ramdisk/";
#define SETUP rocksdb::DB* db; \
rocksdb::Options options; \
options.create_if_missing = true; \
options.wal_bytes_per_sync = 0; \
options.max_total_wal_size = 0; \
options.WAL_ttl_seconds = 0; \
options.WAL_size_limit_MB = 0; \
rocksdb::WriteOptions write; \
write.disableWAL = true; \
rocksdb::DB::Open(options, kDBPath, &db);
#define INSERT_INT_INTO_HASH(key, value) db->Put(write, std::to_string(key), std::to_string(value));
#define DELETE_INT_FROM_HASH(key) db->Delete(write, std::to_string(key));
#define INSERT_STR_INTO_HASH(key, value) db->Put(write, key, std::to_string(value));
#define DELETE_STR_FROM_HASH(key) db->Delete(write, key);
#define CLEAR delete db;
static inline const char* InsertStrIntoHash(const char* key, int value)
{
    INSERT_STR_INTO_HASH(key, value);
    return key;
}
static inline int ExistsInIntHash(int key)
{
    std::string value;
    
    try{
        rocksdb::Status s = db->Get(rocksdb::ReadOptions(), std::to_string(key),&value);
        if(s.ok())
            return 1;
    }catch (const std::exception &e){
        
    }
    return 0;
    
}
static inline int ExistsInStrHash(const char* key)
{
    std::string value;
    
    try{
        rocksdb::Status s = db->Get(rocksdb::ReadOptions(), key,&value);
        if(s.ok())
            return 1;
    }catch (const std::exception &e){
        
    }
    return 0;
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