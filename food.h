#ifndef SNAKE_FOOD_H
#define SNAKE_FOOD_H

#include "snake.h"

typdef struct food {
    int x;
    int y;
} Food;


Food *food_create();

void food_generate(Food *food,snake *snake);

#endif