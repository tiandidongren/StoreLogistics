#include<time.h>
#include<error.h>
#include<stdlib.h>

#include"sqliteAndPthread.h"

//线君应是循环阻塞等待???

//线程的要执行的函数
void * pthread_client_request(void*empty)
{
	message_env_t *msg_env;
	msg_env=(message_env_t*)malloc(sizeof(message_env_t));

	//使用信号量,阻塞接受,然后读取共享内存二中的数据
	//
	//
	

	printf("pthread_client_request\n");
	if(CGI_ORDER==msg_env->type)
	{
		//将数据发送给M0,调用发送命令的线程
	}
	if(CGI_HISTORY==msg_env->type)
	{
		//查询数据库,将查询到的信息逐条写入共享内存二中
		//此处应注意,不要与共享内存一(用以实时同步数据)的
		//共享内存冲突,二者使用两个共享内存
		//调用数据库线程,使用后销毁
	}
	
}

void * pthread_recv_M0_msg(void*empty)
{
	//从Zigbee或者串口中读取数据,阻塞等待读取
	//并将尝试获取互斥锁一,成功时将数据填充到结构体中,
	//失败返回(pthread_mutex_trylock)
	printf("pthread_recv_M0_msg\n");
}

void * pthread_send_msg_to_client(void*empty)
{
	//使用pthread_mutex_lock,上互斥锁一失败等待,
	//成功后,将结构体数据写入共享内存一中,然后释放
	//锁一,并对信号量进行操作(可在锁外进行)
	printf("pthread_send_msg_to_client\n");
}

void * pthread_cemera(void*empty)
{
	printf("pthread_cemera\n");
}

//该线程可能无用?????,查询数据库历史的线程
void * pthread_sqlite(void*empty)
{
	printf("pthread_sqlite\n");
}

//下达命令的线程
void * pthread_send_order_to_M0(void*empty)
{
	printf("pthread_send_order_to_M0\n");
}

//数据库的操作,只需要添加数据,和查询全部即可
void sqlite_add_data(message_env_t* data)
{
	char *sql,*ptr_time,*errmsg;
	char *send_msg;
	time_t time_data;
	if(time(&time_data)<0)
	{
		perror("get time");
		return ;
	}

	ptr_time=ctime(&time_data);
	if(NULL==ptr_time)
	{
		printf("change sec is fail\n");
		return ;
	}
	//对温度的正负进行判断,
	if(data->temp[0]>128)
	{
		sprintf(sql,"insert into storemsg values('%c',-%d,%d,\
			%d,%d,%d,%d,%d,%d,%d,%d,'%s')",\
				data->snum,data->temp[0],data->temp[1],\
				data->hum[0],data->hum[1],data->x,\
				data->y,data->z,data->ill,data->bet,\
				data->adc,ptr_time);

		sprintf(send_msg,"store:%d\ntemp:-%d.%d\nhum:%d.%d\nx,y,z:%d,%d,%d\n\
				ill:%d\nbet:%d\nadc:%d\n",\
				data->snum,data->temp[0],data->temp[1],\
				data->hum[0],data->hum[1],data->x,\
				data->y,data->z,data->ill,data->bet,\
				data->adc);
	}
	else
	{
		sprintf(sql,"insert into storemsg values('%c',%d,%d,\
			%d,%d,%d,%d,%d,%d,%d,%d,'%s')",\
				data->snum,data->temp[0],data->temp[1],\
				data->hum[0],data->hum[1],data->x,\
				data->y,data->z,data->ill,data->bet,\
				data->adc,ptr_time);

		sprintf(send_msg,"store:%d\n\
				temp:%d.%d\n\
				hum:%d.%d\n\
				x,y,z:%d,%d,%d\n\
				ill:%d\n\
				bet:%d\n\
				adc:%d\n",\
				data->snum,data->temp[0],data->temp[1],\
				data->hum[0],data->hum[1],data->x,\
				data->y,data->z,data->ill,data->bet,\
				data->adc);
	}

	//此处应有函数处理,将send_msg发送给CGI
	//
	//
	
	
	if(sqlite3_exec(db,sql,NULL,NULL,&errmsg)!=SQLITE_OK)
	{
		printf("insert data is fail,error:%s\n",errmsg);
		return ;
	}

	printf("insert OK!\n");
}

void sqlite_inquity(void)
{
	char **result;
	int pn_row,pn_col;
	char *errmsg;

	char *sql;
	char *send_msg;

	sprintf(sql,"select * from storemsg");
	if(sqlite3_get_table(db,sql,&result,&pn_row,&pn_col,&errmsg)!=SQLITE_OK)
	{
		printf("error:%s\n",errmsg);
		return ;
	}
	else
	{
		if(0==pn_row)
		{
			printf("now no store data\n");
			return ;
		}
		else
		{
			int i=1;
			for(;i<pn_row;i++)
			{
				sprintf(send_msg,"store:%s\n\
						temp:%s.%s\n\
						hum:%s.%s\n\
						x,y,z:%s.%s.%s\n\
						ill:%s\n\
						bet:%s\n\
						adc:%s\n\
						time:%s\n",\
						result[i*pn_col],result[i*pn_col+1],\
						result[i*pn_col+2],result[i*pn_col+3],\
						result[i*pn_col+4],result[i*pn_col+5],\
						result[i*pn_col+6],result[i*pn_col+7],\
						result[i*pn_col+8],result[i*pn_col+9],\
						result[i*pn_col+10],result[i*pn_col+11]
					   );
				//此处应有函数处理,将send_msg发送给CGI
				//
				//
			}
		}
	}

}

