int main(int argc, int8_t **argv)
{
	if (argc < 2) {
		printf("error:inputs are not enough\n");
		exit(1);
	}
	cds_t ctx;
	memset(&ctx, 0, sizeof(cds_t));
	if (argv[1] == commit){
		ctx.command = COMMIT;
		ctx.method.parse_dir_method = parse_path;
		ctx.method.hash_method = 
	}
	
}
