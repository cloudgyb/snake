//
// Created by Administrator on 2024/4/27.
//
#include <malloc.h>
#include "map.h"
#include "ui.h"


Map *init_map(unsigned int width, unsigned int height, char wall_char) {
    Map *map = (Map *) malloc(sizeof(Map));
    map->width = (int) width;
    map->height = (int) height;
    map->offset_x = map->offset_y = 0;
    map->wall_char = wall_char;
    return map;
}

void show_map(Map *map) {
    int map_y_length = map->height;
    int map_x_length = map->width;
    int map_offset_x = map->offset_x;
    int map_offset_y = map->offset_y;
    char wall_char = map->wall_char;
    for (int y = 0; y < map_y_length; y++) {
        for (int x = 0; x < map_x_length; x++) {
            if (x == 0 || x == map_offset_x + map_x_length - 1 || y == 0 || y == map_offset_y + map_y_length - 1) {
                print_char(wall_char, map_offset_x + x, map_offset_y + y);
            }
        }
    }
}


void show_score(Map *map, int score) {
    int map_y_length = map->height;
    int map_x_length = map->width;
    int map_offset_x = map->offset_x;
    int map_offset_y = map->offset_y;
    int x = map_offset_x + map_x_length + 1;
    int y = (map_offset_y + map_y_length) / 2;
    printf_str("score: %d", x, y, score);
}

void show_game_over(Map *map, int score) {
    int map_y_length = map->height;
    int map_x_length = map->width;
    int map_offset_x = map->offset_x;
    int map_offset_y = map->offset_y;
    printf_str("score:%d\nGame over!\n Press any key to exit!",
               (map_offset_x + map_x_length) / 2 - 5,
               (map_offset_y + map_y_length) / 2,
               score);
}

void destroy_map(Map *map) {
    free(map);
}