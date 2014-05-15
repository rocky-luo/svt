#ifndef	_CDS_H_
#define	_CDS_H_

typedef	struct cds_s cds_t;
struct cds_s {
	uint8_t file[100];
	uint8_t objects_dir[100];
	enum {COMMIT}command;
	struct process {
		void *compression_method;
		void *hash_method;
		void *parse_dir_method;
	}method;	
};
#endif
