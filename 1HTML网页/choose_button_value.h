#ifndef CHOOSE_BUTTON_VALUE_H_
#define CHOOSE_BUTTON_VALUE_H_

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include"public.h"

//通过判断那个button按钮来返回设备号
int ret_equipment_id(char *name);
//根据相应的设备号调用相应的函数判断设备命令
void control_fun(char *val);
void control_led(char *val);
void control_buzzer(char *val);
void control_pipe(char *val);
#endif
