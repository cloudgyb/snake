//
// Created by Administrator on 2024/4/27.
//

#include <malloc.h>
#include <time.h>
#include "snake.h"
#include "ui.h"

extern int map_x_length;
extern int map_y_length;
extern int map_offset_x;
extern int map_offset_y;

snake *snake_create() {
    return (snake *) malloc(sizeof(snake));
}

void snake_init(snake *snake) {
    snake->length = 0;
    snake->init_length = SNAKE_INIT_DEFAULT_LENGTH;
    snake->speed = 1;
    snake->head = (Snake_body_node *) malloc(sizeof(Snake_body_node));
    snake->head->pre = snake->head->next = NULL;
    srand(time(0));
    int x0 = map_offset_x + snake->init_length + 1;
    int x1 = map_offset_x + map_x_length - 1;
    snake->head->x = rand() % (x1 - x0 + 1) + x0;
    int y0 = map_offset_y + 1;
    int y1 = map_offset_y + map_y_length - 1;
    snake->head->y = rand() % (y1 - y0 + 1) + y0;
    Snake_body_node *pre = snake->head;
    int i = SNAKE_INIT_DEFAULT_LENGTH - 1;
    Snake_body_node *newNode = snake->head;
    while (i-- > 0) { // 循环创建身体
        newNode = (Snake_body_node *) malloc(sizeof(Snake_body_node));
        newNode->x = pre->x - 1;
        newNode->y = pre->y;
        pre->next = newNode;
        newNode->pre = pre;
        newNode->next = NULL;
        pre = newNode;
    }
    snake->tail = newNode; // 最后一个节点是尾巴
}

void snake_show(snake *snake) {
    Snake_body_node *head = snake->head;
    while (head != NULL) {
        print_char('*', head->x, head->y);
        head = head->next;
    }
}

void snake_destroy(snake *snake) {
    Snake_body_node *head = snake->head;
    Snake_body_node *des;
    while (head != NULL) {
        des = head;
        head = head->next;
        free(des);
    }
    free(snake);
}