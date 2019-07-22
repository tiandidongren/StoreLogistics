#include<stdio.h>
#include<pthread.h>
#include<sqlite3.h>

//#include"exynos4412.h"
#include"public.h"
#include"sqliteAndPthread.h"

pthread_t id_client_request, 	//处理客户端请求,根据相应请求调用数据库线程或者下发命令的线程
		  id_recv_M0_msg, 		//处理M0发送来的数据,并填充到结构体中
		  id_send_msg_to_client,//将结构体中的数据同步刷新到网页上,并存储到数据库中
		  id_cemera, 			//处理摄像头
		  id_sqlite, 			//调用数据库,并将查询结果返回给客户端
		  id_send_order_to_M0;  //将客户端的命令信息下发给M0




int main(int argc, const char *argv[])
{
	//创建数据库或者打开数据库
	if(sqlite3_open("history.db",&db))
	{
		fprintf(stderr,"open history.db is fail!,error:%s\n",
				sqlite3_errmsg(db));
		return -1;
	}


	int ret;
	//创建接受客户端请求的线程,线程创建成功返回0,失败返回错误码,调试时使用
	ret=pthread_create(&id_client_request,NULL,pthread_client_request,NULL);
	if(ret<0)
	{
		printf("+++\n");
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
	//创建客户端查询数据库的进程
	ret=pthread_create(&id_sqlite,NULL,pthread_sqlite,NULL);
	if(ret<0)
	{
		return 0;
	}
	//创建传递客户端控制M0设备信息的线程.
	ret=pthread_create(&id_send_order_to_M0,NULL,pthread_send_order_to_M0,NULL);
	if(ret<0)
	{
		return 0;
	}
	return 0;
}
