#include "stdio.h"

#include "mdirent.h"

#ifndef NULL
#define NULL 0
#endif

int main(int argc, char *argv[]) {
	char dir[256];
	if (argc != 1) {
		printf("currently only supported param == 1");
	}

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
		printf("Directory: %s\n", dir);
	} else {
		// 如果没有找到 '/', 说明路径没有目录部分
		printf("No directory in path\n");
	}

	DIR d;               // 目录结构体
	struct dirent entry; // 当前目录项
	int ret;

	// 打开目录
	ret = opendir(dir, &d);
	if (ret != 0) {
		printf("Failed to open directory: %s\n", dir);
		return;
	}

	// 遍历并打印目录中的所有文件名
	while (1) {
		// 读取下一个目录项
		readdir(&d, &entry);

		// 如果没有更多目录项，退出循环
		if (entry.filename[0] == '\0') {
			break;
		}

		// 打印文件名
		printf("%s\n", entry.filename);
	}

	// 关闭目录
	closedir(&d);
}