//
// Created by Administrator on 2024/12/14.
//

#include <stdio.h>
#include <conio.h>
#include "help.h"

void help_show() {
    printf("##########################################\n");
    printf("#                                        #\n");
    printf("#                游戏帮助                #\n");
    printf("#                                        #\n");
    printf("#   按键说明：                           #\n");
    printf("#     上下左右 或 w s a d 键             #\n");
    printf("#     控制菜单和蛇的方向                 #\n");
    printf("#                                        #\n");
    printf("#          ↑            w                #\n");
    printf("#       ←     →      a     s             #\n");
    printf("#          ↓            d                #\n");
    printf("#                                        #\n");
    printf("#   游戏说明：                           #\n");
    printf("#      1. 随着蛇蛇吃的食物越来越多,      #\n");
    printf("#         蛇会越来越长,速度会越来越快。  #\n");
    printf("#      2. 蛇不能撞到边界,否则游戏结束。  #\n");
    printf("#         也能设置不许蛇碰到自己的身体。 #\n");
    printf("#      3. 每吃一个食物,得 10 分。        #\n");
    printf("#                                        #\n");
    printf("#             按任意键继续...            #\n");
    printf("#                                        #\n");
    printf("#                                        #\n");
    printf("#                                        #\n");
    printf("#           @cloudgyb 版权所有           #\n");
    printf("##########################################\n");
    getch();
}
