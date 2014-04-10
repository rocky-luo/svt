#ifndef _ODB_H__
#define _ODB_H__

#include "hash.h"

typedef struct blob_s  blob_t;
struct blob_s {
	uint8_t name[50];
	sha1key bid;
};

typedef struct tree_s  tree_t;
struct tree_s {
	uint8_t name[50];
	sha1key tid;
};

typedef struct commitinfo_s  commitinfo_t;
struct commitinfo_s {
	int8_t *date;
	int8_t *author;
};

typedef struct commit_s  commit_t;
struct commit_s {
	sha1key cid;
	commitinfo_t info;
	commit_t *parent;
	commit_t *child;
};

enum otype {TREE, BLOB, COMMIT};

typedef struct object_s  object_t;
struct object_s {
	enum otype type;
	sha1key oid;
	uint8_t name[50];
	void *real;
};

typedef struct object_list_s  object_list_t;
struct object_list_s {
	object_t *item;
	object_list_t *rbrother;
	object_list_t *child;
};

int32_t parse_path(uint8_t *path);
object_list_t **creat_object_list(uint8_t *dir, object_list_t **p);
object_list_t *init_object_list(void);
int32_t creat_commit(uint8_t *dir, object_list_t *pol);
object_t *init_commit(uint8_t *name);
object_t *init_tree(uint8_t *name);
object_t *init_blob(uint8_t *name);
object_list_t **add_commit2list(uint8_t *name, object_list_t **entry);
object_list_t **add_tree2list(uint8_t *name, object_list_t **p);
object_list_t **add_blob2list(uint8_t *name, object_list_t **p);
int32_t store_blob(object_t *obj);
int32_t svt_cp(uint8_t *src, uint8_t *dest);
int32_t store_tree(object_list_t *tree);
	
#endif
