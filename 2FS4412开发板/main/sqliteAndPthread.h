#ifndef SQLITEANDPTHREAD_H_
#define SQLITEANDPTHREAD_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <sys/sem.h>
#include <errno.h>
#include <time.h>
#include <signal.h>

#include"public.h"
#include "sqlite3.h"

#define MEMORY_LEN 1024
union semun{
	int val;
};

sqlite3 *db; 				//数据库指针
message_env_t* MSG; 			//接收并同步信息的

pthread_t id_client_request, 	//处理客户端请求,根据相应请求调用数据库线程或者下发命令的线程
		  id_recv_M0_msg, 		//处理M0发送来的数据,并填充到结构体中
		  id_send_msg_to_client,//将结构体中的数据同步刷新到网页上,并存储到数据库中
		  id_cemera, 			//处理摄像头
		  id_sqlite, 			//调用数据库,并将查询结果返回给客户端
		  id_send_order_to_M0;  //将客户端的命令信息下发给M0




pthread_mutex_t mutex; 		//用来保护全局变量的结构体

key_t msg_key, 				//同步实时信息用的key,共享内存和信号量
	  order_key, 			//CGI下达命令用的key
	  history_key; 			//上传历史数据的key

int msg_semid,order_semid,history_semid;
int msg_shm,order_shm,history_shm;

union semun msg_val_t[2];
struct sembuf msg_op_t[2]; 	//用来处理同步信息的共享内存的信号量{
char *msg_address;

union semun order_val_t[2];
struct sembuf order_op_t[2];	//用来处理命令的信号量{
char *order_address;

union semun history_val_t[2];
struct sembuf history_op_t[2]; 	//用来处理命令的信号量
char *history_address;

//线程的要执行的函数
//处理客户端请求
void * pthread_client_request(void*);
//接受M0的信息并填充结构体,应该是一直运行的
void * pthread_recv_M0_msg(void*);
//将结构体中的数据同步个CGI,并在网页上显示,该线程应该在
//结构体在填充后,调用数据库的函数,将数据存储到数据库中
void * pthread_send_msg_to_client(void*);
//对摄像头进行处理
void * pthread_cemera(void*);
void * pthread_sqlite(void*);
//将客户端的命令信息下发给M0
void * pthread_send_order_to_M0(void*);

//对信号量的操作和信号量的值初始化,在调用共享内存和信号灯集前调用
void semop_semval_init(void);
//对key的初始化,成功返回0,失败返回-1
int key_init(void);
//对共享内存进行初始化病进行映射,成功返回0,失败返回-1
int memory_create(void);
//创建信号灯集,成功返回0,失败返回-1
int sem_create(void);

//数据库的操作,只需要添加数据,和查询全部即可
//对storemsg表进行数据的插入,并同时讲时间插入
void sqlite_add_data(message_env_t* data);
//查询并讲查询到的历史数据通过???函数传递给CGI
void sqlite_inquity(void);

//使用信号处理函数,回收线程资源
void sighandler_free_resource(int sig);

#endif
