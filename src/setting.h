//
// Created by Administrator on 2024/12/14.
//

#ifndef SETTING_H
#define SETTING_H

static char snake_body_chars[] = {'*', '@', '#'};
static char border_chars[] = {'*', '@', '#'};

typedef struct setting {
    char snake_body_char; // 蛇身体字符
    char snake_body_char_index; // 蛇身体字符 index
    char snake_allow_crash_body; // 是否允许蛇吃自己的身体，0 或 1
    char border_char; // 边墙字符
    char border_char_index; // 边墙字符 index
} Setting;

void setting_init(Setting *setting);

void setting_show(Setting *setting);

#endif //SETTING_H
