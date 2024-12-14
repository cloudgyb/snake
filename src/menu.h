//
// Created by Lenovo on 2024/12/10.
//

#ifndef SNAKE_MENU_H
#define SNAKE_MENU_H

#define MENU_WIDTH 30
#define MENU_HEIGHT 20

typedef struct menu {
    int item_count;
    int select_index;
    char **items;
} Menu;

Menu *menu_create(int menu_size, char **menu_items);

void menu_print_border(int width, int height);

void menu_show(const Menu *menu);

int menu_select(Menu *menu);

void menu_destroy(Menu *menu);

void menu_show_max_score(int max_score);

#endif //SNAKE_MENU_H
