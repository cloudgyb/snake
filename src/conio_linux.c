//
// Created by Lenovo on 2025/10/30.
//
#ifndef __WINNT
#include "conio_linux.h"
#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <sys/select.h>
// 恢复终端设置的辅助函数
void reset_terminal_mode(struct termios *oldt) {
    tcsetattr(STDIN_FILENO, TCSANOW, oldt);
}

// 设置终端为非规范模式
void set_noncanonical_mode(struct termios *oldt, struct termios *newt) {
    tcgetattr(STDIN_FILENO, oldt);
    *newt = *oldt;
    newt->c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, newt);
}

int getch(void) {
    struct termios oldt, newt;
    set_noncanonical_mode(&oldt, &newt);
    int ch = getchar();
    reset_terminal_mode(&oldt);
    return ch;
}

int kbhit(void) {
    struct termios oldt, newt;
    set_noncanonical_mode(&oldt, &newt);

    fd_set fds;
    FD_ZERO(&fds);
    FD_SET(STDIN_FILENO, &fds);

    struct timeval tv = {0};
    int ret = select(STDIN_FILENO + 1, &fds, NULL, NULL, &tv);

    reset_terminal_mode(&oldt);
    return ret > 0;
}
#endif