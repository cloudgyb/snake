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

#endif //SNAKE_UI_H
