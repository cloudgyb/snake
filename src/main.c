#include <unistd.h>
#include "map.h"
#include "snake.h"
#include "ui.h"
#include "menu.h"
#include "setting.h"
#include "help.h"

int main(void) {
    window_title("贪吃蛇游戏"); //设置终端标题
    window_init(); // 设置终端窗口，隐藏光标清屏等

    char *menu_items[5] = {"新游戏", "最高分", "设置", "帮助", "退出"};
    Menu *menu = menu_create(5, (char **) menu_items);
    Setting setting = {'*', 0, 0, '#', 2};
    int max_score = 0; // 最高分

    while (1) {
        window_clear();
        menu_show(menu);
        const int menu_index = menu_select(menu);
        window_clear();
        if (menu_index == 0) {
            Map *map = init_map(30, 20, setting.border_char);
            show_map(map);
            snake *snake = snake_create();
            snake->body_char = setting.snake_body_char;
            snake->allow_crush_body = setting.snake_allow_crash_body;
            snake_init(snake, MAP_PARAM(map));
            snake_show(snake);
            show_score(map, 0);
            DIRECT curr_direct = snake->direct;
            DIRECT next_direct = curr_direct;
            while (1) {
                const int key = get_key();
                // 有按键按下，根据按键改变蛇的方向
                if (key != -1) {
                    curr_direct = snake->direct;
                    if ((key == 'w' || key == 72) && curr_direct != DOWN) {
                        next_direct = UP;
                    } else if ((key == 's' || key == 80) && curr_direct != UP) {
                        next_direct = DOWN;
                    } else if ((key == 'a' || key == 75) && curr_direct != RIGHT) {
                        next_direct = LEFT;
                    } else if ((key == 'd' || key == 77) && curr_direct != LEFT) {
                        next_direct = RIGHT;
                    } else if (key == 'q') {
                        break;
                    }
                    snake->direct = next_direct;
                }

                snake_run(snake, MAP_PARAM(map));
                show_score(map, snake->score);
                const int res = snake_crash_check(snake, MAP_PARAM(map));
                // 发生碰撞了
                if (res == 1) {
                    break;
                }
                usleep(1000000 - snake->speed);
            }
            max_score = max_score > snake->score ? max_score : snake->score;
            show_game_over(map, snake->score);
            wait_keypress();
            snake_destroy(snake);
            destroy_map(map);
        } else if (menu_index == 1) {
            // 显示最高分
            menu_show_max_score(max_score);
        } else if (menu_index == 2) {
            // 设置
            setting_show(&setting);
        } else if (menu_index == 3) {
            // 显示帮助
            help_show();
        } else if (menu_index == 4) {
            break;
        }
    }

    menu_destroy(menu);

    window_restore(); //还原终端窗口
    return 0;
}
