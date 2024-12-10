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
            if (key == 'w') {
                print_str("  ", 1, 2 + menu->select_index);
                if (menu->select_index > 0) {
                    menu->select_index--;
                }
                print_str("> ", 1, 2 + menu->select_index);
            } else if(key == 's') {
                print_str("  ", 1, 2 + menu->select_index);
                if (menu->select_index < menu->item_count - 1) {
                    menu->select_index++;
                }
                print_str("> ", 1, 2 + menu->select_index);
            } else if(key == 'c') {
                return menu->select_index;
            }
            /*print_str("  ", 1, 2 + menu->select_index);
            if (key == 0 || key == 224) { // Handle special keys
                key = getch(); // Get the next character
                switch (key) {
                    case 72: // up
                        if (menu->select_index > 0) {
                            menu->select_index--;
                        }
                        break;
                    case 80: // down
                        if (menu->select_index < menu->item_count - 1) {
                            menu->select_index++;
                        }
                        break;
                        //case 75: // left
                        break;
                        //case 77: // right
                        //   break;
                    case 10: // Enter
                        return menu->select_index;
                }

            }
            print_str("> ", 1, 2 + menu->select_index);*/
        }
    }
    //return menu->select_index;
}

void menu_destroy(Menu *menu) {
    free(menu);
}