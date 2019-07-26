#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "memory_cgi_a9.h"
#include "cgic.h"
#include "choose_button_value.h"

int cgiMain()
{
	int ret;
	char *submit=(char*)malloc(15);
	memset(submit,0,15);
	char *value=(char*)malloc(20);
	memset(value,0,10);
	MSG=(message_env_t*)malloc(sizeof(message_env_t));
	memset(MSG,0,sizeof(message_env_t));


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

	ret=ret_equipment_id(submit);
	int ret_fun=cgiFormSuccess;
	switch(ret_equipment_id(submit))
	{
	case EQUI_BUZZER:
		control_buzzer(value);
		MSG->flag|=EQUI_BUZZER;
		break;
	case EQUI_FUN:
		control_fun(value);
		MSG->flag|=EQUI_FUN;
		break;
	case EQUI_LED:
		control_led(value);
		MSG->flag|=EQUI_LED;
		break;
	case EQUI_PIPE:
		control_pipe(value);
		MSG->flag|=EQUI_PIPE;
		break;
	case -1:
		printf("error\n");
		goto ERR_CLO;
	default:
		break;
	}
	MSG->flag|=*value;
	MSG->flag|=MANUAL;

	//semop(order_semid,order_op_t,2);
	//strncpy(order_address,(char*)MSG,sizeof(message_env_t));


	//显示提交成功,并返回控制网页
	cgiHeaderContentType("text/html");
	printf("<html><head><title>Untitled</title></head>\
			<body><div><font color=\"#00000\" class=\"ws26\">\
			msg->flag:%d   value:%d ret:%d ret_fun:%d\
			</font></div></body></html>",MSG->flag,*value,ret,ret_fun);

ERR_CLO:
	free(submit);
	submit=NULL;
	free(value);
	value=NULL;
	free(MSG);
	MSG=NULL;

	return 0;
}
