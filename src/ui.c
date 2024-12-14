//
// Created by Administrator on 2024/4/27.
//
#include <stdio.h>

#ifdef __WINNT

#include <windows.h>
#include <locale.h>

#else
#include <stdlib.h>
#include <unistd.h>
#endif

#include "ui.h"

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

void show_cursor() {
#ifdef __WINNT
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cci;
    GetConsoleCursorInfo(hOut, &cci);
    cci.bVisible = 1;//赋1为显示，赋0为隐藏
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


void move_cursor_to(int x, int y) {
#if defined(WIN32) || defined(WIN64)
    HANDLE hOut;
    COORD pos = {(short) x, (short) y}; // 第一个参数是横坐标，第二个参数是纵坐标
    hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(hOut, pos);
    //SetConsoleTextAttribute(hOut, 0x01 | 0x05); // 设置字体颜色
#else
    printf("\033[%d;%dH",y,x);
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
}

void window_restore() {
    show_cursor();
}
