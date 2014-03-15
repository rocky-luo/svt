#include "odb.h"

int parse_path(unsigned char *path) 
{
	struct object_list *list_entry;
	struct object_list **temp;
	
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
	temp = add_commit2list("first", &list_entry);
	creat_object_list(path, temp); 
	return 0;
}

int creat_object_list(unsigned char *dir, struct object_list **p)
{
	DIR *dp;
	struct dirent *entry;
	struct stat statbuf;
	//struct object *o;
	struct object_list **temp;
	if ((dp = opendir(dir)) == NULL) {
		fprintf(stderr, "cannot open dir:%s\n", dir);
		return -1;	
	}
	temp = add_tree2list(dir, p);
	chdir(dir);
	while((entry = readdir(dp)) != NULL) {
		lstat(entry->d_name, &statbuf);
		if (S_ISDIR(statbuf.st_mode)) {
			if (strcmp(".", entry->d_name) ==0 ||
				strcmp( "..", entry->d_name) ==0)
				continue;
			creat_object_list(entry->d_name, temp); 
		}
		else temp = add_blob2list(entry->d_name, temp);
	}
	chdir("..");
	return 0;
}

struct object_list *init_object_list(void)
{
	struct object_list *pol;
	if ((pol = malloc(sizeof(struct object_list))) == NULL) {
		printf("init_object_list fail\n");
		return NULL;
	}	
	pol->item = NULL;
	pol->rbrother = NULL;
	pol->child = NULL;
	return pol;
}

int creat_commit(unsigned char *dir, struct object_list *pol)
{
	
	pol->item = init_commit(dir);
	pol->rbrother = NULL;
	pol->child = NULL;
	return 0;
}

struct object *init_commit(unsigned char *name)
{
	struct object *pc;
	if ((pc = malloc(sizeof(struct object))) == NULL) {
		printf("init_commit fail!");
		return NULL;
	}
	pc->type = COMMIT;
	strcpy(pc->name, name);
	return pc;
}

struct object *init_tree(unsigned char *name)
{
	struct object *pc;
	if ((pc = malloc(sizeof(struct object))) == NULL) {
		printf("init_blob fail!");
		return NULL;
	}
	pc->type = TREE;
	strcpy(pc->name, name);
	return pc;
}

struct object *init_blob(unsigned char *name)
{
	struct object *pc;
	if ((pc = malloc(sizeof(struct object))) == NULL) {
		printf("init_blob fail!");
		return NULL;
	}
	pc->type = BLOB;
	strcpy(pc->name, name);
	return pc;
}

struct object_list **add_commit2list(unsigned char *name, struct object_list **entry)
{
	*entry = init_object_list();
	(*entry)->item = init_commit(name);
	return &((*entry)->child);
}
struct object_list **add_tree2list(unsigned char *name, struct object_list **p)
{
	struct object_list **a;
	*p = init_object_list();
	(*p)->item = init_tree(name);
	a = &((*p)->child);
	return a;
	 
} 

struct object_list **add_blob2list(unsigned char *name, struct object_list **p)
{
	struct object_list **a;
	*p = init_object_list();
	(*p)->item = init_blob(name);
	a= &((*p)->rbrother);
	return a;
}
