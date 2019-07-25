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

	ret=memory_order_create();
	if(ret<0){
		printf("memory error\n");
		return -1;
	}

	semop_semval_order_init();

	cgiHeaderContentType("text/html");

	printf("<html>\
			<head>\
			<title>Untitled</title>\
			<meta http-equiv=\"content-type\" content=\"text/html; charset=iso-8859-1\">\
			<meta name=\"generator\" content=\"Web Page Maker (unregistered version)\">\
			<style type=\"text/css\">\
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
			DIV,UL,OL /* Left */\
			{\
				margin-top: 0px;\
					margin-bottom: 0px;\
			}\
	</style>\
		</head>\
		<body>\
		<div id=\"back_image\" style=\"position:absolute; overflow:hidden; left:0px; top:0px; width:1920px; height:1080px; z-index:0\"><img src=\"/images/1563976593863.jpg\" alt=\"\" title=\"\" border=0 width=1920 height=1080></div>\
		<div id=\"return\" style=\"position:absolute; overflow:hidden; left:1120px; top:380px; width:177px; height:52px; z-index:1\">\
		<a href=\"/store_first.html\"><div class=\"wpmd\">\
		<div><font face=\"Microsoft YaHei UI\" class=\"ws26\">&#36820;&#22238;&#19978;&#19968;&#32423;</font></div>\
		</div></a></div>\
		<input name=\"formbutton5\" type=\"submit\" value=\"提交\" style=\"position:absolute;left:860px;top:540px;z-index:2\">\
		<div id=\"pipe_close\" style=\"position:absolute; left:680px; top:560px; z-index:3\"><input type=\"radio\" name=\"formradio4\" checked></div>\
		<div id=\"pipe_label_close\" style=\"position:absolute; overflow:hidden; left:640px; top:560px; width:48px; height:24px; z-index:4\">\
		<div class=\"wpmd\">\
		<div><font color=\"#FFFFFF\" face=\"Microsoft YaHei UI\" class=\"ws12\">&#20851;&#38381;&#65306;</font></div>\
		</div></div>\
		<input name=\"formtext4\" type=\"text\" style=\"position:absolute;width:66px;left:740px;top:520px;z-index:5\">\
		<div id=\"pipe_open\" style=\"position:absolute; left:680px; top:520px; z-index:6\"><input type=\"radio\" name=\"formradio4\" checked></div>\
		<div id=\"pipe_label_open\" style=\"position:absolute; overflow:hidden; left:640px; top:520px; width:52px; height:24px; z-index:7\">\
		<div class=\"wpmd\">\
		<div><font face=\"Microsoft YaHei UI\" class=\"ws12\">&#26174;&#31034;&#65306;</font></div>\
		</div></div>\
		<div id=\"pipe_label\" style=\"position:absolute; overflow:hidden; left:520px; top:540px; width:88px; height:24px; z-index:8\">\
		<div class=\"wpmd\">\
		<div><font color=\"#FFFFFF\" face=\"Microsoft YaHei UI\" class=\"ws12\">&#25968;&#25511;&#31649;&#65306;</font></div>\
		</div></div>\
		<input name=\"formbutton3\" type=\"submit\" value=\"提交\" style=\"position:absolute;left:860px;top:440px;z-index:9\">\
		<div id=\"led_open\" style=\"position:absolute; left:780px; top:440px; z-index:10\"><input type=\"radio\" name=\"formradio3\"></div>\
		<div id=\"led_label_open\" style=\"position:absolute; overflow:hidden; left:740px; top:440px; width:49px; height:24px; z-index:11\">\
		<div class=\"wpmd\">\
		<div><font face=\"Microsoft YaHei UI\" class=\"ws12\">&#24320;&#21551;&#65306;</font></div>\
		</div></div>\
		<div id=\"led_close\" style=\"position:absolute; left:680px; top:440px; z-index:12\"><input type=\"radio\" name=\"formradio3\" checked></div>\
		<div id=\"led_label_close\" style=\"position:absolute; overflow:hidden; left:640px; top:440px; width:49px; height:24px; z-index:13\">\
		<div class=\"wpmd\">\
		<div><font face=\"Microsoft YaHei UI\" class=\"ws12\">&#20851;&#38381;&#65306;</font></div>\
		</div></div>\
		<div id=\"led\" style=\"position:absolute; overflow:hidden; left:520px; top:440px; width:63px; height:24px; z-index:14\">\
		<div class=\"wpmd\">\
		<div><font face=\"Microsoft YaHei UI\" class=\"ws12\">LED&#28783;&#65306;</font></div>\
		</div></div>\
		<input name=\"formbutton4\" type=\"submit\" value=\"提交\" style=\"position:absolute;left:860px;top:340px;z-index:15\">\
		<div id=\"fun_three\" style=\"position:absolute; left:780px; top:360px; z-index:16\"><input type=\"radio\" name=\"formradio2\"></div>\
		<div id=\"fun_label_three\" style=\"position:absolute; overflow:hidden; left:740px; top:360px; width:50px; height:24px; z-index:17\">\
		<div class=\"wpmd\">\
		<div><font face=\"Microsoft YaHei UI\" class=\"ws12\">&#19977;&#26723;&#65306;</font></div>\
		</div></div>\
		<div id=\"fun_two\" style=\"position:absolute; left:680px; top:360px; z-index:18\"><input type=\"radio\" name=\"formradio2\"></div>\
		<div id=\"fun_label_two\" style=\"position:absolute; overflow:hidden; left:640px; top:360px; width:50px; height:24px; z-index:19\">\
		<div class=\"wpmd\">\
		<div><font face=\"Microsoft YaHei UI\" class=\"ws12\">&#20108;&#26723;&#65306;</font></div>\
		</div></div>\
		<div id=\"fun_first\" style=\"position:absolute; left:780px; top:320px; z-index:20\"><input type=\"radio\" name=\"formradio2\"></div>\
		<div id=\"fun_label_first\" style=\"position:absolute; overflow:hidden; left:740px; top:320px; width:49px; height:24px; z-index:21\">\
		<div class=\"wpmd\">\
		<div><font face=\"Microsoft YaHei UI\" class=\"ws12\">&#19968;&#26723;&#65306;</font></div>\
		</div></div>\
		<div id=\"fun_close\" style=\"position:absolute; left:680px; top:320px; z-index:22\"><input type=\"radio\" name=\"formradio2\" checked></div>\
		<div id=\"fun_label_close\" style=\"position:absolute; overflow:hidden; left:640px; top:320px; width:49px; height:23px; z-index:23\">\
		<div class=\"wpmd\">\
		<div><font face=\"Microsoft YaHei UI\" class=\"ws12\">&#20851;&#38381;&#65306;</font></div>\
		</div></div>\
		<div id=\"fun\" style=\"position:absolute; overflow:hidden; left:520px; top:340px; width:49px; height:24px; z-index:24\">\
		<div class=\"wpmd\">\
		<div><font face=\"Microsoft YaHei UI\" class=\"ws12\">&#39118;&#25159;&#65306;</font></div>\
		</div></div>\
		<input name=\"formbutton1\" type=\"submit\" value=\"提交\" style=\"position:absolute;left:860px;top:240px;z-index:25\">\
		<div id=\"buzzer_open\" style=\"position:absolute; left:780px; top:240px; z-index:26\"><input type=\"radio\" name=\"formradio1\"></div>\
		<div id=\"buzzer_label_open\" style=\"position:absolute; overflow:hidden; left:740px; top:240px; width:49px; height:25px; z-index:27\">\
		<div class=\"wpmd\">\
		<div><font face=\"Microsoft YaHei UI\" class=\"ws12\">&#24320;&#21551;&#65306;</font></div>\
		</div></div>\
		<div id=\"buzzer_close\" style=\"position:absolute; left:680px; top:240px; z-index:28\"><input type=\"radio\" name=\"formradio1\" checked></div>\
		<div id=\"buzzer_label_close\" style=\"position:absolute; overflow:hidden; left:640px; top:240px; width:49px; height:24px; z-index:29\">\
		<div class=\"wpmd\">\
		<div><font face=\"Microsoft YaHei UI\" class=\"ws12\">&#20851;&#38381;&#65306;</font></div>\
		</div></div>\
		<div id=\"buzzer\" style=\"position:absolute; overflow:hidden; left:520px; top:240px; width:75px; height:24px; z-index:30\">\
		<div class=\"wpmd\">\
		<div><font face=\"Microsoft YaHei UI\" class=\"ws12\">&#34562;&#40483;&#22120;&#65306;</font></div>\
		</div></div>\
		<div id=\"title\" style=\"position:absolute; overflow:hidden; left:660px; top:120px; width:239px; height:42px; z-index:31\">\
		<div class=\"wpmd\">\
		<div><font class=\"ws22\">M 0 &#25511;&#21046;&#36873;&#39033;</font></div></div></div>\
		<div style=\"position:absolute;left:0;top:1090px;z-index:999\"><a href=\"http://www.webpage-maker.com\"><img border=0 src=\"images/wpmhome.gif\" alt=\"Web Page Maker, create your own web pages.\"</a></div></body></html>");



	return 0;
}
