#include <glib.h>
GHashTable * hash;
GHashTable * str_hash;
#define SETUP hash = g_hash_table_new(g_direct_hash, g_direct_equal); \
              str_hash = g_hash_table_new(g_str_hash, g_str_equal);
#define INSERT_INT_INTO_HASH(key, value) g_hash_table_insert(hash, GINT_TO_POINTER(key), &value)
#define DELETE_INT_FROM_HASH(key) g_hash_table_remove(hash, GINT_TO_POINTER(key))
#define INSERT_STR_INTO_HASH(key, value) g_hash_table_insert(str_hash, key, &value)
#define DELETE_STR_FROM_HASH(key) g_hash_table_remove(str_hash, key)
#define CLEAR

static inline const char* InsertStrIntoHash(const char* key, int value)
{
	INSERT_STR_INTO_HASH( (gpointer) key, value);
	return key;
}
static inline int ExistsInIntHash(int key)
{
	if ( !g_hash_table_lookup (hash, GINT_TO_POINTER(key)) ){
		return 0;
	}else{
		return 1;
	}
	
}
static inline int ExistsInStrHash(const char* key)
{
	if ( !g_hash_table_lookup (str_hash, (gpointer) key) ){
		return 0;
	}else{
		return 1;
	}
}
static inline void SetIntIntoHash(int key, int value)
{
	g_hash_table_insert(hash, GINT_TO_POINTER(key), &value);
}
static inline void SetStringIntoHash(const char* key, int value, size_t length)
{
	g_hash_table_insert(str_hash,(gpointer) key, &value);
}

#include "template_access.c"
