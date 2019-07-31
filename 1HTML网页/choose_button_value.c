#include "choose_button_value.h"

char *html_num[]={
	"0","1","2","3"};

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
	int num;
	cgiFormRadio("formradio2",html_num,4,&num,0);
	if(num==0)
		*val=0;
	if(num==1)
		*val=1;
	if(num==2)
		*val=2;
	if(num==3)
		*val=3;
}

void control_led(char *val)
{
	int num;
	cgiFormRadio("formradio3",html_num,4,&num,0);
	if(num==0)
		*val=0;
	if(num==1)
		*val=1;
}

void control_buzzer(char *val)
{
	int num;
	cgiFormRadio("formradio1",html_num,4,&num,0);
	if(num==0)
		*val=0;
	if(num==1)
		*val=1;
}

void control_pipe(char *val)
{
	int num;
	cgiFormRadio("formradio4",html_num,4,&num,0);
	if(num==0)
		*val=0xf;
	if(num==1)
	{
		cgiFormString("formtext4",val,20);  
		*val=*val-'0';
	}
}
