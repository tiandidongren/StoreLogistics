#CC=gcc
#ORDER=sudo cp *.cgi /boa/cgi-bin/
CC=arm-none-linux-gnueabi-gcc
ORDER=sudo cp *.cgi ~/rootfs/boa/cgi-bin/
all:
	$(CC) history_photo.c cgic.c memory_cgi_a9.c -o history_photo.cgi
	$(CC) history_environment.c cgic.c memory_cgi_a9.c -o history_environment.cgi
	$(CC) environment.c cgic.c memory_cgi_a9.c -o environment.cgi
	$(CC) camera.c cgic.c memory_cgi_a9.c -o camera.cgi
	$(CC) control_m0.c cgic.c memory_cgi_a9.c choose_button_value.c -o control_m0.cgi
	$(ORDER)
	
.PHONY:
clean:
	rm *.cgi
