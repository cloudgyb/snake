//
// Created by Lenovo on 2024/12/10.
//

#include <malloc.h>
#include <conio.h>
#include "ui.h"
#include "menu.h"

Menu *menu_create(int menu_size, char **menu) {
    Menu *m = (Menu *) malloc(sizeof(Menu));
    m->item_count = menu_size;
    m->items = menu;
    m->select_index = 0;
    return m;
}

void menu_show(Menu *menu) {
    int width = 30;
    int height = 20;
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (i == 0 || i == height - 1 || j == 0 || j == width - 1) {
                print_char('#', j, i);
            }
        }
    }

    for (int i = 0; i < menu->item_count; i++) {
        if (menu->select_index == i) {
            print_str("> ", 1, 2 + i);
        }
        print_str((menu->items)[i], 3, 2 + i);
    }
}

int menu_select(Menu *menu) {
    int key;
    while (1) {
        if (kbhit()) {
            key = getch();
            if (key == 0 || key == 224) { // 处理方向键（上下左右）getch() 会有两次返回
                key = getch();
            }
            if (key == 'w' || key == 72) {// 按了 w 或者 ↑ 键，菜单选项上移
                print_str("  ", 1, 2 + menu->select_index);
                if (menu->select_index > 0) {
                    menu->select_index--;
                }
                print_str("> ", 1, 2 + menu->select_index);
            } else if (key == 's' || key == 80) { // 按了 s 或者 ↓ 键，菜单选项下移
                print_str("  ", 1, 2 + menu->select_index);
                if (menu->select_index < menu->item_count - 1) {
                    menu->select_index++;
                }
                print_str("> ", 1, 2 + menu->select_index);
            } else if (key == 'c' || key == 13) { // 按 c 或者 Enter 选中菜单退出
                return menu->select_index;
            }
        }
    }
}

void menu_destroy(Menu *menu) {
    free(menu);
}