#include <conio.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <time.h>

#ifdef __WINNT

#include <windows.h>
#include <locale.h>

#else
#include <stdlib.h>
#include <unistd.h>
#endif

///////////////////////////////////////////////////
typedef struct food {
    int x;
    int y;
} Food;

Food *food_create();

void food_generate(Food *food, int map_x_length, int map_y_length, int map_offset_x, int map_offset_y);

void food_show(Food *food);

void food_destroy(Food *food);
///////////////////////////////////////////////
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

////////////////////////////////////////////////
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
    int score;
    char body_char;
    char allow_crush_body;
    DIRECT direct;
    Food *food;
    Snake_body_node *head;
    Snake_body_node *tail;
} snake;

snake *snake_create();

void snake_init(snake *snake, int map_x_length, int map_y_length, int map_offset_x, int map_offset_y);

void snake_show(const snake *snake);

void snake_run(snake *snake, int map_x_length, int map_y_length, int map_offset_x, int map_offset_y);

int snake_crash_check(snake *snake, int map_x_length, int map_y_length, int map_offset_x, int map_offset_y);

void snake_destroy(snake *snake);

///////////////////////////////////////////////////////////
void hidden_cursor();

void move_cursor_to(int x, int y);

void print_char(char c, int x, int y);

void print_str(char *str, int x, int y);

void printf_str(char *format, int x, int y, ...);

/**
 * 设置窗口标题
 * @param title 标题
 */
void window_title(const char *title);

/**
 * 清屏
 */
void window_clear();

void window_init();

void window_restore();

//////////////////////////////////////////////////////////////////////////
int main(void) {
    window_title("贪吃蛇游戏"); //设置终端标题
    window_init(); // 设置终端窗口，隐藏光标清屏等
    window_clear();
    Map *map = init_map(30, 20, '#');
    show_map(map);
    snake *snake = snake_create();
    snake->body_char = '*';
    snake->allow_crush_body = 0;
    snake_init(snake, MAP_PARAM(map));
    snake_show(snake);
    show_score(map, 0);
    DIRECT curr_direct = snake->direct;
    DIRECT next_direct = curr_direct;
    while (1) {
        int key = -1;
        while (kbhit()) {
            // 非阻塞的检测键盘按下，使用 while 是处理用户多次连续按键，防止缓冲区一次读取不完影响下一次方向改变
            key = getch();
            if (key == 0 || key == 224) {
                // 处理功能键和方向键（上下左右）getch() 会有两次返回
                key = getch();
            }
        }
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
    show_game_over(map, snake->score);
    getch();
    snake_destroy(snake);
    destroy_map(map);
    window_restore(); //还原终端窗口
    return 0;
}

//////////////////////////////////////////////////////////////////
Food *food_create() {
    Food *food = (Food *) malloc(sizeof(Food));
    food->x = 0;
    food->y = 0;
    return food;
}

void food_generate(Food *food, int map_x_length, int map_y_length, int map_offset_x, int map_offset_y) {
    srand(time(0));
    int x0 = map_offset_x + 1; // 1
    int x1 = map_offset_x + map_x_length - 1; // 19
    food->x = rand() % (x1 - x0) + x0; // 18=0,17 1 18
    int y0 = map_offset_y + 1; // 1
    int y1 = map_offset_y + map_y_length - 1; // 9
    food->y = rand() % (y1 - y0) + y0; //8=0,7 1 8
}

void food_show(Food *food) {
    print_char('@', food->x, food->y);
}

void food_destroy(Food *food) {
    free(food);
}
////////////////////////////////////////////////////////////////////

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
    printf_str("score:%d",
               (map_offset_x + map_x_length) / 2 - 4,
               (map_offset_y + map_y_length) / 2 - 3,
               score);
    print_str("Game over!", (map_offset_x + map_x_length) / 2 - 5,
              (map_offset_y + map_y_length) / 2 + 2 - 3);
    print_str("按任意键继续!", (map_offset_x + map_x_length) / 2 - 6,
              (map_offset_y + map_y_length) / 2 + 3 - 3);
}

void destroy_map(Map *map) {
    free(map);
}

/////////////////////////////////////////////////////////////
int food_eat_check(snake *snake);

snake *snake_create() {
    return (snake *) malloc(sizeof(snake));
}

void snake_init(snake *snake, int map_x_length, int map_y_length, int map_offset_x, int map_offset_y) {
    snake->length = 0;
    snake->init_length = SNAKE_INIT_DEFAULT_LENGTH;
    snake->speed = 100000;
    snake->score = 0;
    snake->direct = RIGHT;
    snake->food = food_create();
    food_generate(snake->food, map_x_length, map_y_length, map_offset_x, map_offset_y);
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
    while (i-- > 0) {
        // 循环创建身体
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

void snake_show(const snake *snake) {
    food_show(snake->food); //显示食物
    const Snake_body_node *head = snake->head;
    while (head != NULL) {
        print_char(snake->body_char, head->x, head->y);
        head = head->next;
    }
}

void snake_run(snake *snake, int map_x_length, int map_y_length, int map_offset_x, int map_offset_y) {
    Snake_body_node *head = snake->head;
    Snake_body_node *newNode = (Snake_body_node *) malloc(sizeof(Snake_body_node));
    newNode->pre = newNode->next = NULL;
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
    print_char(snake->body_char, x, y); //显示新节点

    int is_eat = food_eat_check(snake);
    if (is_eat == 0) {
        //没吃到食物
        Snake_body_node *tail = snake->tail;
        snake->tail = tail->pre;
        snake->tail->next = NULL;
        print_char(' ', tail->x, tail->y);
        free(tail);
    } else {
        // 吃到了食物，不清除最后一个节点，将最后一个节点作为增长节点
        food_generate(snake->food, map_x_length, map_y_length, map_offset_x, map_offset_y);
        if (snake->speed < 1000000 - 100000) {
            // 速度有上限
            snake->speed += 20000;
        }
        snake->score += 10;
    }
    food_show(snake->food);
}

int snake_crash_check(snake *snake, int map_x_length, int map_y_length, int map_offset_x, int map_offset_y) {
    int min_x = map_offset_x;
    int max_x = map_offset_x + map_x_length - 1;
    int min_y = 0;
    int max_y = map_offset_y + map_y_length - 1;
    int x = snake->head->x;
    int y = snake->head->y;
    if (x <= min_x || x >= max_x || y <= min_y || y >= max_y) {
        return 1;
    }
    // 如果不允许蛇碰到自己的身体，检测蛇头是否碰到了身体
    if (!snake->allow_crush_body) {
        const Snake_body_node *head = snake->head;
        const Snake_body_node *next = head->next;
        while (next != NULL) {
            if (head->x == next->x && head->y == next->y) {
                return 1;
            }
            next = next->next;
        }
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

//////////////////////////////////////////////////////////////
void hidden_cursor() {
#ifdef __WINNT
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cci;
    GetConsoleCursorInfo(hOut, &cci);
    cci.bVisible = 0;//赋1为显示，赋0为隐藏
    SetConsoleCursorInfo(hOut, &cci);
#else
    printf("\033[?25l");
    fflush(stdout);
#endif
}

void show_cursor() {
#ifdef __WINNT
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cci;
    GetConsoleCursorInfo(hOut, &cci);
    cci.bVisible = 1;//赋1为显示，赋0为隐藏
    SetConsoleCursorInfo(hOut, &cci);
#else
    printf("\033[?25h");
    fflush(stdout);
#endif
}

void print_char(char c, int x, int y) {
    move_cursor_to(x, y);
    printf("%c", c);
}

void print_str(char *str, int x, int y) {
    move_cursor_to(x, y);
    printf("%s", str);
}

void printf_str(char *format, int x, int y, ...) {
    move_cursor_to(x, y);
    va_list argv;
    va_start(argv, y);
    vprintf(format, argv);
    va_end(argv);
}


void move_cursor_to(int x, int y) {
#if defined(WIN32) || defined(WIN64)
    HANDLE hOut;
    COORD pos = {(short) x, (short) y}; // 第一个参数是横坐标，第二个参数是纵坐标
    hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(hOut, pos);
    //SetConsoleTextAttribute(hOut, 0x01 | 0x05); // 设置字体颜色
#else
    printf("\033[%d;%dH",y,x);
#endif
}

void window_title(const char *title) {
#if defined(WIN32) || defined(WIN64)
    system("chcp 65001");
    SetConsoleTitle(title);
#else
    printf("\033]0;%s\007", title);
#endif
}

void window_clear() {
#if defined(WIN32) || defined(WIN64)
    system("cls");
#else
    system("clear");
#endif
}

void window_init() {
    hidden_cursor();
    window_clear();
}

void window_restore() {
    show_cursor();
}