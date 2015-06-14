#include <kcpolydb.h>
#include <string>
typedef kyotocabinet::HashDB hash_t;
typedef kyotocabinet::HashDB str_hash_t;
hash_t hash;
str_hash_t str_hash;
#define SETUP hash.open("hash_access.kch", hash_t::OWRITER | hash_t::OTRUNCATE); str_hash.open("str_hash_access.kch", str_hash_t::OWRITER | str_hash_t::OCREATE);
#define INSERT_INT_INTO_HASH(key, value) hash.set(std::to_string(key), std::to_string(value))
#define DELETE_INT_FROM_HASH(key) hash.remove(std::to_string(key))
#define INSERT_STR_INTO_HASH(key, value) str_hash.set( key, std::to_string(value))
#define DELETE_STR_FROM_HASH(key) str_hash.remove(key)
#define CLEAR hash.close(); str_hash.close();

static inline const char* InsertStrIntoHash(const char* key, int value)
{
	INSERT_STR_INTO_HASH(key, value);
	return key;
}
static inline int ExistsInIntHash(int key)
{
	std::string s_key = std::to_string(key);
	std::string s_val;
	if ( !hash.get(s_key, &s_val) ){
		return 0;
	}else{
		return 1;
	}
}
static inline int ExistsInStrHash(const char* key)
{
	std::string s_key = key;
	std::string s_val;
	if ( !str_hash.get(s_key, &s_val) ){
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

#include "template_access.c"