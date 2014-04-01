#include "common.h"
#include "initdir.h"

int svt_mkdir(char *path)
{
	return mkdir(path, S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP|S_IROTH|S_IWOTH);
}
