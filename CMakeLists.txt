cmake_minimum_required(VERSION 3.28)
project(snake C)

set(CMAKE_C_STANDARD 11)

add_executable(snake main.c
        map.h
        map.c
        ui.h
        ui.c
        snake.c
        snake.h)
