#include <malloc.h>
#include <time.h>
#include "food.h"
#include "ui.h"

Food *food_create() {
    Food *food = (Food *) malloc(sizeof(Food));
    food->x = 0;
    food->y = 0;
    return food;
}

void food_generate(Food *food,int map_x_length, int map_y_length, int map_offset_x, int map_offset_y) {
    srand(time(0));
    int x0 = map_offset_x + 1; // 1
    int x1 = map_offset_x + map_x_length - 1; // 19
    food->x = rand() % (x1 - x0) + x0; // 18=0,17 1 18
    int y0 = map_offset_y + 1; // 1
    int y1 = map_offset_y + map_y_length - 1; // 9
    food->y = rand() % (y1 - y0) + y0; //8=0,7 1 8
}

void food_show(Food *food) {
    print_char('@', food->x, food->y);
}

void food_destroy(Food *food) {
    free(food);
}