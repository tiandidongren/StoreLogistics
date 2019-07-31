#include"memory_cgi_a9.h"

//对key的初始化,成功返回0,失败返回-1
int key_init(void)
{
	msg_key_sem=ftok("/",'A');
	if(msg_key_sem<0){
		perror("msg_key");
		return -1;
	}
	order_key_sem=ftok("/",'B');
	if(order_key_sem<0){
		perror("order_key");
		return -1;
	}
	history_key_sem=ftok("/",'C');
	if(history_key_sem<0){
		perror("history_key");
		return -1;
	}
	msg_key_add=ftok("/",'a');
	if(msg_key_add<0){
		perror("msg_key");
		return -1;
	}
	order_key_add=ftok("/",'b');
	if(order_key_add<0){
		perror("order_key");
		return -1;
	}
	history_key_add=ftok("/",'c');
	if(history_key_add<0){
		perror("history_key");
		return -1;
	}	
	return 0;
}
//对信号量的操作和信号量的值初始化,在调用共享内存和信号灯集前调用
void semop_semval_msg_init(void)
{
	//msg_val_t[0].val=1;
	//msg_val_t[1].val=0;
	msg_op_t[0].sem_num=1;
	msg_op_t[0].sem_op=-1;
	msg_op_t[0].sem_flg=0;
	msg_op_t[1].sem_num=0;
	msg_op_t[1].sem_op=1;
	msg_op_t[1].sem_flg=0;
}

//对信号量的操作和信号量的值初始化,在调用共享内存和信号灯集前调用
void semop_semval_order_init(void)
{
	//order_val_t[0].val=1;
	//order_val_t[1].val=0;
	order_op_t[0].sem_num=0;
	order_op_t[0].sem_op=-1;
	//order_op_t[0].sem_flg=0;
	order_op_t[1].sem_num=1;
	order_op_t[1].sem_op=1;
	//order_op_t[1].sem_flg=0;
}

//对信号量的操作和信号量的值初始化,在调用共享内存和信号灯集前调用
void semop_semval_history_init(void)
{
	//history_val_t[0].val=1;
	//history_val_t[1].val=0;
	history_op_t[0].sem_num=1;
	history_op_t[0].sem_op=-1;
	history_op_t[0].sem_flg=0;
	history_op_t[1].sem_num=0;
	history_op_t[1].sem_op=1;
	history_op_t[1].sem_flg=0;
}

//对共享内存进行初始化病进行映射,成功返回0,失败返回-1
int memory_msg_create(void)
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

	return 0;
}

//对共享内存进行初始化病进行映射,成功返回0,失败返回-1
int memory_order_create(void)
{
	int ret;
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

	return 0;
}

//对共享内存进行初始化病进行映射,成功返回0,失败返回-1
int memory_history_create(void)
{
	int ret;
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

//创建信号灯集,成功返回0,失败返回-1
int sem_msg_create(void)
{
	int i; 		//用作循环计数
	msg_semid=semget(msg_key_sem,2,IPC_CREAT|IPC_EXCL|0777);
	if(msg_semid<0){
		if(errno==EEXIST){
			msg_semid=semget(msg_key_sem,2,0);
		}
		else{
			printf("create msg_semid fail\n");
			return -1;
		}
	}
#if 0
	for(i=0;i<2;i++)
	{
		semctl(msg_semid,i,SETVAL,msg_val_t[i]);
	}
#endif
	printf("create sem_msg_create successful\n");
	return 0;
}

//创建信号灯集,成功返回0,失败返回-1
int sem_order_create(void)
{
	int i; 		//用作循环计数
	order_semid=semget(order_key_sem,2,IPC_CREAT|IPC_EXCL|0777);
	if(order_semid<0){
		if(errno==EEXIST){
			order_semid=semget(order_key_sem,2,0);
		}
		else{
			printf("create order_semid fail\n");
			return -1;
		}
	}
#if 0
	for(i=0;i<2;i++)
	{
		semctl(order_semid,i,SETVAL,order_val_t[i]);
	}
#endif
	printf("create sem_order_create successful\n");
	return 0;
}

//创建信号灯集,成功返回0,失败返回-1
int sem_history_create(void)
{
	int i; 		//用作循环计数
	history_semid=semget(history_key_sem,2,IPC_CREAT|IPC_EXCL|0777);
	if(history_semid<0){
		if(errno==EEXIST){
			history_semid=semget(history_key_sem,2,0);
		}
		else{
			printf("create history_semid fail\n");
			return -1;
		}
	}
#if 0
	for(i=0;i<2;i++){
		semctl(history_semid,i,SETVAL,history_val_t[i]);
	}
#endif
	printf("create sem_history_create successful\n");
	return 0;
}
