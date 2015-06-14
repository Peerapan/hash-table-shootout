#include <stdio.h>
#include "leveldb/db.h"

std::string kDBPath = "/tmp/leveldb_simple_example2";

leveldb::DB* db;

#define SETUP leveldb::Options options; options.create_if_missing = true; \
    leveldb::DB::Open(options, kDBPath, &db);


#define INSERT_INT_INTO_HASH(key, value) db->Put(leveldb::WriteOptions(), std::to_string(key), std::to_string(value));
#define DELETE_INT_FROM_HASH(key) db->Delete(leveldb::WriteOptions(), std::to_string(key));
#define INSERT_STR_INTO_HASH(key, value) db->Put(leveldb::WriteOptions(), key, std::to_string(value));
#define DELETE_STR_FROM_HASH(key) db->Delete(leveldb::WriteOptions(), key);
#define CLEAR delete db;

#include "template.c"