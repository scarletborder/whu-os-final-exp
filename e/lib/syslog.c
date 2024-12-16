// clang-format off

/*************************************************************************//**
 *****************************************************************************
 * @file   syslog.c
 * @brief  
 * @author Forrest Y. Yu
 * @date   Thu Nov 20 17:02:42 2008
 *****************************************************************************
 *****************************************************************************/

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

static int __log_end_pos = 0;

/*****************************************************************************
 *                                syslog
 *****************************************************************************/
/**
 * Write log directly to the disk by sending message to FS.
 * 
 * @param fmt The format string.
 * 
 * @return How many chars have been printed.
 *****************************************************************************/
PUBLIC int syslog(const char *fmt, ...)
{
	int i;
	char buf[STR_DEFAULT_LEN];

	va_list arg = (va_list)((char*)(&fmt) + 4); /**
						     * 4: size of `fmt' in
						     *    the stack
						     */
	i = vsprintf(buf, fmt, arg);
	assert(strlen(buf) == i);

	
	return __log_end_pos = disklog(buf);
}


PUBLIC int syslogWithStr(const char *str)
{
	return __log_end_pos = disklog(str);
}

// dmesg | tail -n 123
PUBLIC void printLogTail(int tail){

}