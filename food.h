#ifndef SNAKE_FOOD_H
#define SNAKE_FOOD_H

typedef struct food {
    int x;
    int y;
} Food;


Food *food_create();

void food_generate(Food *food);

void food_show(Food *food);

void food_destroy(Food *food);

#endif