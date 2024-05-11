#include <malloc.h>
#include <time.h>
#include <unistd.h>
#include "food.h"

extern int map_x_length;
extern int map_y_length;
extern int map_offset_x;
extern int map_offset_y;

Food *food_create() {
    Food *food = (Food *)malloc(sizeof(Food));
    food->x = 0;
    food->y = 0;
    return food;
}

void food_generate(Food *food,snake *snake) {
    srand(time(0));
    int x0 = map_offset_x + snake->init_length + 1;
    int x1 = map_offset_x + map_x_length - 1;
    food->x = rand() % (x1 - x0 + 1) + x0;
    int y0 = map_offset_y + 1;
    int y1 = map_offset_y + map_y_length - 1;
    food->y = rand() % (y1 - y0 + 1) + y0;
}