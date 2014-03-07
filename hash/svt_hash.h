#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <errno.h>

typedef unsigned int u32;
typedef struct {
        u32  h0,h1,h2,h3,h4;
        u32  nblocks;
        unsigned char buf[64];
 	int  count;
 } SHA1_CONTEXT;

void transform(SHA1_CONTEXT *hd, unsigned char *data);
void sha1_write(SHA1_CONTEXT *hd, unsigned char *inbuf, size_t inlen);
void sha1_final(SHA1_CONTEXT *hd);
int svt_sha1sum(char *filename, unsigned char *sha1sum);
void sha1_init(SHA1_CONTEXT *hd);