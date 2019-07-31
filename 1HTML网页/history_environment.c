#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "memory_cgi_a9.h"
#include "cgic.h"

int cgiMain()
{
	int ret;
	int x=240;
	//MSG=(message_env_t*)malloc(sizeof(message_env_t));

	ret=key_init();
	if(ret<0){
		printf("key error\n");
		return -1;
	}

	ret=memory_history_create();
	if(ret<0){
		printf("memory error\n");
		return -1;
	}
	
	ret=memory_order_create();
	if(ret<0){
		printf("memory error\n");
		return -1;
	}


	semop_semval_order_init();
	semop_semval_history_init();

	MSG=(message_env_t*)order_address;
	MSG->type=CGI_HISTORY;
	strncpy(MSG->head,"st:",3);
	usleep(100);
	while(1)
	{
		//do{
			//ret=semop(history_semid,history_op_t,2);
		//}while(ret<0);
		//strnpcy((char*)MSG,msg_address,sizeof(message_env_t));
		//MSG=(message_env_t*)history_address;



		cgiHeaderContentType("text/html");

		printf("<html><head><title>Untitled</title>\
				<meta http-equiv=\"content-type\" content=\"text/html; charset=iso-8859-1\">\
				<meta name=\"generator\" content=\"Web Page Maker (unregistered version)\">\
				<style type=\"text/css\">\
				/*----------Text Styles----------*/\
				.ws6 {font-size: 8px;}\
				.ws7 {font-size: 9.3px;}\
				.ws8 {font-size: 11px;}\
				.ws9 {font-size: 12px;}\
				.ws10 {font-size: 13px;}\
				.ws11 {font-size: 15px;}\
				.ws12 {font-size: 16px;}\
				.ws14 {font-size: 19px;}\
				.ws16 {font-size: 21px;}\
				.ws18 {font-size: 24px;}\
				.ws20 {font-size: 27px;}\
				.ws22 {font-size: 29px;}\
				.ws24 {font-size: 32px;}\
				.ws26 {font-size: 35px;}\
				.ws28 {font-size: 37px;}\
				.ws36 {font-size: 48px;}\
				.ws48 {font-size: 64px;}\
				.ws72 {font-size: 96px;}\
				.wpmd {font-size: 13px;font-family: 'Arial';font-style: normal;font-weight: normal;}\
				/*----------Para Styles----------*/\
				DIV,UL,OL /* Left */\
				{\
					margin-top: 0px;\
						margin-bottom: 0px;\
				}\
		</style>\
			</head><body>\
			<div id=\"back_image\" style=\"position:absolute; overflow:hidden; left:0px; top:0px; width:1920px; height:1080px; z-index:0\"><img src=\"/images/1563976566594.jpg\" alt=\"\" title=\"\" border=0 width=1920 height=1080></div>\
			<div id=\"information_history\" style=\"position:absolute; overflow:hidden; left:400px; top:%dpx; width:736px; height:521px; z-index:1\">\
			<div class=\"wpmd\">\
			<div><font color=\"#000000\" class=\"ws26\"history_address:%s......</font></div>\
			</div></div>\
			<div id=\"title\" style=\"position:absolute; overflow:hidden; left:380px; top:140px; width:276px; height:46px; z-index:2\">\
			<div class=\"wpmd\">\
			<div><font face=\"Microsoft YaHei UI\" class=\"ws26\">&#20179;&#24211;&#30340;&#21382;&#21490;&#20449;&#24687;</font></div>\
			</div></div>\
			<div style=\"position:absolute;left:0;top:1090px;z-index:999\"><a href=\"http://www.webpage-maker.com\"><img border=0 src=\"/images/wpmhome.gif\" alt=\"Web Page Maker, create your own web pages.\"</a></div>\
			</body></html>",x,history_address);
			x+=70;

		if(history_address[0]=='\0')
			break;
		usleep(1);
	}
	return 0;
}

