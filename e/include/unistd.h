// clang-format off
/** unistd.h
 * Here I stored some functions related with shell processing
 * NOTE: shabby_shell ought to be called at the launching stage only.
 */

#ifndef _SCARLETBORDER_UNISTD_H_
#define _SCARLETBORDER_UNISTD_H_

#include "type.h"

//clang-format on

// 文件操作相关

/**
 * change currently working directory
 * 
 * @param path path of target directory
 * @return Return ZERO if changing success, otherwise a non-zero value
 * 
 * NOTE: the logic code will not validate whether the target path is a directory
 */
int chdir(char *path);

// 系统信息与控制

/**
 * Get current working directory
 */
char *getcwd(char *buf, size_t size);

/**
 * util: cat a full filepath for a relative path
 */
char *get_full_path(char* path);


/**
 * init a shell
 * 
 * this function will initialize parameters related with shell
 */
void Init_Shell();

#endif