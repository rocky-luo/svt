#include "common.h"
#include "odb.h"

uint8_t ROOTPATH[100] = "\0";
uint8_t OBJECTSPATH[100] = "\0";

int32_t parse_path(uint8_t *path) 
{
	object_list_t *list_entry;
	object_list_t **temp;
	getcwd(ROOTPATH, 100);
	strcat(ROOTPATH, "/");
	strcat(ROOTPATH, path);
 	strcat(OBJECTSPATH,ROOTPATH);
	strcat(OBJECTSPATH,"/objects/");
	svt_mkdir(OBJECTSPATH);
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
	temp = add_commit2list("commit this", &list_entry);
	creat_object_list(path, temp); 
	return 0;
}

object_list_t **creat_object_list(uint8_t *dir, object_list_t **p)
{
	DIR *dp;
	struct dirent *entry;
	struct stat statbuf;
	//object_t *o;
	object_list_t **temp;
	object_t *tree;
	object_t *blob;
	if ((dp = opendir(dir)) == NULL) {
		fprintf(stderr, "cannot open dir:%s\n", dir);
		return NULL;	
	}
	temp = add_tree2list(dir, p);
	chdir(dir);
	while((entry = readdir(dp)) != NULL) {
		lstat(entry->d_name, &statbuf);
		if (S_ISDIR(statbuf.st_mode)) {
			if (strcmp(".", entry->d_name) ==0 ||
				strcmp( "..", entry->d_name) ==0 ||
					strcmp( "objects", entry->d_name) ==0)
				continue;
			temp = creat_object_list(entry->d_name, temp); 
		}
		else {
			temp = add_blob2list(entry->d_name, temp);
			
		}
	}
	store_tree(*p);	
	chdir("..");
	return &((*p)->rbrother);
}

object_list_t *init_object_list(void)
{
	object_list_t *pol;
	if ((pol = malloc(sizeof(object_list_t))) == NULL) {
		printf("init_object_list fail\n");
		return NULL;
	}	
	pol->item = NULL;
	pol->rbrother = NULL;
	pol->child = NULL;
	return pol;
}

int32_t creat_commit(uint8_t *dir, object_list_t *pol)
{
	
	pol->item = init_commit(dir);
	pol->rbrother = NULL;
	pol->child = NULL;
	return 0;
}

object_t *init_commit(uint8_t *name)
{
	object_t *pc;
	if ((pc = malloc(sizeof(object_t))) == NULL) {
		printf("init_commit fail!");
		return NULL;
	}
	pc->type = COMMIT;
	strcpy(pc->name, name);
	return pc;
}

object_t *init_tree(uint8_t *name)
{
	object_t *pc;
	if ((pc = malloc(sizeof(object_t))) == NULL) {
		printf("init_blob fail!");
		return NULL;
	}
	pc->type = TREE;
	strcpy(pc->name, name);
	return pc;
}

object_t *init_blob(uint8_t *name)
{
	object_t *pc;
	if ((pc = malloc(sizeof(object_t))) == NULL) {
		printf("init_blob fail!");
		return NULL;
	}
	pc->type = BLOB;
	strcpy(pc->name, name);
	return pc;
}

object_list_t **add_commit2list(uint8_t *name, object_list_t **entry)
{
	*entry = init_object_list();
	(*entry)->item = init_commit(name);
	return &((*entry)->child);
}
object_list_t **add_tree2list(uint8_t *name, object_list_t **p)
{
	object_list_t **a;
	*p = init_object_list();
	(*p)->item = init_tree(name);
	a = &((*p)->child);
	return a;
	 
} 

object_list_t **add_blob2list(uint8_t *name, object_list_t **p)
{
	object_list_t **a;
	*p = init_object_list();
	(*p)->item = init_blob(name);
	a= &((*p)->rbrother);
	store_blob((*p)->item); 
	return a;
}

int32_t store_blob(object_t *obj)
{
	if (0 != svt_sha1sum(obj->name, obj->oid.key))
		fprintf(stderr, "svt_sha1sum in store_blob erro\n");
	key2str(obj->oid.key, obj->oid.strkey);
	
	uint8_t store[400] = "\0";
	strcat(store, OBJECTSPATH);
	strcat(store, obj->oid.strkey);
	svt_cp(obj->name, store);
	return 0;
}

int32_t svt_cp(uint8_t *src, uint8_t *dest)
{
	uint8_t block[4096];
	int32_t in, out;
	int32_t nread, nwrite;
	in = open(src, O_RDONLY);
	out = open(dest, O_WRONLY|O_CREAT|O_TRUNC, S_IRUSR|S_IWUSR);
	while ((nread = read(in, block, sizeof(block))) > 0)
		nwrite = write(out, block, nread);
	close(in);
	close(out);	
	return 0;
}

int32_t store_tree(object_list_t *tree)
{
	uint8_t path[400] = "\0";
	uint8_t realpath[400] = "\0";
	strcat(path, OBJECTSPATH);
	strcat(path, "temp_treetohash");
	object_list_t *u = tree->child;
	int32_t treefile;
	uint32_t nname;
	treefile = open(path, O_WRONLY|O_CREAT|O_TRUNC, S_IRUSR|S_IWUSR);
	for(u = tree->child; u != NULL; u = u->rbrother) {
		if (SHA1STRLEN != write(treefile, u->item->oid.strkey, SHA1STRLEN))
			fprintf(stderr, "write erro in store_tree\n");
		if (u->item->type == BLOB)
			if (write(treefile, "blob", 4) != 4)
				fprintf(stderr, "write erro in store_tree\n");
		if (u->item->type == TREE)
			if (write(treefile, "tree", 4) != 4)
				fprintf(stderr, "write erro in store_tree\n");
		/*TODO COMMIT*/
		nname = strlen(u->item->name);
		if (nname != write(treefile, u->item->name, nname))
			fprintf(stderr, "write erro in store_tree\n");
		if (1 != write(treefile, "\n", 1))
			fprintf(stderr, "write erro in store_tree\n");
	}
/*
	if (1 != write(treefile, "\0", 1))
		fprintf(stderr, "write erro in store_tree\n");
*/
	close(treefile);
	if (0 != svt_sha1sum(path, tree->item->oid.key))
		fprintf(stderr, "svt_sha1sum in store_tree erro\n");
	key2str(tree->item->oid.key, tree->item->oid.strkey);
	strcat(realpath, OBJECTSPATH);
	strcat(realpath, tree->item->oid.strkey);
	rename(path, realpath);
	return 0;
	
}
