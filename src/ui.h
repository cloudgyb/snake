//
// Created by Administrator on 2024/4/27.
//

#ifndef SNAKE_UI_H
#define SNAKE_UI_H

void hidden_cursor();

void move_cursor_to(int x, int y);

void print_char(char c, int x, int y);

void print_str(char *str, int x, int y);

void printf_str(char *format, int x, int y, ...);

/**
 * 设置窗口大小
 * @param w 宽度
 * @param h 高度
 */
void window_resize(short w, short h);

/**
 * 设置窗口标题
 * @param title 标题
 */
void window_title(const char *title);

#endif //SNAKE_UI_H
