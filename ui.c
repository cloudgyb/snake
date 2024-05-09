//
// Created by Administrator on 2024/4/27.
//
#include <stdio.h>

#ifdef __WINNT

#include <windows.h>

#endif

# include "ui.h"

void print_char(char c, int x, int y) {
#if defined(WIN32) || defined(WIN64)
    HANDLE hOut;
    COORD pos = {(short) x, (short) y}; // 第一个参数是横坐标，第二个参数是纵坐标
    hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(hOut, pos);

    SetConsoleTextAttribute(hOut, 0x01 | 0x05);

    printf("%c", c);
#endif
}