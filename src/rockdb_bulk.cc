#include <string>
#include "rocksdb/db.h"
#include "rocksdb/slice.h"
#include "rocksdb/options.h"
#include "rocksdb/table.h"
#include "rocksdb/write_batch.h"

std::string kDBPath = "/mnt/ramdisk";
std::string waldir = "/mnt/ramdisk";
rocksdb::DB* db;
rocksdb::Options options;
rocksdb::WriteOptions write_ss;

#define SETUP options.create_if_missing = true; \
    options.keep_log_file_num = 1; \
    options.wal_bytes_per_sync = 0; \
    options.wal_dir = waldir; \
    options.db_log_dir = waldir; \
    options.max_total_wal_size = 0; \
    options.WAL_ttl_seconds = 0; \
    options.WAL_size_limit_MB = 0; \
    write_ss.disableWAL = true; \
    rocksdb::DB::Open(options, kDBPath, &db);

#define INSERT_INT_INTO_HASH(key, value) db->Put(write_ss, std::to_string(key), std::to_string(value));
#define DELETE_INT_FROM_HASH(key) db->Delete(write_ss, std::to_string(key));
#define INSERT_STR_INTO_HASH(key, value) db->Put(write_ss, key, std::to_string(value));
#define DELETE_STR_FROM_HASH(key) db->Delete(write_ss, key);
#define CLEAR delete db;

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