#include "choose_button_value.h"

//通过判断那个button按钮来返回设备号
int ret_equipment_id(char *name)
{
	cgiFormString("formbutton1",name,15);  
	if(!strcmp(name,"提交")){
		return EQUI_BUZZER;
	}
	cgiFormString("formbutton3",name,15);  
	if(!strcmp(name,"提交")){
		return EQUI_LED;
	}
	cgiFormString("formbutton4",name,15);  
	if(!strcmp(name,"提交")){
		return EQUI_FUN;
	}
	cgiFormString("formbutton5",name,15);  
	if(!strcmp(name,"提交")){
		return EQUI_PIPE;
	}

	return -1;
}

//根据相应的设备号调用相应的函数判断设备命令
void control_fun(char *val)
{
	cgiFormString("fun_close",name,15);  
	if(1==name[0]){
		*val=FUN_CLOSE;
		return ;
	}
	
	cgiFormString("fun_first",name,15);  
	if(1==name[0]){
		*val=FUN_LEVEL1;
		return ;
	}
	
	cgiFormString("fun_two",name,15);  
	if(1==name[0]){
		*val=FUN_LEVEL2;
		return ;
	}

	cgiFormString("fun_three",name,15);  
	if(1==name[0]){
		*val=FUN_LEVEL3;
		return ;
	}
}

void control_led(char *val)
{
	cgiFormString("led_close",name,15);  
	if(1==name[0]){
		*val=LED_CLOSE;
		return ;
	}
	
	cgiFormString("led_open",name,15);  
	if(1==name[0]){
		*val=LED_OPEN;
		return ;
	}	
}

void control_buzzer(char *val)
{
	cgiFormString("buzzer_close",name,15);  
	if(1==name[0]){
		*val=BUZZER_CLOSE;
		return ;
	}
	
	cgiFormString("buzzer_open",name,15);  
	if(1==name[0]){
		*val=BUZZER_OPEN;
		return ;
	}	
}

void control_pipe(char *val)
{
	cgiFormString("pipe_close",name,15);  
	if(1==name[0]){
		*val=PIPE_CLOSE;
		return ;
	}
	
	cgiFormString("pipe_open",name,15);  
	if(1==name[0]){





		return ;
	}	
}
