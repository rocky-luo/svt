#include "hash.h"

int main(void)
{
	unsigned char *a = "frist/rocky/are";
	unsigned char sha1[20], sha[41];
	svt_sha1sum(a,sha1);
	int i;
	for (i = 0; i < 20; i++)
		printf("%x", sha1[i]);
	printf("\n");
	for (i=0; i<20; i++)
		sprintf(&sha[2*i],"%x",sha1[i]);
	//strncpy(sha, sha1, 20);
	//sha[20] = '\n';
	printf("%s\n", sha);
	return 0;
}
