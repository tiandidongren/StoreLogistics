#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "cgic.h"
#include "public.h"
#include "memory_cgi_a9.h"

int cgiMain()
{
	int ret;

	//MSG=(message_env_t*)malloc(sizeof(message_env_t));

	ret=key_init();
	if(ret<0){
		printf("key error\n");
		return -1;
	}

	ret=memory_msg_create();
	if(ret<0){
		printf("memory error\n");
		return -1;
	}

	semop_semval_msg_init();

	do{
		ret=semop(msg_semid,msg_op_t,2);
	}while(ret<0);
	//strnpcy((char*)MSG,msg_address,sizeof(message_env_t));
	MSG=(message_env_t*)msg_address;

	cgiHeaderContentType("text/html");	

	printf("\
			<html>\
			<head>\
			<title>Untitled</title>\
			<meta http-equiv=\"gcontent-type\" content=\"text/html; charset=iso-8859-1\">\
			<meta name=\"ggenerator\" content=\"Web Page Maker (unregistered version)\">\
			<style type=\"gtext/css\">\
			/*----------Text Styes----------*/\
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
		<div id=\"gback_image\" style=\"position:absolute; overflow:hidden; left:0px; top:0px; width:1920px; height:1080px; z-index:0\"><img src=\"/images/1563976648743.jpg\" alt=\"\" title=\"\" border=0 width=1920 height=1080></div>\
		<div id=\"ginformation_show\" style=\"position:absolute; overflow:hidden; left:380px; top:200px; width:736px; height:521px; z-index:1\">\
		<div class=\"gwpmd\">\
		<div><font class=\"gws26\">\
		temp:%c.%c\n\
		hum:%c.%c\n\
		x,y,z:%c,%c,%c\
		ill:%d\
		bet:%d\
		adc:%d\
		ret:%d\n\
		</font></div>\
		</div></div>\
		<div id=\"gtitle\" style=\"position:absolute; overflow:hidden; left:380px; top:140px; width:276px; height:46px; z-index:2\">\
		<div class=\"gwpmd\">\
		<div><font face=\"gMicrosoft YaHei UI\" class=\"ws26\">&#20179;&#24211;&#30340;&#23454;&#26102;&#20449;&#24687;</font></div>\
		</div></div>\
		<div style=\"gposition:absolute;left:0;top:1090px;z-index:999\"><a href=\"http://www.webpage-maker.com\"><img border=0 src=\"images/wpmhome.gif\" alt=\"Web Page Maker, create your own web pages.\"</a></div>\
		</body></html>",\
		MSG->temp[0],MSG->temp[1],MSG->hum[0],MSG->hum[1],\
		MSG->x,MSG->y,MSG->z,MSG->ill,MSG->bet,MSG->adc,ret);

	return 0;
}


