//
// Created by Administrator on 2024/4/27.
//
#include <stdio.h>

#ifdef __WINNT

#include <windows.h>
#include <locale.h>
#include <conio.h>

#else
#include <stdlib.h>
#include <unistd.h>
#include <termio.h>
#include <fcntl.h>
#include <stdarg.h>
#endif

#include "ui.h"

void hidden_cursor() {
#ifdef __WINNT
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cci;
    GetConsoleCursorInfo(hOut, &cci);
    cci.bVisible = 0; //赋1为显示，赋0为隐藏
    SetConsoleCursorInfo(hOut, &cci);
#else
    printf("\033[?25l");
    fflush(stdout);
#endif
}

void show_cursor() {
#ifdef __WINNT
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cci;
    GetConsoleCursorInfo(hOut, &cci);
    cci.bVisible = 1; //赋1为显示，赋0为隐藏
    SetConsoleCursorInfo(hOut, &cci);
#else
    printf("\033[?25h");
    fflush(stdout);
#endif
}

void print_char(char c, int x, int y) {
    move_cursor_to(x, y);
    printf("%c", c);
}

void print_str(char *str, int x, int y) {
    move_cursor_to(x, y);
    printf("%s", str);
}

void printf_str(char *format, int x, int y, ...) {
    move_cursor_to(x, y);
    va_list argv;
    va_start(argv, y);
    vprintf(format, argv);
    va_end(argv);
}

#ifndef __WINNT
static void terminal_init() {
    struct termios term_conf;
    tcgetattr(STDIN_FILENO, &term_conf);
    term_conf.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &term_conf);
    const int stdin_fd_fl = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, stdin_fd_fl | O_NONBLOCK);
}

static int kbhit(void) {
    int ch;
    char is = 0;
    while ((ch = getchar()) != EOF) {
        ungetc(ch, stdin);
        is = 1;
    }
    if (is) {
        return 1;
    }
    return 0;
}
#endif


int get_key() {
    int key = -1;
#ifdef __WINNT
    while (kbhit()) {
        // 非阻塞的检测键盘按下，使用 while 是处理用户多次连续按键，防止缓冲区一次读取不完影响下一次方向改变
        key = getch();
        if (key == 0 || key == 224) {
            // 处理功能键和方向键（上下左右）getch() 会有两次返回
            key = getch();
        }
    }
#else
    char ch = -1;
    if ((ch = getchar()) != EOF) {
        if (ch == 27) {
            // 处理方向按键
            ch = getchar();
            if (ch == 91) {
                ch = getchar();
                if (ch == 65) {
                    ch = 'w';
                } else if (ch == 66) {
                    ch = 's';
                } else if (ch == 67) {
                    ch = 'd';
                } else if (ch == 68) {
                    ch = 'a';
                }
            }
        }
    }
    // 兼容windows的回车键
    if (ch == '\n') {
        ch = 13;
    }
    key = (int) ch;
#endif
    return key;
}

void wait_keypress() {
#ifdef __WINNT
    getch();
#else
    while (getchar() == -1) {
    }
#endif
}


void move_cursor_to(int x, int y) {
#if defined(WIN32) || defined(WIN64)
    HANDLE hOut;
    COORD pos = {(short) x, (short) y}; // 第一个参数是横坐标，第二个参数是纵坐标
    hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(hOut, pos);
    //SetConsoleTextAttribute(hOut, 0x01 | 0x05); // 设置字体颜色
#else
    printf("\033[%d;%dH", y, x);
#endif
}

void window_title(const char *title) {
#if defined(WIN32) || defined(WIN64)
    system("chcp 65001");
    SetConsoleTitle(title);
#else
    printf("\033]0;%s\007", title);
#endif
}

void window_clear() {
#if defined(WIN32) || defined(WIN64)
    system("cls");
#else
    system("clear");
#endif
}

void window_init() {
    hidden_cursor();
    window_clear();
#ifndef __WINNT
    terminal_init();
#endif
}

void window_restore() {
    show_cursor();
#ifndef __WINNT
    system("reset");
#endif
}
