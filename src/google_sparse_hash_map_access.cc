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

static inline const char* InsertStrIntoHash(const char* key, int value)
{
	INSERT_STR_INTO_HASH(key, value);
	return key;
}
static inline int ExistsInIntHash(int key)
{
	hash_t::const_iterator value = hash.find (key);
	if ( value == hash.end() ){
		return 0;
	}else{
		return 1;
	}
	
}
static inline int ExistsInStrHash(const char* key)
{
	str_hash_t::const_iterator value = str_hash.find (key);
	if ( value == str_hash.end() ){
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
