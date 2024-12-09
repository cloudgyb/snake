#include <conio.h>
#include <stdlib.h>
#include <unistd.h>
#include "map.h"
#include "snake.h"
#include "ui.h"


int main(void) {
    hidden_cursor();
    system("chcp 65001");
    system("cls");
    window_title("贪吃蛇游戏");
    Map *map = init_map(30, 20, '$');
    show_map(map);
    snake *snake = snake_create();
    snake_init(snake, MAP_PARAM(map));
    snake_show(snake);
    show_score(map, 0);
    char key;
    DIRECT curr_direct;
    DIRECT next_direct;
    while (1) {
        if (kbhit()) { // 方向控制及退出游戏
            key = getch();
            curr_direct = snake->direct;
            if (key == 'w' && curr_direct != DOWN) {
                next_direct = UP;
            } else if (key == 's' && curr_direct != UP) {
                next_direct = DOWN;
            } else if (key == 'a' && curr_direct != RIGHT) {
                next_direct = LEFT;
            } else if (key == 'd' && curr_direct != LEFT) {
                next_direct = RIGHT;
            } else if (key == 'q') {
                break;
            }
            snake->direct = next_direct;
        }
        snake_run(snake, MAP_PARAM(map));
        show_score(map, snake->score);
        int res = snake_crash_check(snake, MAP_PARAM(map));
        if (res == 1) { // 发生碰撞了
            break;
        }
        usleep(1000000 - snake->speed);
    }
    show_game_over(map, snake->score);
    snake_destroy(snake);
    system("pause");
    destroy_map(map);
    return 0;
}
