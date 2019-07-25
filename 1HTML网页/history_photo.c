#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


#include "cgic.h"

int cgiMain()
{
	cgiHeaderContentType("text/html");

	int aaa=0;
	while(1)
	{

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
		</style></head><body>\
			<div id=\"back_image\" style=\"position:absolute; overflow:hidden; left:0px; top:0px; width:1920px; height:1080px; z-index:0\"><img src=\"/images/1563976662342.jpg\" alt=\"\" title=\"\" border=0 width=1920 height=1080></div>\
			<div id=\"photo_history\" style=\"position:absolute; overflow:hidden; left:420px; top:260px; width:736px; height:521px; z-index:1\">\
			<div class=\"wpmd\">\
			<div><font color=\"#FFFFFF\" class=\"ws26\">%d\b</font></div>\
			</div></div>\
			<div id=\"title\" style=\"position:absolute; overflow:hidden; left:420px; top:160px; width:276px; height:46px; z-index:2\">\
			<div class=\"wpmd\">\
			<div><font color=\"#FFFFFF\" face=\"Microsoft YaHei UI\" class=\"ws26\">&#21382;&#21490;&#29031;&#29255;&#20449;&#24687;</font></div>\
			</div></div>\
			<div style=\"position:absolute;left:0;top:1090px;z-index:999\"><a href=\"http://www.webpage-maker.com\"><img border=0 src=\"images/wpmhome.gif\" alt=\"Web Page Maker, create your own web pages.\"</a></div>\
			</body></html>",aaa);
		aaa+=10;
		sleep(1);
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
		</style></head><body>\
			<div id=\"back_image\" style=\"position:absolute; overflow:hidden; left:0px; top:0px; width:1920px; height:1080px; z-index:0\"><img src=\"/images/1563976662342.jpg\" alt=\"\" title=\"\" border=0 width=1920 height=1080></div>\
			<div><font color=\"#000000\" class=\"ws26\">      </font></div>\
			</body></html>");

			
	}
	return 0;
}
