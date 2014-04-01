#include "common.h"
#include "odb.h"

int main(int argc, char **argv) {
	if (argc != 2) {
		printf("miss a argc\n");
		return 0;
	}
	if (!parse_path(argv[1]))
		printf("i can make it\n");
	return 0;
}
