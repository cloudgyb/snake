//
// Created by Administrator on 2024/4/27.
//

#include <malloc.h>
#include <time.h>
#include <unistd.h>
#include "snake.h"
#include "ui.h"
#include "map.h"

extern int map_x_length;
extern int map_y_length;
extern int map_offset_x;
extern int map_offset_y;

int food_eat_check(snake *snake);

snake *snake_create() {
    return (snake *) malloc(sizeof(snake));
}

void snake_init(snake *snake) {
    snake->length = 0;
    snake->init_length = SNAKE_INIT_DEFAULT_LENGTH;
    snake->speed = 10000;
    snake->score = 0;
    snake->direct = RIGHT;
    snake->food = food_create();
    food_generate(snake->food);
    snake->head = (Snake_body_node *) malloc(sizeof(Snake_body_node));
    snake->head->pre = snake->head->next = NULL;
    srand(time(0));
    int x0 = map_offset_x + snake->init_length + 1;
    int x1 = map_offset_x + map_x_length - 1;
    snake->head->x = rand() % (x1 - x0) + x0;
    int y0 = map_offset_y + 1;
    int y1 = map_offset_y + map_y_length - 1;
    snake->head->y = rand() % (y1 - y0) + y0;
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
    food_show(snake->food); //显示食物
    Snake_body_node *head = snake->head;
    while (head != NULL) {
        print_char('*', head->x, head->y);
        head = head->next;
    }
    show_score(0);
}

void snake_run(snake *snake) {
    Snake_body_node *head = snake->head;
    Snake_body_node *newNode = (Snake_body_node *) malloc(sizeof(Snake_body_node));
    DIRECT direct = snake->direct;
    int x = head->x;
    int y = head->y;
    if (direct == LEFT) {
        x = head->x - 1;
    } else if (direct == RIGHT) {
        x = head->x + 1;
    } else if (direct == UP) {
        y = head->y - 1;
    } else {
        y = head->y + 1;
    }
    newNode->x = x;
    newNode->y = y;
    snake->head = newNode;
    newNode->next = head;
    head->pre = newNode;
    print_char('*', x, y); //显示新节点

    int is_eat = food_eat_check(snake);
    if (is_eat == 0) { //没吃到食物
        Snake_body_node *tail = snake->tail;
        snake->tail = tail->pre;
        print_char(' ', tail->x, tail->y);
        free(tail);
    } else { // 吃到了食物，不清除最后一个节点，将最后一个节点作为增长节点
        food_generate(snake->food);
        if (snake->speed < 1000000 - 100000) { // 速度有上限
            snake->speed += 20000;
        }
        snake->score += 10;
        show_score(snake->score);
    }
    food_show(snake->food);
    usleep(1000000 - snake->speed);
}

int snake_crash_check(snake *snake) {
    int min_x = map_offset_x;
    int max_x = map_offset_x + map_x_length - 1;
    int min_y = 0;
    int max_y = map_offset_y + map_y_length - 1;
    int x = snake->head->x;
    int y = snake->head->y;
    if (x <= min_x || x >= max_x || y <= min_y || y >= max_y) {
        return 1;
    }
    return 0;
}


void snake_destroy(snake *snake) {
    food_destroy(snake->food);
    Snake_body_node *head = snake->head;
    Snake_body_node *des;
    while (head != NULL) {
        des = head;
        head = head->next;
        free(des);
    }
    free(snake);
}

int food_eat_check(snake *snake) {
    Food *food = snake->food;
    Snake_body_node *head = snake->head;
    if (food->x == head->x && food->y == head->y) {
        return 1;
    }
    return 0;
}