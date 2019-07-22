#ifndef SQLITEANDPTHREAD_H_
#define SQLITEANDPTHREAD_H_

#include<stdio.h>
#include<pthread.h>
#include<sqlite3.h>


#include"public.h"

sqlite3 *db;
message_env_t MSG;

// 	  对于上锁,在对结构体操作的两个信息传递的进程使用全局的变量.
//
//
//
// 	  对于下发命令的进程而言,下达的给M0的命令可以在使用时
//创建临时变量,结束后销毁即可.但是在上传历史记录时,与CGI的通讯
//会用到共享内存,可以写入共享内存的前后加入互斥锁,保证在同一时间
//只能上传历史记录或者实时同步信息
//
//
//
//为了避免对共享内存使用与CGI造成静态的问题,使用信号量(或者说信号灯)
//来保护共享内存

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


//数据库的操作,只需要添加数据,和查询全部即可
//对storemsg表进行数据的插入,并同时讲时间插入
void sqlite_add_data(message_env_t* data);
//查询并讲查询到的历史数据通过???函数传递给CGI
void sqlite_inquity(void);
#endif
