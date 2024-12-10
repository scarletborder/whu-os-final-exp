#include "stdio.h"

// PUBLIC int getpid();  // 声明 getpid 函数

int main() {
    int pid = getpid();  // 获取当前进程的 PID
    printf("Current process PID: %d\n", pid);  // 打印 PID
    return 0;
}
