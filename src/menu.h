//
// Created by Lenovo on 2024/12/10.
//

#ifndef SNAKE_MENU_H
#define SNAKE_MENU_H

typedef struct menu {
    int item_count;
    int select_index;
    char **items;
} Menu;

Menu *menu_create(int menu_size, char **menu_items);

void menu_show(Menu *menu);

int menu_select(Menu *menu);

void menu_destroy(Menu *menu);

#endif //SNAKE_MENU_H
