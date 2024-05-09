#include <stdio.h>
#include "map.h"
#include "snake.h"

extern int map_x_length; // 地图的长度
extern int map_y_length; // 地图的宽度

extern int map_offset_x; // 地图开始像素的水平偏移量
extern int map_offset_y; // 地图开始像素的纵向偏移量

extern int **map_data; // 地图数据，二维数组
int main(void) {
    map_offset_y = map_offset_x = 0;
    map_x_length = 20;
    map_y_length = 10;
    init_map();
    snake *snake = snake_create();
    snake_init(snake);
    snake_show(snake);
    snake_destroy(snake);
    getchar();
    destroy_map();
    return 0;
}
