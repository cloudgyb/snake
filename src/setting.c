//
// Created by Administrator on 2024/12/14.
//
#include <stdio.h>
#include <conio.h>
#include "ui.h"
#include "setting.h"


void setting_init(Setting *setting) {
    setting->snake_body_char = snake_body_chars[0];
    setting->snake_allow_crash_body = 0;
    setting->border_char = border_chars[2];
}

void setting_show(Setting *setting) {
    printf("####################################\n");
    printf("#                                  #\n");
    printf("#           游戏设置               #\n");
    printf("#                                  #\n");
    printf("#   > 蛇身显示：[ ] * [ ] @ [ ] #  #\n");
    printf("#     蛇允许碰到自己：[v]          #\n");
    printf("#     边框显示：[ ] * [ ] @ [ ] #  #\n");
    printf("#                                  #\n");
    printf("#    说明：上下切换设置项          #\n");
    printf("#         左右切换选项选中         #\n");
    printf("#         v 表示设置选中           #\n");
    printf("#         q 退出设置并保存         #\n");
    printf("#                                  #\n");
    printf("####################################\n");

    int y_select_index = 0;
    int snake_body_char_index = (unsigned char) setting->snake_body_char_index;
    int border_char_index = (unsigned char) setting->border_char_index;
    int snake_allow_crash_body = (unsigned char) setting->snake_allow_crash_body;
    // 初始化选中
    print_char('v', 17 + 6 * snake_body_char_index, 4 + 0);
    print_char(snake_allow_crash_body ? 'v' : ' ', 23, 4 + 1);
    print_char('v', 17 + 6 * border_char_index, 4 + 2);

    while (1) {
        if (kbhit()) {
            int key = getch();
            if (key == 0 || key == 224) {
                // 处理方向键（上下左右）getch() 会有两次返回
                key = getch();
            }
            if (key == 'w' || key == 72) {
                // 按了 w 或者 ↑ 键，菜单选项上移
                print_str(" ", 4, 4 + y_select_index);
                if (y_select_index > 0) {
                    y_select_index--;
                }
                print_str(">", 4, 4 + y_select_index);
            } else if (key == 's' || key == 80) {
                // 按了 s 或者 ↓ 键，菜单选项下移
                print_str(" ", 4, 4 + y_select_index);
                if (y_select_index < 3 - 1) {
                    y_select_index++;
                }
                print_str(">", 4, 4 + y_select_index);
            } else if (key == 'a' || key == 75) {
                // 处理 a 或者 ← 键，选择设置项
                // 蛇身显示设置
                if (y_select_index == 0) {
                    print_char(' ', 17 + 6 * snake_body_char_index, 4 + y_select_index);
                    if (snake_body_char_index > 0) {
                        snake_body_char_index--;
                    }
                    print_char('v', 17 + 6 * snake_body_char_index, 4 + y_select_index);
                    // 蛇允许碰到自己设置
                } else if (y_select_index == 1) {
                    snake_allow_crash_body = !snake_allow_crash_body;
                    const char v = snake_allow_crash_body ? 'v' : ' ';
                    print_char(v, 23, 4 + y_select_index);
                    // 边框显示设置
                } else if (y_select_index == 2) {
                    print_char(' ', 17 + 6 * border_char_index, 4 + y_select_index);
                    if (border_char_index > 0) {
                        border_char_index--;
                    }
                    print_char('v', 17 + 6 * border_char_index, 4 + y_select_index);
                }
            } else if (key == 'd' || key == 77) {
                if (y_select_index == 0) {
                    print_str(" ", 17 + 6 * snake_body_char_index, 4 + y_select_index);
                    if (snake_body_char_index < 2) {
                        snake_body_char_index++;
                    }
                    print_str("v", 17 + 6 * snake_body_char_index, 4 + y_select_index);
                    // 蛇允许碰到自己设置
                } else if (y_select_index == 1) {
                    snake_allow_crash_body = !snake_allow_crash_body;
                    const char v = snake_allow_crash_body ? 'v' : ' ';
                    print_char(v, 23, 4 + y_select_index);
                    // 边框显示设置
                } else if (y_select_index == 2) {
                    print_str(" ", 17 + 6 * border_char_index, 4 + y_select_index);
                    if (border_char_index < 2) {
                        border_char_index++;
                    }
                    print_str("v", 17 + 6 * border_char_index, 4 + y_select_index);
                }
            } else if (key == 'c' || key == 'q') {
                // 按 c 或者 'q' 退出设置
                break;
            }
        }
    }
    setting->snake_body_char = snake_body_chars[snake_body_char_index];
    setting->border_char = border_chars[border_char_index];
    setting->snake_allow_crash_body = (char) snake_allow_crash_body;
    setting->snake_body_char_index = (char) snake_body_char_index;
    setting->border_char_index = (char) border_char_index;
    //printf_str("%c %c %d", 0, 50, setting->snake_body_char, setting->border_char, setting->snake_allow_crash_body);
    //getch();
}
