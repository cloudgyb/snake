//
// Created by Administrator on 2024/4/27.
//

#ifndef SNAKE_H
#define SNAKE_H
#define SNAKE_INIT_DEFAULT_LENGTH 4

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
    Snake_body_node *head;
    Snake_body_node *tail;
} snake;

snake *snake_create();

void snake_init(snake *snake);

void snake_show(snake *snake);

void snake_group(snake *snake);

void snake_destroy(snake *snake);

#endif //SNAKE_H
