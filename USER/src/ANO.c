/*
# ANO  
ANO应用说明  
	·移植和修改说明  
		··1.添加ANO.h和ANO.c文件到你的工程  
		··2.ANO.c 中修改下文中A&B两处  
	·查看实例demo  
	·ANO上位机设置  
		··1.高级收码界面使能对用的功能帧  
		··2.设置帧格式，根据你定义的数据来设定  
		··3.设定数据来源，保存设置  
		··4.打开数据波形，选择用户数据，开启对应通道  
作	者：meetwit  
日	期：2019年3月20日  
*/
#include "ANO.h"

/*
A处：修改为你字节发送函数的头文件
*/
#include "usart1.h"

/*
B处：修改为你字节发送函数
*/
#define usart_send_char PcTx_Byte 

/*
函数名：ANO_report
参	数：u8 func 						功能字,自定义，0xF1-0xFF
				u8*data							要发送的数据部分,
				u8 len							要发送数据的长度，单位：byte	
功	能：将数据增加帧头，功能字以及校验和并且发送到ANO上位机
日	期：2019年3月20日
作	者：meetwit
*/
void ANO_report(u8 func,u8*data,u8 len)
{
    u8 send_buf[85]={0},i;
    if(len>80)return;   																		//最多80字节数据 
    send_buf[len+3]=0;  																		//校验数置零
    send_buf[0]=0XAA;   																		//帧头
    send_buf[1]=0XAA;   
    send_buf[2]=func;    																		//功能字
    send_buf[3]=len;    																		//数据长度
    for(i=0;i<len;i++)send_buf[4+i]=data[i];         				//复制数据
    for(i=0;i<len+4;i++)send_buf[len+4]+=send_buf[i];    		//计算校验和 
    for(i=0;i<len+5;i++)usart_send_char(send_buf[i]);  			//发送数据到串口
}

/*
函数名：ANO_send
参	数：u8 fun 							功能字,自定义，0xF1-0xFF
				unsigned char * sp	显示数据的地址,
				u8 sizenum					数据类型长度,
				u8 len							数据总长度，单位：byte	
功	能：把数组的内容发送到匿名，需要在匿名选好对应长度的接收
				建议把需要发送数据根据长度（n byte）分为几个数组，分别用不同的功能字发送
日	期：2019年3月20日
作	者：meetwit
*/
void ANO_send(u8 fun,unsigned char * sp,u8 sizenum,u8 len)
{
    u8 tbuf[80]={0},i,j; 
    unsigned char *p;
		for(i=0;i<len/sizenum;i++){															//循环发送若干个数据
			p=sp+sizenum*i;																				//数据地址偏移	
			for(j=0;j<sizenum;j++){
				tbuf[j+4*i]=(unsigned char)(*(p+3-j));							//一个数据若干字节，先发送高字节，循环发送，数据内字节地址偏移
			}
		}
    ANO_report(fun,tbuf,len);																//调用ANO_report函数
}   


