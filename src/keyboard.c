//
// Created by Lenovo on 2025/10/30.
//

#include "keyboard.h"

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

int getch_linux(char *buf) {
    struct termios oldt, newt;
    set_noncanonical_mode(&oldt, &newt);
    int ch = read(0, buf, 100);
    reset_terminal_mode(&oldt);
    return ch;
}

int kbhit_linux(void) {
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

/*
 *   27|91|65| up
 *   27|91|66| down
 *   27|91|67| right
 *   27|91|68| left
 */
int get_key() {
    char buf[100];
    int key = 0;
    if (kbhit_linux()) {
        const int n = getch_linux(buf);
        // 27|91|65 处理方向键
        if (n == 3 && buf[0] == 27 && buf[1] == 91) {
            if (buf[2] == 65) { // up
                key = 'w';
            } else if (buf[2] == 66) { //down
                key = 's';
            } else if (buf[2] == 67) { // right
                key = 'd';
            } else if (buf[2] == 68) { // left
                key = 'a';
            }
        } else if (n == 1) {
            return buf[0];
        }
    }

    return key;
}

int main() {
    printf("Press any key (or 'q' to quit)...\n");
    char buf[100];
    while (1) {
        if (kbhit_linux()) {
            int ch = getch_linux(buf);
            printf("count: %d\n", ch);
            for (int i = 0; i < ch; i++) { printf("%d|", buf[i]); }
            printf("\n");
            if (buf[0] == 'q')
                break;
        }
        //printf("----\n");
        // 其他非阻塞任务
        //usleep(100000); // 避免忙等待
    }
    return 0;
}
