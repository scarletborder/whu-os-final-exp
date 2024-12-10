#include "type.h"
#include "stdio.h"
#include "string.h"
#include "sys/const.h"
#include "sys/protect.h"
#include "sys/fs.h"
#include "sys/proc.h"
#include "sys/tty.h"
#include "sys/console.h"
#include "sys/global.h"
#include "sys/proto.h"

int main(int argc, char* argv[]) {
    if (argc != 2) {
        printf("Usage: kill <PID>\n");
        return -1;
    }

    int target_pid = atoi(argv[1]);  // 将传入的 PID 转为整数
    if (target_pid < 0 || target_pid >= NR_TASKS + NR_PROCS) {
        printf("Invalid PID: %d\n", target_pid);
        return -1;
    }

    MESSAGE msg;
    msg.PID = target_pid;
    msg.type = KILL;  
    send_recv(BOTH, TASK_MM, &msg);  // 发送请求给MM

    if (msg.type == SYSCALL_RET) {
        printf("Process %d killed successfully.\n", target_pid);
    } else {
        printf("Failed to kill process %d.\n", target_pid);
    }

    return 0;
}