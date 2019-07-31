#include<stdio.h>
#include<pthread.h>
#include<signal.h>
//#include<sqlite3.h>

#include"public.h"
#include"sqlite3.h"
#include"sqliteAndPthread.h"


//#define DEBUG_MY

int main(int argc, const char *argv[])
{
	int ret;
#ifndef DEBUG_MY	
	if(argc!=2){
		printf("Please enter:%s USBdevname\n");
		return -1;
	}
#endif
	//创建数据库或者打开数据库
	if(sqlite3_open("/history.db",&db)){
		fprintf(stderr,"open history.db is fail!,error:%s\n",
				sqlite3_errmsg(db));
		return -1;
	}
	printf("open success\n");
	MSG=(message_env_t*)malloc(sizeof(message_env_t));
	if(NULL==MSG){
		printf("create message_env_t is fail\n");
		return -1;
	}

#ifndef DEBUG_MY	
	ret=open_port(argv[1]);
	if(ret<0){
		printf("open fail\n");
		return -1;
	}
#endif

	//注册信号处理函数,一旦ctrl+c结束进程,则将
	//进成的资源释放
	signal(SIGINT,sighandler_free_resource);
	//初始化互斥锁
	ret=pthread_mutex_init(&mutex,NULL);
	if(ret<0){
		printf("init mutex is fail\n");
		return -1;
	}
	
	//对号量的操作和信号量的值初始化,在调用共享内存和信号灯集前调用
 	semop_semval_init();

	//调用初始化钥匙key,成功返回0,失败返回-1
	ret=key_init();
	if(ret<0)
	{
		printf("init key error\n");
		return -1;
	}

	//调用创建或打开共享内存的函数,失败返回-1
	ret=memory_create();
	if(ret<0)
	{
		printf("create memory error\n");
		return -1;
	}

	//调用创建信号灯集的函数,失败返回-1
	ret=sem_create();
	if(ret<0){
		printf("create sem error\n");
		return -1;
	}

	//创建接受客户端请求的线程,线程创建成功返回0,失败返回错误码,调试时使用
	ret=pthread_create(&id_client_request,NULL,pthread_client_request,NULL);
	if(ret<0)
	{
		return 0;
	}
	//创建接受M0数据的线程
	ret=pthread_create(&id_recv_M0_msg,NULL,pthread_recv_M0_msg,NULL);
	if(ret<0)
	{
		return 0;
	}
	//创建将结构体数据同步到客户端,并保存在数据库中
	ret=pthread_create(&id_send_msg_to_client,NULL,pthread_send_msg_to_client,NULL);
	if(ret<0)
	{
		return 0;
	}
	//处理摄像头的线程
	ret=pthread_create(&id_cemera,NULL,pthread_cemera,NULL);
	if(ret<0)
	{
		return 0;
	}

	char *ch=(char*)malloc(20);
	memset(ch,0,20);
	while(1)
	{
	}

	return 0;
}
