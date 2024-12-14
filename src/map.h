//
// Created by Administrator on 2024/4/27.
//

#ifndef SNAKE_MAP_H
#define SNAKE_MAP_H

#define MAP_PARAM(m) m->width, m->height, m->offset_x, m->offset_y

typedef struct map {
    int width; // 地图的宽
    int height; // 地图的高
    int offset_x; // 地图打印显示x轴的偏移量
    int offset_y; // 地图打印显示y轴的偏移量
    char wall_char; // 地图围墙字符，# % @ 都可以
} Map;

Map *init_map(unsigned int width, unsigned int height, char wall_char);

void show_map(Map *map);

void show_score(Map *map, int score);

void show_game_over(Map *map, int score);


void destroy_map(Map *map);

#endif //SNAKE_MAP_H
