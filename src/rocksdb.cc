#include <string>
#include "rocksdb/db.h"
#include "rocksdb/slice.h"
#include "rocksdb/options.h"
#include "rocksdb/table.h"
#include "rocksdb/write_batch.h"

std::string kDBPath = "/mnt/ramdisk";
std::string waldir = "/mnt/ramdisk";

#define SETUP rocksdb::DB* db; \
    rocksdb::Options options; \
    options.create_if_missing = true; \
    options.keep_log_file_num = 1; \
    options.wal_bytes_per_sync = 0; \
    options.wal_dir = waldir; \
    options.db_log_dir = waldir; \
    options.max_total_wal_size = 0; \
    options.WAL_ttl_seconds = 0; \
    options.WAL_size_limit_MB = 0; \
    rocksdb::WriteOptions write; \
    write.disableWAL = true; \
    rocksdb::DB::Open(options, kDBPath, &db); \
    rocksdb::WriteBatch batch;

/*#define INSERT_INT_INTO_HASH(key, value) batch.Put(std::to_string(key), std::to_string(value)); \
    db->Put(write, &batch);
#define DELETE_INT_FROM_HASH(key) batch.Delete(std::to_string(key));
#define INSERT_STR_INTO_HASH(key, value) batch.Put(key, value); db->Put(write, &batch);
#define DELETE_STR_FROM_HASH(key) batch.Delete(key);
#define CLEAR delete db;*/

#define INSERT_INT_INTO_HASH(key, value) db->Put(write, std::to_string(key), std::to_string(value));
#define DELETE_INT_FROM_HASH(key) db->Delete(write, std::to_string(key));
#define INSERT_STR_INTO_HASH(key, value) db->Put(write, key, std::to_string(value));
#define DELETE_STR_FROM_HASH(key) db->Delete(write, key);
#define CLEAR delete db;
 

#include "template.c"