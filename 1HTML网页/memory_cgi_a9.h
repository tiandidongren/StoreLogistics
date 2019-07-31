#ifndef MEMORY_CGI_A9_H_
#define MEMORY_CGI_A9_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <sys/sem.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <errno.h>
#include <signal.h>
#include <fcntl.h>

#include "public.h"

#define MEMORY_LEN 1024
//union semun{
//	int val;
//};

int fd_usb_M0; 	//与M0通讯的文件描述符

message_env_t* MSG; 			//接收并同步信息的

pthread_mutex_t mutex; 		//用来保护全局变量的结构体

key_t msg_key_add, 				//同步实时信息用的key,共享内存和信号量
	  order_key_add, 			//CGI下达命令用的key
	  history_key_add; 			//上传历史数据的key
key_t msg_key_sem, 				//同步实时信息用的key,共享内存和信号量
	  order_key_sem, 			//CGI下达命令用的key
	  history_key_sem; 			//上传历史数据的key

int msg_semid,order_semid,history_semid;
int msg_shm,order_shm,history_shm;

//union semun msg_val_t[2];
struct sembuf msg_op_t[2]; 	//用来处理同步信息的共享内存的信号量{
char *msg_address;

//union semun order_val_t[2];
struct sembuf order_op_t[2];	//用来处理命令的信号量{
char *order_address;

//union semun history_val_t[2];
struct sembuf history_op_t[2]; 	//用来处理命令的信号量
char *history_address;

//对信号量的操作和信号量的值初始化,在调用共享内存和信号灯集前调用
void semop_semval_msg_init(void);
//对信号量的操作和信号量的值初始化,在调用共享内存和信号灯集前调用
void semop_semval_order_init(void);
//对信号量的操作和信号量的值初始化,在调用共享内存和信号灯集前调用
void semop_semval_history_init(void);
//对key的初始化,成功返回0,失败返回-1
int key_init(void);
//对共享内存进行初始化病进行映射,成功返回0,失败返回-1
int memory_msg_create(void);
//对共享内存进行初始化病进行映射,成功返回0,失败返回-1
int memory_order_create(void);
//对共享内存进行初始化病进行映射,成功返回0,失败返回-1
int memory_history_create(void);
//创建信号灯集,成功返回0,失败返回-1
int sem_msg_create(void);
//创建信号灯集,成功返回0,失败返回-1
int sem_order_create(void);
//创建信号灯集,成功返回0,失败返回-1
int sem_history_create(void);



#endif
