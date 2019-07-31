#include"sqliteAndPthread.h"

#define DEBUG_MY
#define NO_USE

//打开文件按描述符并进行判断的函数,需在最前调用
int open_port(const char*path_dev)
{
	fd_usb_M0=open(path_dev,O_RDWR|O_NDELAY|O_NOCTTY);
	if(fd_usb_M0<0){
		printf("open device id fail\n");
		perror("???");
		return -1;
	}

	//回复串口的阻塞状态
	if(fcntl(fd_usb_M0,F_SETFL,0)<0){
		perror("fcntl F_SETFL\n");
	}

	if(0==isatty(fd_usb_M0)){
		perror("this is not a terminal device");
	}

	set_com_config(fd_usb_M0, 115200, 8, 'N', 1);
	return 0;
}
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
	order_op_t[0].sem_num=1;
	order_op_t[0].sem_op=-1;
	order_op_t[0].sem_flg=0;
	order_op_t[1].sem_num=0;
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
	msg_key_sem=ftok("/",'A');
	if(msg_key_sem<0){
		perror("msg_key_sem");
		return -1;
	}
	order_key_sem=ftok("/",'B');
	if(order_key_sem<0){
		perror("order_key_sem");
		return -1;
	}
	history_key_sem=ftok("/",'C');
	if(history_key_sem<0){
		perror("history_key_sem");
		return -1;
	}
	msg_key_add=ftok("/",'a');
	if(msg_key_add<0){
		perror("msg_key_add");
		return -1;
	}
	order_key_add=ftok("/",'b');
	if(order_key_add<0){
		perror("order_key_add");
		return -1;
	}
	history_key_add=ftok("/",'c');
	if(history_key_add<0){
		perror("history_key_add");
		return -1;
	}	


	return 0;
}
//对共享内存进行初始化并进行映射,成功返回0,失败返回错误码
int memory_create(void)
{
	int ret;
	msg_shm=shmget(msg_key_add,MEMORY_LEN,IPC_CREAT|IPC_EXCL|0777);
	if(msg_shm<0){
		if(errno==EEXIST){
			msg_shm=shmget(msg_key_add,0,0);
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

	order_shm=shmget(order_key_add,MEMORY_LEN,IPC_CREAT|IPC_EXCL|0777);
	if(order_shm<0){
		if(errno==EEXIST){
			order_shm=shmget(order_key_add,0,0);
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

	history_shm=shmget(history_key_add,MEMORY_LEN,IPC_CREAT|IPC_EXCL|0777);
	if(history_shm<0){
		if(errno==EEXIST){
			history_shm=shmget(history_key_add,0,0);
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
	msg_semid=semget(msg_key_sem,2,IPC_CREAT|IPC_EXCL|0777);
	if(msg_semid<0){
		if(errno==EEXIST){
			printf("msg_semid exit\n");
			msg_semid=semget(msg_key_sem,2,0);
		}
		else{
			printf("create msg_semid fail\n");
			return -1;
		}
	}
	for(i=0;i<2;i++)
	{
		semctl(msg_semid,i,SETVAL,msg_val_t[i]);
	}
	order_semid=semget(order_key_sem,2,IPC_CREAT|IPC_EXCL|0777);
	if(order_semid<0){
		if(errno==EEXIST){
			printf("order_semid exit\n");
			order_semid=semget(order_key_sem,2,0);
		}
		else{
			printf("create order_semid fail\n");
			return -1;
		}
	}
	for(i=0;i<2;i++)
	{
		semctl(order_semid,i,SETVAL,order_val_t[i]);
	}

	history_semid=semget(history_key_sem,2,IPC_CREAT|IPC_EXCL|0777);
	if(history_semid<0){
		if(errno==EEXIST){
			printf("history_semid exit\n");
			history_semid=semget(history_key_sem,2,0);
		}
		else{
			printf("create history_semid fail\n");
			return -1;
		}
	}
	for(i=0;i<2;i++){
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

	while(1)
	{
#ifndef NO_USE
		ret=semop(order_semid,order_op_t,1);
		printf("=====\n");
#endif
		msg_env=(message_env_t*)order_address;

#ifndef NO_USE
		strncpy(msg_env->head,"st:",3);
#else
		if(strncmp(msg_env->head,"st:",3))
		{
			sleep(2);
			continue;
		}
#endif

			printf("recv the order\n");
		//printf("msg:%d head:%s     order:%d\n",msg_env->flag,msg_env->head,((message_env_t*)order_address)->flag);
		//strncpy((char*)msg_env,order_address,sizeof(message_env_t));
		//此处直接使用msg_env指针指向改地址是否可行?
		//msg_env=(message_env_t*)order_address;

		if(CGI_ORDER==msg_env->type){
			//将数据发送给M0,调用发送命令的线程,发送后销毁
			ret=pthread_create(&id_send_order_to_M0,NULL,pthread_send_order_to_M0,(void*)msg_env);
#ifdef DEBUG_MY
			//printf("recv the order\n");
#endif
			if(ret<0){
				printf("send msg to M0 fail");
			}
			sleep(2);

		}
		else{
			//查询数据库,将查询到的信息逐条写入共享内存二中
			//此处应注意,不要与共享内存一(用以实时同步数据)的
			//共享内存冲突,二者使用两个共享内存
			//调用数据库线程,使用后销毁
			//semop(order_semid,order_op_t+1,1);

			memset(MSG,0,sizeof(message_env_t));
			ret=pthread_create(&id_sqlite,NULL,pthread_sqlite,NULL);
			if(ret<0){
				printf("check history to client fail");
			}
			sleep(2);
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
	while(1)
	{
		ret=pthread_mutex_trylock(&mutex);
		if(ret<0){
			continue;
		}
		else{
			//将数据存储到MSG中;
			ret=read(fd_usb_M0,(char*)MSG,sizeof(message_env_t));

			while(strncmp(MSG->head,"st:",3)){
				ret=read(fd_usb_M0,(char*)MSG,sizeof(message_env_t));
				continue;
			}
			printf("pthread_recv_M0_msg\n");
#if 0
			printf("head:%s\nstore:%d\ntemp:%d.%d\nhum:%d.%d\nx,y,z:%d,%d,%d\nill:%d\nbet:%d\nadc:%d\nMSG->flag:%d  %d  %d  %d\n",\
					MSG->head,MSG->snum,MSG->temp[0],MSG->temp[1],\
					MSG->hum[0],MSG->hum[1],MSG->x,\
					MSG->y,MSG->z,MSG->ill,MSG->bet,\
					MSG->adc,(MSG->flag)>>24,(((MSG->flag)>>16)&0xff),(((MSG->flag)>>8)&0xff),\
					((MSG->flag)&0xff));
#endif
			pthread_mutex_unlock(&mutex);
		}
		
	}
}

void * pthread_send_msg_to_client(void*empty)
{
	//使用pthread_mutex_lock,上互斥锁一失败等待,
	//成功后,将结构体数据写入共享内存一中,然后释放
	//锁一,并对信号量进行操作(可在锁外进行)
	int ret;
	sleep(10);
	while(1)
	{
		//semop(msg_semid,msg_op_t,1);
		while(1){
			ret=pthread_mutex_trylock(&mutex);
			if(ret<0)
				continue;
			else if(strncmp(MSG->head,"st:",3)){
				((message_env_t*)msg_address)->ill=MSG->ill;
				continue;
			}
			else
				break;
		}
		//不知道为什么,只好依次复制;
		((message_env_t*)msg_address)->snum=MSG->snum;
		((message_env_t*)msg_address)->temp[0]=MSG->temp[0];
		((message_env_t*)msg_address)->temp[1]=MSG->temp[1];
		((message_env_t*)msg_address)->hum[0]=MSG->hum[0];
		((message_env_t*)msg_address)->hum[1]=MSG->hum[1];
		((message_env_t*)msg_address)->x=MSG->x;
		((message_env_t*)msg_address)->y=MSG->y;
		((message_env_t*)msg_address)->z=MSG->z;
		((message_env_t*)msg_address)->ill=MSG->ill;
		((message_env_t*)msg_address)->bet=MSG->bet;
		((message_env_t*)msg_address)->adc=MSG->adc;

		printf("pthread_send_msg_to_client\n");
		sqlite_add_data((message_env_t*)msg_address);
		memset(MSG,0,sizeof(message_env_t));
		pthread_mutex_unlock(&mutex);
		//semop(msg_semid,msg_op_t+1,1);
		sleep(10);
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
	memset(order_address,0,sizeof(message_env_t));
	pthread_exit(0);
}

//下达命令的线程
void * pthread_send_order_to_M0(void*msg_env)
{
	//将接收到的命令发送给指定的设备节点
#ifdef DEBUG_MY
	printf("order:store:%d\ntemp:%d.%d\nhum:%d.%d\nx,y,z:%d,%d,%d\nill:%d\nbet:%d\nadc:%d\n",\
						((message_env_t*)msg_env)->snum,((message_env_t*)msg_env)->temp[0],((message_env_t*)msg_env)->temp[1],\
						((message_env_t*)msg_env)->hum[0],((message_env_t*)msg_env)->hum[1],((message_env_t*)msg_env)->x,\
						((message_env_t*)msg_env)->y,((message_env_t*)msg_env)->z,((message_env_t*)msg_env)->ill,((message_env_t*)msg_env)->bet,\
						((message_env_t*)msg_env)->adc);
#endif
	 ((message_env_t*)msg_env)->type=0;

	write(fd_usb_M0,msg_env,sizeof(message_env_t));
	printf("pthread_send_order_to_M0\n");
	memset(order_address,0,sizeof(message_env_t));

	pthread_exit(0);
}

//数据库的操作,只需要添加数据,和查询全部即可
void sqlite_add_data(message_env_t* data)
{
	char *sql,*ptr_time,*errmsg;
	char *send_msg;
	//为指针分配空间;
	sql=(char*)malloc(1024);
	if(NULL==sql){
		printf("malloc sql fail\n");
		return ;
	}
	memset(sql,0,1024);
	send_msg=(char*)malloc(1024);
	if(NULL==send_msg){
		printf("malloc send_msg fail\n");
		return ;
	}

	time_t time_data;
	if(time(&time_data)<0){
		perror("get time");
		return ;
	}

	/*ptr_time=ctime(&time_data);
	printf("2222222221=\n");
	if(NULL==ptr_time){
		printf("change sec is fail\n");
		return ;
	}*/
	//printf("_____\n");
	//对温度的正负进行判断,
	if(data->temp[0]>128){
		sprintf(sql,"insert into storemsg values('%d',-%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,'1')",\
			data->snum,data->temp[0],data->temp[1],\
			data->hum[0],data->hum[1],data->x,\
			data->y,data->z,data->ill,data->bet,\
			data->adc);

		sprintf(send_msg,"store:%c\ntemp:-%d.%d\nhum:%d.%d\nx,y,z:%d,%d,%d\n\
				ill:%d\nbet:%d\nadc:%d\n",\
				data->snum,data->temp[0],data->temp[1],\
				data->hum[0],data->hum[1],data->x,\
				data->y,data->z,data->ill,data->bet,\
				data->adc);

	}
	else{
		printf("++++++=++++\n");
		sprintf(sql,"insert into storemsg values('%d',%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,'1')",\
			data->snum,data->temp[0],data->temp[1],\
			data->hum[0],data->hum[1],data->x,\
			data->y,data->z,data->ill,data->bet,\
			data->adc);
#if 1
		printf("store:%d\ntemp:%d.%d\nhum:%d.%d\nx,y,z:%d,%d,%d\nill:%d\nbet:%d\nadc:%d\n",\
				data->snum,data->temp[0],data->temp[1],\
				data->hum[0],data->hum[1],data->x,\
				data->y,data->z,data->ill,data->bet,\
				data->adc);
#endif
		sprintf(send_msg,"store:%d\ntemp:%d.%d\nhum:%d.%d\nx,y,z:%d,%d,%d\nill:%d\nbet:%d\nadc:%d\n",\
				data->snum,data->temp[0],data->temp[1],\
				data->hum[0],data->hum[1],data->x,\
				data->y,data->z,data->ill,data->bet,\
				data->adc);
		printf("send_msg:%s\n",send_msg);
	}
	//printf("=====\n");

	if(sqlite3_exec(db,sql,empty_callback,NULL,&errmsg)!=SQLITE_OK){
		printf("insert data is fail,error:%s\n",errmsg);
		
		return ;
	}

	printf("insert OK!\n");

#if 0
	free(sql);
	sql=NULL;
	free(send_msg);
	send_msg=NULL;
#endif
}

void sqlite_inquity(void)
{
	char **result;
	int pn_row,pn_col;
	char *errmsg;

	char *sql;
	char *send_msg;
	//为指针分配空间;
	sql=(char*)malloc(1024);
	send_msg=(char*)malloc(1024);

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
			for(;i<=pn_row;i++){
				sprintf(history_address,"store:%s\ntemp:%s.%s\nhum:%s.%s\nx,y,z:%s.%s.%s\nill:%s\nbet:%s\nadc:%s\ntime:%s\n",\
						result[i*pn_col],result[i*pn_col+1],\
						result[i*pn_col+2],result[i*pn_col+3],\
						result[i*pn_col+4],result[i*pn_col+5],\
						result[i*pn_col+6],result[i*pn_col+7],\
						result[i*pn_col+8],result[i*pn_col+9],\
						result[i*pn_col+10],result[i*pn_col+11]
					   );
				printf("history_address:%s\n",history_address);
				//此处应有函数处理,将send_msg发送给CGI,
				//使用共享内存
				//semop(history_semid,history_op_t,2);
				//strcpy(history_address,send_msg);
				sleep(1);
			}
			history_address[0]='\0';
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

//回调函数
int empty_callback(void *data,int f_num,char **f_calue,char **f_name)
{
	return ;
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
	//sleep(3);

	free(MSG);
	MSG=NULL;

	//解除共享内存的映射
	shmdt(msg_address);
	shmdt(order_address);
	shmdt(history_address);

	//删除信号灯集
	int i;
	for(i=0;i<sizeof(history_val_t)/sizeof(union semun);i++){
		semctl(history_semid,i,IPC_RMID);
		semctl(order_semid,i,IPC_RMID);
		semctl(msg_semid,i,IPC_RMID);
	}

	//关闭文件描述符
	close(fd_usb_M0);

	printf("\nresource release\n");

	exit(0);
}


int set_com_config(int fd, int baud_rate, int data_bits, char parity, int stop_bits)
{
	struct termios new_cfg, old_cfg;
	int speed;
	/*int保存原有串口配置*/
	if (tcgetattr(fd, &old_cfg) != 0){
		perror("tcgetattr");
		return -1;
	}

	new_cfg =old_cfg;

	/*配置为原始æ¨¡式*/
	cfmakeraw(&new_cfg);
	new_cfg.c_cflag &= ~CSIZE;

	/*设置波特率*/
	switch (baud_rate)
	{
	case 2400:{
				  speed = B2400;
				  break; 
			  }
	case 4800:{
				  speed = B4800;
				  break;
			  }
	case 9600:{
				  speed = B9600;
				  break;
			  }
	case 19200:{
				   speed = B19200;
				   break;
			   }
	case 38400:{//设置波特率   
				   speed = B38400;
				   break;
			   }

	default:
	case 115000:{
					speed = B115200;
					break;
				}
	}

	cfsetispeed(&new_cfg, speed);
	cfsetospeed(&new_cfg, speed);

	/*设置数据位*/
	switch (data_bits)
	{
	case 7:{
			   new_cfg.c_cflag |= CS7;
			   break;
		   }   
	default:
	case 8:{
			   new_cfg.c_cflag |= CS8;
			   break;
		   }
	}

	/*设置奇偶校验位*/
	switch (parity)
	{
	default:
	case 'n':
	case 'N':{
				 new_cfg.c_cflag &= ~PARENB;
				 new_cfg.c_iflag &= ~INPCK;
				 break;
			 }
	case 'o':
	case 'O':{
				 new_cfg.c_cflag |= (PARODD |PARENB);
				 new_cfg.c_iflag |= INPCK;
				 break;
			 }
	case 'e':
	case 'E':{
				 new_cfg.c_cflag |= PARENB;
				 new_cfg.c_cflag &= ~PARODD;
				 new_cfg.c_iflag |= INPCK;
				 break;
			 }
	case 's':
	case 'S':{
				 new_cfg.c_cflag &= ~PARENB;
				 new_cfg.c_cflag &= ~CSTOPB;
				 break;
			 }
	}

	/*设置停止位*/
	switch (stop_bits)
	{
	default:
	case 1:{
			   new_cfg.c_cflag &= ~CSTOPB;
			   break;
		   }   
	case 2:{
			   new_cfg.c_cflag |= CSTOPB;
			   break;
		   }
	}

	/*设置为手动控制等待时间和最小接收字符*/
	new_cfg.c_cc[VTIME] = 0;
	new_cfg.c_cc[VMIN] = 1;
	tcflush(fd, TCIFLUSH);
	if ((tcsetattr(fd, TCSANOW, &new_cfg)) != 0)
	{
		perror("tcsetattr");
		return -1;
	}

	return 0;
}


