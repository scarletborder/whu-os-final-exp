// clang-format off

/*************************************************************************//**
 *****************************************************************************
 * @file   syslog.c
 * @brief  
 * @author Forrest Y. Yu
 * @date   Thu Nov 20 17:02:42 2008
 *****************************************************************************
 *****************************************************************************/

#include "config.h"
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

// clang-format on

PUBLIC int syslogWithStr(const char *str) {
	return __log_end_pos = disklog(str);
}

// dmesg | tail -n 123
PUBLIC void printLogTail(int tail) {
	int device             = root_inode->i_dev;
	struct super_block *sb = get_super_block(device);
	int nr_log_blk0_nr     = sb->nr_sects - NR_SECTS_FOR_LOG; /* 0x9D41-0x800=0x9541 */

	int pos = 0x40;
	// read from pos to __log_end_pos
	char tmp_buf[1025] = "\0";

	int sect_nr    = nr_log_blk0_nr + (pos >> SECTOR_SIZE_SHIFT);
	int bytes_left = __log_end_pos - pos;

	printl("cotain end%d\n", __log_end_pos);

	while (pos < __log_end_pos) {
		rw_sector(DEV_READ, device, (sect_nr) * 512, 512, TASK_LOGS, tmp_buf);
		int off   = pos % SECTOR_SIZE;
		int bytes = ((bytes_left) < (512 - off) ? (bytes_left) : (512 - off));

		bytes_left -= bytes;
		sect_nr++;
		pos += bytes;
	}
	tmp_buf[tail + 1] = '\0';
	printx(tmp_buf);
}