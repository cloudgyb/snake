cmake_minimum_required(VERSION 3.28)
project(snake C)

set(CMAKE_C_STANDARD 11)

add_executable(snake src/main.c
        src/map.h
        src/map.c
        src/ui.h
        src/ui.c
        src/snake.c
        src/snake.h
        src/food.c
        src/menu.c
        src/menu.h
        src/setting.h
        src/setting.c
        src/help.c
        src/help.h)
