#include "choose_button_value.h"

//通过判断那个button按钮来返回设备号
int ret_equipment_id(char *name)
{
	cgiFormString("formbutton1",name,15);  
	if(name[0]!=0){
		return EQUI_BUZZER;
	}
	cgiFormString("formbutton3",name,15);  
	if(name[0]!=0){
		return EQUI_LED;
	}
	cgiFormString("formbutton4",name,15);  
	if(name[0]!=0){
		return EQUI_FUN;
	}
	cgiFormString("formbutton5",name,15);  
	if(name[0]!=0){
		return EQUI_PIPE;
	}

	return -1;
}

//根据相应的设备号调用相应的函数判断设备命令
void control_fun(char *val)
{
	cgiFormString("formradio2",val,20);  
	if(*val=='0')
		*val=0;
	if(*val='1')
		*val=1;
	if(*val='2')
		*val=2;
	if(*val='3')
		*val=3;
}

void control_led(char *val)
{
	cgiFormString("formradio3",val,20);  
	if(*val=='0')
		*val=0;
	if(*val='1')
		*val=1;
}

void control_buzzer(char *val)
{
	cgiFormString("formradio1",val,20);  
	if(*val=='0')
		*val=0;
	if(*val='1')
		*val=1;
}

void control_pipe(char *val)
{
	cgiFormString("formradio4",val,20);  
	if(*val=='0')
		*val=0;
	if(*val=='1')
	{
		cgiFormString("formtext4",val,20);  
		*val=*val-'0';
	}
}
