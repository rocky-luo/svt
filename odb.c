#include <dirent.h>
#include <string.h>
#include <malloc.h>
#include "odb.h"
int parse_path(unsigned char *path) 
{
	struct stat s;
	struct object_list *ol;
	/*
	if (lstat(path, &s) < 0) {
		printf("lstat error\n");
		return -1;
	}
	if (!S_ISDIR(s.st_mode)) {
		printf("%s is not a dir!", path);
		return -1;
	}
	*/
	creat_object_list(path, &ol, NULL); 
}

int creat_object_list(unsigned char *dir, struct object_list *parent)
{
	DIR *dp;
	struct dirent *entry;
	struct stat statbuf;
	struct object *o;
	struct object_list *this;
	if ((dp = opendir(dir)) == NULL) {
		fprintf(stderr, "cannot open dir:%s\n", dir);
		return -1;	
	}
	this = add_tree2list(dir, parent->rbrother);
	chdir(dir);
	while((entry = readdir(dp)) != NULL) {
		lstat(entry->d_name, &statbuf);
		if (S_ISDIR(statbuf.st_mode)) {
			if (strcmp(".", entry->d_name) ==0 ||
				strcmp( "..", entry->d_name) ==0)
				continue;
			creat_object_list(entry->d_name, this); 
		}
		else this = add_blob2list(entry->d_name, this->rbrother);
	}
	chdir("..");
	return 0;
}

struct object_list *init_object_list(void)
{
	struct object_list *pol;
	if ((pol = malloc(sizeof(struct object_list))) == NULL) {
		printf("init_object_list fail\n");
		return NULL
	}	
	pol->item = NULL;
	pol->rbrother = NULL;
	pol->child = NULL;
	return pol;
}

int creat_commit(unsigned char *dir, struct object_list *pol)
{
	
	pol->item = init_commit()
	pol->rbrother = NULL;
	pol->child = NULL;
	return 0;
}

struct object *init_commit(void)
{
	struct object *pc;
	if ((pc = malloc(sizeof(struct object))) == NULL) {
		printf("init_commit fail!");
		return NULL;
	}
	pc->otype = COMMIT;
	return pc;
}

struct object *init_tree(unsigned char *name)
{
	struct object *pc;
	if ((pc = malloc(sizeof(struct object))) == NULL) {
		printf("init_commit fail!");
		return NULL;
	}
	pc->otype = TREE;
	strcpy(pc->name, name);
	return pc;
}

struct object_list *add_tree2list(unsigned char *name, struct object_list *p)
{
	p = init_object_list();
	p->item = init_tree();
} 
