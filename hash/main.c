#include "svt_hash.h"

int main(int argc, char **argv)
{
	unsigned char sha1sum[20];
	int i;
	if(!svt_sha1sum("/home/rocky/svt/yes.txt", sha1sum))
		printf("i make it!\n");
	for(i=0;i < 20; i++)
		printf("%02x", sha1sum[i]);
	printf("\n");
	return 0;
}
