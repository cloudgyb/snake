//
// Created by Administrator on 2024/4/27.
//

#ifndef SNAKE_H
#define SNAKE_H

#include "food.h"

#define SNAKE_INIT_DEFAULT_LENGTH 4
typedef enum {
    LEFT, RIGHT, UP, DOWN
} DIRECT;
typedef struct snake_body_node {
    int x;
    int y;
    struct snake_body_node *pre;
    struct snake_body_node *next;
} Snake_body_node;

typedef struct {
    int init_length;
    int length;
    int speed;
    DIRECT direct;
    Food *food;
    Snake_body_node *head;
    Snake_body_node *tail;
} snake;

snake *snake_create();

void snake_init(snake *snake);

void snake_show(snake *snake);

void snake_run(snake *snake);

int snake_crash_check(snake *snake);

void snake_destroy(snake *snake);

#endif //SNAKE_H
