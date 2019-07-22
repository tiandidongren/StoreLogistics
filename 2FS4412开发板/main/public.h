#ifndef PUBLIC_H_
#define PUBLIC_H_
#include<stdint.h>

#define AUTOMATA 	0x100 	//设置为自动控制
#define MANUAL 		0x000 	//设置为手动控制

#define STORE  		0xc0 	//仓库所在位
#define EQUIPMENT 	0x30 	//设备编号所在位
#define HANDLE 	 	0x0f 	//设备操作所在的位

#define STORE_ONE  	0x40 	//一号仓库的编号
#define STORE_two  	0x80 	//二号仓库的编号
#define STORE_three 0xc0 	//三号仓库的编号

#define EQUI_FUN 	0x00 	//风扇设备的编号
#define EQUI_BUZZER 0x10 	//蜂鸣器设备的编号
#define EQUI_LED 	0x20  	//LED设备的编号
#define EQUI_PIPE 	0x30 	//数码管设备的编号

#define FUN_CLOSE  	0x00  	//风扇关闭
#define FUN_LEVEL1 	0x01  	//风扇一档
#define FUN_LEVEL2  0x02  	//风扇二挡
#define FUN_LEVEL3 	0x03  	//风扇三挡

#define BUZZER_CLOSE  	0x00 //蜂鸣器关闭
#define BUZZER_OPEN  	0x01 //蜂鸣器打开

#define LED_CLOSE 	0x00 	//LED灯关闭
#define LED_OPEN 	0x01 	//LEd灯打开

#define PIPE_CON 	0x0f 	//数控管关闭,&得到的值如不如该值相等,
							//则是数控管应该显示的值

#define LENGTH 200

#define CGI_ORDER 		0x01
#define CGI_HISTORY 	0x02

typedef struct add_extern 	//留作环境数据的扩展
{
	char ext[8];
}Add_t;

typedef struct sendEnv 	//环境数据的结构体
{
	uint8_t head[3]; 	//标示位st
	uint8_t type; 		//数据类型
	uint8_t snum; 		//仓库编号
	uint8_t temp[4]; 	//温度,上传数据时只用前两个字节,下达控制命令时
						//,前两个表示温度下限,后两位表示温度下限
	uint8_t hum[4]; 	//湿度,上传数据时只用前两个字节,下达控制命令时
						//,前两个表示湿度下限,后两位表示湿度下限
	uint8_t x; 			//三轴信息
	uint8_t y; 			
	uint8_t z;
	uint32_t ill; 		//光照
	uint32_t bet; 		//电池电量
	uint32_t adc; 		//电位器信息,电池电量
	uint32_t flag; 		//数据类型,风扇 蜂鸣器 LED灯 数码管的状态
	Add_t extension; 	//留作扩展
}message_env_t;

typedef struct sendGoods
{
	uint8_t head[3]; 	//标示位
	uint8_t type; 		//数据类型
	uint8_t snum; 		//仓库编号
	uint8_t io; 		//进出仓库
	uint8_t goodsno; 	//商品编号
	uint8_t goodsnum;  	//商品数量
}msg_good_t;

typedef struct cgi_msg
{
	long type;
	long msgtype;
	unsigned char text[LENGTH];
}msg_cgi_a9;


#endif
