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
#include "keyboard.h"
#include "proto.h"

#include "logfila.h"
// clang-format on

PUBLIC void task_log() {
	InitLogWares();
	char buf[256];
	MESSAGE msg;
	while (1) {
		send_recv(RECEIVE, ANY, &msg);
		int type = msg.type;
		int len  = msg.u.m3.m3i1;
		int src  = msg.source;

		if (type == 1) {
			phys_copy((void *)va2la(TASK_LOGS, buf), /* to   */
				(void *)va2la(src, msg.u.m3.m3p1),   /* from */
				len + 1);

			syslogWithStr(buf);
		}else {
			int tail = msg.u.m3.m3i1;
			printLogTail(tail);
		}
	}
}