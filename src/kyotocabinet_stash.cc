#include <kcstashdb.h>
#include <string>
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
#include "template.c"