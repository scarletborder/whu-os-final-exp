// clang-format off
#include "stdio.h"
#include "string.h"
#include "unistd.h"
#include "keywise.h"

// clang-format on

int main(int argc, char *argv[]) {
	if (argc != 2) {
		printf("ERROR need a file");
		return 1;
	}
	char filepath[256] = "";
	get_full_path(argv[1], filepath);

	struct stat f_stat;
	int ret = stat(filepath, &f_stat);

	if (ret != 0 || f_stat.st_mode != 0100000) {
		printf("ERROR can not get target file or not a regular file: %s\n", filepath);
	}

	int fd = open(filepath, O_RDWR);
	if (fd == 0) {
		printf("can nor open file: %s\n", filepath);
	}

	char buf[4096];
	ret = read(fd, buf, 4090);

	if (ret == -1) {
		printf("ERROR can not read file: %s\n", filepath);
	} else {
		printf("read %d bytes from %s\n", ret, filepath);
	}

	_strcpy(buf, "fixed content will be written to fgile");
	int length = strlen(buf);
	ret        = write(fd, buf, length + 1);
	if (ret == -1) {
		printf("ERROR can not write file: %s\n", filepath);
	} else {
		printf("write %d bytes from %s\n", ret, filepath);
	}
	return 0;
}