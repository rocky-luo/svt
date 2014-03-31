#include "test_odb.h"

int main(void) {
	if (!parse_path("nginx-1.0.15"))
		printf("i can make it\n");
	return 0;
}
