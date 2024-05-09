//
// Created by Administrator on 2024/4/27.
//
#include "map.h"
#include <stdlib.h>
#include <mem.h>
#include "ui.h"

int map_x_length; // 地图的长度
int map_y_length; // 地图的宽度

int map_offset_x; // 地图开始像素的水平偏移量
int map_offset_y; // 地图开始像素的纵向偏移量

int **map_data; // 地图数据，二维数组

void init_map() {
    size_t mem_size = sizeof(int) * map_y_length * map_x_length;
    map_data = (int **) malloc(mem_size);
    memset(map_data, 0, mem_size);
    for (int y = 0; y < map_y_length; y++) {
        for (int x = 0; x < map_x_length; x++) {
            if (x == 0 || x == map_offset_x + map_x_length - 1 || y == 0 || y == map_offset_y + map_y_length - 1) {
                print_char('*', map_offset_x + x, map_offset_y + y);
            }
        }
    }
}

void destroy_map() {
    free(map_data);
}