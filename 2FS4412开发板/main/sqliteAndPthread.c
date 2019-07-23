#include"sqliteAndPthread.h"

//对信号量的操作和信号量的值初始化
void semop_semval_init(void)
{
	msg_val_t[0].val=1;
	msg_val_t[1].val=0;
	msg_op_t[0].sem_num=0;
	msg_op_t[0].sem_op=-1;
	msg_op_t[0].sem_flg=0;
	msg_op_t[1].sem_num=1;
	msg_op_t[1].sem_op=1;
	msg_op_t[1].sem_flg=0;

	order_val_t[0].val=1;
	order_val_t[1].val=0;
	order_op_t[0].sem_num=0;
	order_op_t[0].sem_op=-1;
	order_op_t[0].sem_flg=0;
	order_op_t[1].sem_num=1;
	order_op_t[1].sem_op=1;
	order_op_t[1].sem_flg=0;

	history_val_t[0].val=1;
	history_val_t[1].val=0;
	history_op_t[0].sem_num=0;
	history_op_t[0].sem_op=-1;
	history_op_t[0].sem_flg=0;
	history_op_t[1].sem_num=1;
	history_op_t[1].sem_op=1;
	history_op_t[1].sem_flg=0;
}
//对key的初始化,成功返回0,失败返回-1
int key_init(void)
{
	msg_key=ftok("/",'A');
	if(msg_key<0){
		perror("msg_key");
		return -1;
	}
	order_key=ftok("/",'B');
	if(order_key<0){
		perror("order_key");
		return -1;
	}
	history_key=ftok("/",'C');
	if(history_key<0){
		perror("history_key");
		return -1;
	}	

	return 0;
}
//对共享内存进行初始化并进行映射,成功返回0,失败返回错误码
int memory_create(void)
{
	int ret;
	msg_shm=shmget(msg_key,MEMORY_LEN,IPC_CREAT|IPC_EXCL|0777);
	if(msg_shm<0){
		if(errno==EEXIST){
			msg_shm=shmget(msg_key,0,0);
		}
		else{
			perror("msg_shm");
			return -1;
		}
	}
	msg_address=shmat(msg_shm,NULL,0);
	if((char*)-1==msg_address){
		perror("msg_address");
		return -1;
	}

	order_shm=shmget(order_key,MEMORY_LEN,IPC_CREAT|IPC_EXCL|0777);
	if(order_shm<0){
		if(errno==EEXIST){
			order_shm=shmget(order_key,0,0);
		}
		else{
			perror("order_shm");
			return -1;
		}
	}
	order_address=shmat(order_shm,NULL,0);
	if((char*)-1==order_address){
		perror("order_address");
		return -1;
	}

	history_shm=shmget(history_key,MEMORY_LEN,IPC_CREAT|IPC_EXCL|0777);
	if(history_shm<0){
		if(errno==EEXIST){
			history_shm=shmget(history_key,0,0);
		}
		else{
			perror("history_shm");
			return -1;
		}
	}
	history_address=shmat(history_shm,NULL,0);
	if((char*)-1==history_address){
		perror("history_address");
		return -1;
	}

	return 0;
}
//创建信号灯集并对其值初始化,成功返回0,失败返回-1
int sem_create(void)
{
	int i; 		//用作循环计数
	msg_semid=semget(msg_key,2,IPC_CREAT|IPC_EXCL|0777);
	if(msg_semid<0){
		if(errno==EEXIST){
			msg_semid=semget(msg_key,2,0);
		}
		else{
			printf("create msg_semid fail\n");
			return -1;
		}
	}
	for(i=0;i<sizeof(msg_val_t)/sizeof(union semun);i++)
	{
		semctl(msg_semid,i,SETVAL,msg_val_t[i]);
	}

	order_semid=semget(order_key,2,IPC_CREAT|IPC_EXCL|0777);
	if(order_semid<0){
		if(errno==EEXIST){
			order_semid=semget(order_key,2,0);
		}
		else{
			printf("create order_semid fail\n");
			return -1;
		}
	}
	for(i=0;i<sizeof(order_val_t)/sizeof(union semun);i++)
	{
		semctl(order_semid,i,SETVAL,order_val_t[i]);
	}

	history_semid=semget(history_key,2,IPC_CREAT|IPC_EXCL|0777);
	if(history_semid<0){
		if(errno==EEXIST){
			history_semid=semget(history_key,2,0);
		}
		else{
			printf("create history_semid fail\n");
			return -1;
		}
	}
	for(i=0;i<sizeof(history_val_t)/sizeof(union semun);i++){
		semctl(history_semid,i,SETVAL,history_val_t[i]);
	}

	printf("create sem successful\n");
	return 0;
}
//线君应是循环阻塞等待???

//线程的要执行的函数
void * pthread_client_request(void*empty)
{
	int ret;
	message_env_t *msg_env;
	msg_env=(message_env_t*)malloc(sizeof(message_env_t));

	while(1)
	{
		//使用命令信号量,读取映射的命令地址的内容到msg_env指针中
		ret=semop(order_semid,order_op_t,2);
		///printf("======\n");

		strncpy((char*)msg_env,order_address,sizeof(message_env_t));
		//此处直接使用msg_env指针指向改地址是否可行?
		//msg_env=(message_env_t*)order_address;
		///printf("++++++\n");

		if(CGI_ORDER==msg_env->type){
			//将数据发送给M0,调用发送命令的线程,发送后销毁
			ret=pthread_create(&id_send_order_to_M0,NULL,pthread_send_order_to_M0,(void*)msg_env);
			if(ret<0){
				printf("send msg to M0 fail");
			}

		}
		if(CGI_HISTORY==msg_env->type){
			//查询数据库,将查询到的信息逐条写入共享内存二中
			//此处应注意,不要与共享内存一(用以实时同步数据)的
			//共享内存冲突,二者使用两个共享内存
			//调用数据库线程,使用后销毁
			ret=pthread_create(&id_sqlite,NULL,pthread_sqlite,NULL);
			if(ret<0){
				printf("check history to client fail");
			}
		}
	}

	//回收线程资源?
}

void * pthread_recv_M0_msg(void*empty)
{
	int ret;
	//从Zigbee或者串口中读取数据,阻塞等待读取
	//并将尝试获取互斥锁一,成功时将数据填充到结构体中,
	//失败返回(pthread_mutex_trylock)
	printf("pthread_recv_M0_msg\n");
	while(1)
	{
		ret=pthread_mutex_trylock(&mutex);
		if(ret<0){
			continue;
		}
		else{
			//将数据存储到MSG中;
			pthread_mutex_unlock(&mutex);
		}
	}
}

void * pthread_send_msg_to_client(void*empty)
{
	//使用pthread_mutex_lock,上互斥锁一失败等待,
	//成功后,将结构体数据写入共享内存一中,然后释放
	//锁一,并对信号量进行操作(可在锁外进行)
	while(1)
	{
		semop(msg_semid,msg_op_t,2);
		printf("pthread_send_msg_to_client\n");
		pthread_mutex_lock(&mutex);
		strncpy(msg_address,(char*)MSG,sizeof(message_env_t));
		msg_address[sizeof(message_env_t)]='\0';
		sqlite_add_data(MSG);
		printf("---------\n");
		pthread_mutex_unlock(&mutex);
		printf("pthread_send_msg_to_client\n");
		sleep(5);
	}
}

void * pthread_cemera(void*empty)
{
	printf("pthread_cemera\n");
}

//该线程可能无用?????,查询数据库历史的线程
void * pthread_sqlite(void*empty)
{
	sqlite_inquity();
	printf("pthread_sqlite\n");
	pthread_exit(0);
}

//下达命令的线程
void * pthread_send_order_to_M0(void*msg_env)
{
	printf("pthread_send_order_to_M0\n");
	pthread_exit(0);
}

//数据库的操作,只需要添加数据,和查询全部即可
void sqlite_add_data(message_env_t* data)
{
	char *sql,*ptr_time,*errmsg;
	char *send_msg;
	//为指针分配空间;
	sql=(char*)malloc(sizeof(1024));
	send_msg=(char*)malloc(sizeof(1024));

	time_t time_data;
	if(time(&time_data)<0){
		perror("get time");
		return ;
	}

	ptr_time=ctime(&time_data);
	if(NULL==ptr_time){
		printf("change sec is fail\n");
		return ;
	}
	printf("_____\n");
	//对温度的正负进行判断,
	if(data->temp[0]>128){
		///printf("true******\n");
		sprintf(sql,"insert into storemsg values('%c',-%d,%d,\
			%d,%d,%d,%d,%d,%d,%d,%d,'%s')",\
			data->snum,data->temp[0],data->temp[1],\
			data->hum[0],data->hum[1],data->x,\
			data->y,data->z,data->ill,data->bet,\
			data->adc,ptr_time);

		///printf("true-----\n");
		sprintf(send_msg,"store:%d\ntemp:-%d.%d\nhum:%d.%d\nx,y,z:%d,%d,%d\n\
				ill:%d\nbet:%d\nadc:%d\n",\
				data->snum,data->temp[0],data->temp[1],\
				data->hum[0],data->hum[1],data->x,\
				data->y,data->z,data->ill,data->bet,\
				data->adc);

		///printf("true+++++\n");
	}
	else{
		///printf("false******\n");
		sprintf(sql,"insert into storemsg values('%c',%d,%d,\
			%d,%d,%d,%d,%d,%d,%d,%d,'%s')",\
			data->snum,data->temp[0],data->temp[1],\
			data->hum[0],data->hum[1],data->x,\
			data->y,data->z,data->ill,data->bet,\
			data->adc,ptr_time);

		///printf("false-----\n");
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
		///printf("fasle+++++\n");
	}
	printf("=====\n");

	if(sqlite3_exec(db,sql,NULL,NULL,&errmsg)!=SQLITE_OK){
		printf("insert data is fail,error:%s\n",errmsg);
		return ;
	}

	printf("insert OK!\n");

	free(sql);
	sql=NULL;
	free(send_msg);
	send_msg=NULL;
}

void sqlite_inquity(void)
{
	char **result;
	int pn_row,pn_col;
	char *errmsg;

	char *sql;
	char *send_msg;
	//为指针分配空间;
	sql=(char*)malloc(sizeof(1024));
	send_msg=(char*)malloc(sizeof(1024));

	sprintf(sql,"select * from storemsg");
	if(sqlite3_get_table(db,sql,&result,&pn_row,&pn_col,&errmsg)!=SQLITE_OK){
		printf("error:%s\n",errmsg);
		return ;
	}
	else{
		if(0==pn_row){
			printf("now no store data\n");
			return ;
		}
		else{
			int i=1;
			for(;i<pn_row;i++){
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
				semop(history_semid,history_op_t,2);
				strcpy(history_address,send_msg);
			}
			//需要将结束标志传送过去吗????
			//semop(history_semid,history_op_t,2);
			//strcpy(history_address,"");
		}
	}

	free(sql);
	sql=NULL;
	free(send_msg);
	send_msg=NULL;
}



//使用信号处理函数,回收线程资源
void sighandler_free_resource(int sig)
{
	pthread_detach(id_client_request);
	pthread_detach(id_recv_M0_msg);
	pthread_detach(id_send_msg_to_client);
	pthread_detach(id_cemera);
	//其中有两个线程等待3~4秒后,执行完毕自动回收,
	//避免在其中分配的空间未回收
	sleep(3);

	free(MSG);
	MSG=NULL;

	//解除共享内存的映射
	shmdt(msg_address);
	shmdt(order_address);
	shmdt(history_address);

	printf("\nresource release\n");

	exit(0);
}
