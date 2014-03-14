#ifndef _ODB_H_
#define _ODB_H_
#include "hash.h"
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
	void *real
}
struct object_list {
	struct object *item;
	struct object *rbrother;
	struct object *child;
}
	
#endif
