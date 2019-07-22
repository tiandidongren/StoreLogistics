CC=gcc
#CC=arm-none-linux-gnueabi-gcc
CFLAG=-lpthread -lsqlite3
test:main.o sqliteAndPthread.o
	$(CC) $^ $(CFLAG) -o test
.PHONY:
clean:
	rm test *.o
