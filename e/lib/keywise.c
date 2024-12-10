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

#include"keywise.h"
// clang-format on

// keyboard.c中一个变量原始为0
// 每次正常读取键盘会设置为1
// 用户send后,看看这个值,然后将其充值为原始0
int _kbhit() {
	MESSAGE msg;
	msg.type      = TYPETTY;
	msg.u.m1.m1i1 = 1;
	send_recv(BOTH, TASK_TTY, &msg);
	return msg.u.m1.m1i2;
}

// 用户send,阻塞
// keyboard.c设置一个变量
// keyboard.c下次正常运行读取键盘会send回来
int _getch() {
	MESSAGE msg;
	msg.type      = TYPETTY;
	msg.u.m1.m1i1 = 2;
	send_recv(BOTH, TASK_TTY, &msg);
	return msg.u.m1.m1i2;
}

int IsFlag(int flag) {
    MESSAGE msg;
	msg.type      = TYPETTY;
	msg.u.m1.m1i1 = 3;
    msg.u.m1.m1i2 = flag;
	send_recv(BOTH, TASK_TTY, &msg);
	return msg.u.m1.m1i2;
}