#include "stdio.h"
#include "string.h"
#include "type.h"
#include "unistd.h"

int main(int argc, char *argv[]) {
	// only accept one arg
	if (argc != 2) {
		printf("ERROR: `mkdir` allows invocation with only one parameter.\n");
		return 1;
	}

	char dir[256];
	// 处理第一个参数即软件路径

	char *full_path  = argv[0]; // 获取程序的完整路径
	char *last_slash = NULL;    // 用于存储最后一个 '/' 的位置

	// 遍历字符串找到最后一个 '/' 字符
	for (char *ptr = full_path; *ptr != '\0'; ptr++) {
		if (*ptr == '/') {
			last_slash = ptr;
		}
	}
	// 如果找到了 '/'，则截取目录部分
	if (last_slash != NULL) {
		// 用指针操作来截取路径

		for (int i = 0; i < last_slash - full_path; i++) {
			dir[i] = full_path[i];
		}
		dir[last_slash - full_path] = '\0'; // 添加字符串结束符
	} else {
		// 如果没有找到 '/', 说明路径没有目录部分
		printf("No directory in path\n");
	}
	if (dir[0] == '\0') { // 根目录'/'
		dir[0] = '/';
		dir[1] = '\0';
	}

	char *target_path = argv[1];
	strcat(dir, target_path);

	int res = mkdir(dir, O_CREAT);
	if (res == -1) {
		printf("ERROR create directory %s fail\n", dir);
		return 1;
	}
	return 0;
}