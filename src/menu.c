//
// Created by Lenovo on 2024/12/10.
//

#include <malloc.h>
#include <conio.h>
#include "ui.h"
#include "menu.h"

#define MENU_ITEM_X_OFFSET 8
#define MENU_ITEM_Y_OFFSET 5

Menu *menu_create(int menu_size, char **menu) {
    Menu *m = (Menu *) malloc(sizeof(Menu));
    m->item_count = menu_size;
    m->items = menu;
    m->select_index = 0;
    return m;
}

/**
 * 打印边界
 *
 * @param width 宽度
 * @param height 高度
 */
void menu_print_border(const int width, const int height) {
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (i == 0 || i == height - 1 || j == 0 || j == width - 1) {
                print_char('#', j, i);
            }
        }
    }
}

void menu_show(const Menu *menu) {
    menu_print_border(MENU_WIDTH, MENU_HEIGHT);
    print_str("贪吃蛇游戏", MENU_ITEM_X_OFFSET, 2);
    for (int i = 0; i < menu->item_count; i++) {
        if (menu->select_index == i) {
            print_str("> ", MENU_ITEM_X_OFFSET, MENU_ITEM_Y_OFFSET + i);
        }
        print_str((menu->items)[i], MENU_ITEM_X_OFFSET + 2, MENU_ITEM_Y_OFFSET + i);
    }
}

int menu_select(Menu *menu) {
    int key;
    while (1) {
        if (kbhit()) {
            key = getch();
            if (key == 0 || key == 224) {
                // 处理方向键（上下左右）getch() 会有两次返回
                key = getch();
            }
            if (key == 'w' || key == 72) {
                // 按了 w 或者 ↑ 键，菜单选项上移
                print_str("  ", MENU_ITEM_X_OFFSET, MENU_ITEM_Y_OFFSET + menu->select_index);
                if (menu->select_index > 0) {
                    menu->select_index--;
                }
                print_str("> ", MENU_ITEM_X_OFFSET, MENU_ITEM_Y_OFFSET + menu->select_index);
            } else if (key == 's' || key == 80) {
                // 按了 s 或者 ↓ 键，菜单选项下移
                print_str("  ", MENU_ITEM_X_OFFSET, MENU_ITEM_Y_OFFSET + menu->select_index);
                if (menu->select_index < menu->item_count - 1) {
                    menu->select_index++;
                }
                print_str("> ", MENU_ITEM_X_OFFSET, MENU_ITEM_Y_OFFSET + menu->select_index);
            } else if (key == 'c' || key == 13) {
                // 按 c 或者 Enter 选中菜单退出
                return menu->select_index;
            }
        }
    }
}

void menu_destroy(Menu *menu) {
    free(menu);
}

void menu_show_max_score(const int max_score) {
    menu_print_border(MENU_WIDTH, MENU_HEIGHT);
    printf_str("最高分：%d", MENU_ITEM_X_OFFSET, MENU_ITEM_Y_OFFSET, max_score);
    print_str("按任意键继续!", MENU_ITEM_X_OFFSET, MENU_ITEM_Y_OFFSET + 3);
    getch();
}
