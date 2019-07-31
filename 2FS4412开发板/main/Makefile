#CC=gcc
#CFLAG=-lpthread -lsqlite3
CC=arm-none-linux-gnueabi-gcc
CFLAG=-lpthread -L ./lib -lsqlite3
test:main.o sqliteAndPthread.o
	$(CC) $^ $(CFLAG) -o test
	sudo cp test ~/rootfs/
.PHONY:
clean:
	rm test *.o
