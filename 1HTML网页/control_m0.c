#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "memory_cgi_a9.h"
#include "cgic.h"
#include "choose_button_value.h"

struct control_order
{
	int 
};

int cgiMain()
{
	int ret;
	char *submit=(char*)malloc(15);
	memset(submit,0,15);
	char *value=(char*)malloc(10);
	memset(value,0,10);
	message_env_t* msg_order=(message_env_t*)malloc(sizeof(message_env_t));
	memset(msg_order,0,sizeof(message_env_t));


	ret=key_init();
	if(ret<0){
		printf("key error\n");
		return -1;
	}

	ret=memory_order_create();
	if(ret<0){
		printf("memory error\n");
		return -1;
	}

	semop_semval_order_init();
	//通过返回值判断是哪个按钮提交

	switch(ret_equipment_id(submit))
	{
	case EQUI_BUZZER:
		control_buzzer(value);
		msg_order->flag|=EQUI_BUZZER;
		break;
	case EQUI_FUN:
		control_fun(value);
		msg_order->flag|=EQUI_FUN;
		break;
	case EQUI_LED:
		control_led(value);
		msg_order->flag|=EQUI_LED;
		break;
	case EQUI_PIPE:
		control_pipe(value);
		msg_order->flag|=EQUI_PIPE;
		break;
	case -1:
		printf("error\n");
		goto ERR_CLO;
	default:
		break;
	}
	msg_order->flag|=value;

	semop(
	//显示提交成功,并返回控制网页
	cgiHeaderContentType("text/html");





ERR_CLO:
	free(submit);
	submit=NULL;
	free(value);
	value=NULL;
	free(msg_order);
	msg_order=NULL;

	return 0;
}
