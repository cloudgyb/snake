//
// Created by Administrator on 2024/4/27.
//
#include <stdio.h>

#ifdef __WINNT

#include <windows.h>

#else
#include <unistd.h>
#endif

# include "ui.h"

void hidden_cursor() {
#ifdef __WINNT
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cci;
    GetConsoleCursorInfo(hOut, &cci);
    cci.bVisible = 0;//赋1为显示，赋0为隐藏
    SetConsoleCursorInfo(hOut, &cci);
#else
    printf("\033[?25l");
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

void move_cursor_to(int x, int y) {
#if defined(WIN32) || defined(WIN64)
    HANDLE hOut;
    COORD pos = {(short) x, (short) y}; // 第一个参数是横坐标，第二个参数是纵坐标
    hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(hOut, pos);

    SetConsoleTextAttribute(hOut, 0x01 | 0x05);
#else
    printf("\033[10;20H");
#endif
}