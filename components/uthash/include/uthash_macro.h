#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "uthash.h"

// Macro to create a generic hash table add/store function
// rewrite with variable arguments, detects data types and automatically choose functions
#define HASHTABLE_ADD(SRCTABLE, NVSKEY_ARG, NVSVALUE_ARG) \
do { \
    typeof(*(SRCTABLE)) *s; \
    HASH_FIND_STR(SRCTABLE, NVSKEY_ARG, s); \
    if (s == NULL) { \
        s = malloc(sizeof(typeof(*(SRCTABLE)))); \
        strcpy(s->nvskey, NVSKEY_ARG); \
        strcpy(s->nvsvalue, NVSVALUE_ARG); \
        HASH_ADD_STR(SRCTABLE, nvskey, s); \
    } \
} while(0)
// Use the macro for different types of hashtables
//HASH_ADD_STORE(httpd_uri_hashtable_t, uri_table, "key1", "value1");
#define HASHTABLE_FIND(SRCTABLE, NVSKEY) ({ \
    typeof(*(SRCTABLE)) *s; \
    HASH_FIND_STR(SRCTABLE, NVSKEY, s); \
    s ? s->nvsvalue : NULL; \
})