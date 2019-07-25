all:
	gcc history_photo.c cgic.c memory_cgi_a9.c -o history_photo.cgi
	gcc history_environment.c cgic.c memory_cgi_a9.c -o history_environment.cgi
	gcc environment.c cgic.c memory_cgi_a9.c -o environment.cgi
	gcc camera.c cgic.c memory_cgi_a9.c -o camera.cgi
	gcc control_m0.c cgic.c memory_cgi_a9.c -o control_m0.cgi
	sudo cp *.cgi /boa/cgi-bin/
	#sudo cp *.cgi ~/rootfs/boa/cgi-bin/
	
.PHONY:
clean:
	rm *.cgi
