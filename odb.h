#ifndef _ODB_H_
#define _ODB_H_
#include "hash/hash.h"
struct blob {
	sha1key bid;
};
struct tree {
	sha1key tid;
	struct tree *tree_list;
	struct blob *blob_list;
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
	struct tree *ft;
}
#endif
