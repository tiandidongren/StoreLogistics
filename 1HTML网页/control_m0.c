#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "memory_cgi_a9.h"
#include "cgic.h"
#include "choose_button_value.h"

#define NO_USE
int cgiMain()
{
	int ret,ret_key,ret_mem;
	char *submit=(char*)malloc(15);
	memset(submit,0,15);
	char *value=(char*)malloc(20);
	memset(value,0,10);
	MSG=(message_env_t*)malloc(sizeof(message_env_t));
	memset(MSG,0,sizeof(message_env_t));

	ret_key=key_init();
	if(ret_key<0){
		printf("key error\n");
		return -1;
	}

	ret_mem=memory_order_create();
	if(ret_mem<0){
		printf("memory error\n");
		return -1;
	}

	semop_semval_order_init();
	//通过返回值判断是哪个按钮提交

	//ret=ret_equipment_id(submit);
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

#ifndef NO_USE
	semop(order_semid,order_op_t,1);
	//strncpy(order_address,(char*)MSG,sizeof(message_env_t));
#else
	strncpy(((message_env_t*)order_address)->head,"st:",3);
#endif
	((message_env_t*)order_address)->flag=MSG->flag;
	((message_env_t*)order_address)->type=CGI_ORDER;
#ifndef NO_USE
	semop(order_semid,order_op_t+1,1);
#endif

	//显示提交成功,并返回控制网页
	cgiHeaderContentType("text/html");
	printf("<html><head><title>Untitled</title></head>\
			<body><div><font color=\"#00000\" class=\"ws26\">\
			msg->flag:%d   value:%d ret:%dret_key:%dret_mem:%d order->flag:%d   \
			</font></div></body></html>",MSG->flag,*value,ret,ret_key,ret_mem,((message_env_t*)order_address)->flag);

ERR_CLO:
	free(submit);
	submit=NULL;
	free(value);
	value=NULL;
	free(MSG);
	MSG=NULL;

	return 0;
}
