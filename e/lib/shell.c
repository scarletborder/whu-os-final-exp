// clang-format off
#include "type.h"
#include "stdio.h"
#include "const.h"
#include "protect.h"
#include "string.h"
#include "fs.h"
#include "proc.h"
#include "tty.h"
#include "console.h"
#include "global.h"
#include "proto.h"

#include "unistd.h"
// clang-format on
#ifndef NULL
#define NULL 0
#endif

PUBLIC char Working_Directory[BYTES_SHELL_WORKING_DIRECTORY];
PUBLIC char tmp_path[BYTES_SHELL_WORKING_DIRECTORY + 101];

PUBLIC void Init_Shell() {
	Working_Directory[0] = '/';
	Working_Directory[1] = '\0';
}

PUBLIC int chdir(char *path) {
	char *src = path;
	char *dst = Working_Directory;
	while (*src != '\0') {
		*dst = *src;
		dst++;
		src++;
	}
	*dst = '\0';
	return 0;
}

PUBLIC char *getcwd(char *buf, size_t size) {
	// 检查 buf 是否为 NULL 或 size 是否为 0
	if (buf == NULL || size == 0) {
		return NULL;
	}

	// 将当前工作目录复制到 buf
	size_t i = 0;
	while (Working_Directory[i] != '\0' && i < size - 1) {
		buf[i] = Working_Directory[i];
		i++;
	}

	// 如果缓冲区大小足够，确保最后有 '\0' 字符
	buf[i] = '\0';

	// 如果目录没有被完全复制，表示缓冲区太小
	if (Working_Directory[i] != '\0') {
		return NULL;
	}

	return buf;
}

PUBLIC char *get_full_path(char *path) {
	if (path[0] == '/') {
		// 根目录开头的
		return path;
	}

	// 临时路径，用于处理路径段
	char *token;
	char temp_path[BYTES_SHELL_WORKING_DIRECTORY + 101] = {'\0'}; // 用于拼接新的路径

	size_t len1 = strlen(Working_Directory);
	// printl("[DEBUG ls] %s %d", Working_Directory, len1);
	// 初始化 tmp_path 为当前工作目录
	_strcpy(temp_path, Working_Directory);

	size_t len = strlen(temp_path);

	// 如果路径不是根路径, 并且当前路径没有以 / 结尾, 添加 /
	if (path[0] != '/') {
		// 如果当前工作目录没有以 / 结尾, 则加上 /
		if (temp_path[len - 1] != '/') {
			strcat(temp_path, "/");
		}
	}

	// 处理路径
	strcat(temp_path, path);        // 将给定的路径拼接到当前工作目录后面
	char *current_path = temp_path; // 用于遍历拼接后的路径

	// 解析路径中的各个部分
	char final_path[BYTES_SHELL_WORKING_DIRECTORY + 101]; // 最终生成的路径
	final_path[0]        = '/';                           // 初始化为空字符串
	final_path[1]        = '\0';
	char *final_path_ptr = final_path + 1; // 最终路径指针

	token = strtok(current_path, "/"); // 以 / 为分隔符，获取路径中的各部分

	// 遍历每一部分
	while (token != NULL) {
		if (strcmp(token, ".") == 0) {
			// 当前目录 (.) 不做任何操作，直接跳过
			token = strtok(NULL, "/");
			continue;
		} else if (strcmp(token, "..") == 0) {
			// 上级目录 (..) 删除最后一部分目录
			if (final_path_ptr != final_path) {
				// 如果 final_path_ptr 不指向路径的开头 (即 final_path 不为空)，删除最后的部分
				// 回退一个目录
				while (final_path_ptr > final_path && *(final_path_ptr - 1) != '/') {
					final_path_ptr--; // 移动指针回退一个字符
				}
				if (final_path_ptr > final_path) {
					final_path_ptr--; // 去掉目录部分的 /
				}
			} else {
				// 如果当前路径已经是根目录（即 final_path_ptr == final_path），不能再往上返回
				return NULL;
			}
		} else {
			// 正常路径部分
			if (final_path_ptr != final_path + 1 && *(final_path_ptr - 1) != '/') {
				// 如果不是路径的开头且没有 /，则加上 /
				*final_path_ptr = '/';
				final_path_ptr++;
			}
			// 将当前目录名添加到最终路径中
			_strcpy(final_path_ptr, token);
			final_path_ptr += strlen(token); // 更新 final_path_ptr
		}

		// 获取下一个路径部分
		token = strtok(NULL, "/");
	}

	// 确保最终路径以 '\0' 结尾
	*final_path_ptr = '\0';

	// 将最终的路径复制到 tmp_path 并返回
	_strcpy(tmp_path, final_path);

	// printl("")

	return tmp_path;
}