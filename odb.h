#ifndef _ODB_H_
#define _ODB_H_
#include "hash.h"
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>
#include <malloc.h>

struct blob {
	unsigned char name[50];
	sha1key bid;
};
struct tree {
	unsigned char name[50];
	sha1key tid;
};
struct commitinfo {
	char *date;
	char *author;
};
struct commit {
	sha1key cid;
	struct commitinfo inf;
	struct commit *parent;
	struct commit *child;
};

enum otype {TREE, BLOB, COMMIT};
struct object {
	enum otype type;
	sha1key oid;
	unsigned char name[50];
	void *real;
};
struct object_list {
	struct object *item;
	struct object_list *rbrother;
	struct object_list *child;
};

int parse_path(unsigned char *path);
int creat_object_list(unsigned char *dir, struct object_list **p);
struct object_list *init_object_list(void);
int creat_commit(unsigned char *dir, struct object_list *pol);
struct object *init_commit(unsigned char *name);
struct object *init_tree(unsigned char *name);
struct object *init_blob(unsigned char *name);
struct object_list **add_commit2list(unsigned char *name, struct object_list **entry);
struct object_list **add_tree2list(unsigned char *name, struct object_list **p);
struct object_list **add_blob2list(unsigned char *name, struct object_list **p);
	
#endif
