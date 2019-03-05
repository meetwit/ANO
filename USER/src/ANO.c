#include "ANO.h"

#define usart_send_char PcTx_Byte 

//fun:功能字. 0XA0~0XAF
//data:数据缓存区,最多28字节!!
//len:data区有效数据个数
void ANO_report(u8 func,u8*data,u8 len)
{
    u8 send_buf[32]={0};
    u8 i;
    if(len>28)return;    //最多28字节数据 
    send_buf[len+3]=0;  //校验数置零
    send_buf[0]=0XAA;   //帧头
    send_buf[1]=0XAA;   
    send_buf[2]=func;    //功能字
    send_buf[3]=len;    //数据长度
    for(i=0;i<len;i++)send_buf[4+i]=data[i];         //复制数据
    for(i=0;i<len+4;i++)send_buf[len+4]+=send_buf[i];    //计算校验和 
    for(i=0;i<len+5;i++)usart_send_char(send_buf[i]);   //发送数据到串口
}
 
void ANO_send(u8 fun,float a,float b,float c)
{
    u8 tbuf[12]={0}; 
    unsigned char *p;
	
    p=(unsigned char *)&a;
    tbuf[0]=(unsigned char)(*(p+3));
    tbuf[1]=(unsigned char)(*(p+2));
    tbuf[2]=(unsigned char)(*(p+1));
    tbuf[3]=(unsigned char)(*(p+0));
     
    p=(unsigned char *)&b;
    tbuf[4]=(unsigned char)(*(p+3));
    tbuf[5]=(unsigned char)(*(p+2));
    tbuf[6]=(unsigned char)(*(p+1));
    tbuf[7]=(unsigned char)(*(p+0));
     
    p=(unsigned char *)&c;
    tbuf[8]=(unsigned char)(*(p+3));
    tbuf[9]=(unsigned char)(*(p+2));
    tbuf[10]=(unsigned char)(*(p+1));
    tbuf[11]=(unsigned char)(*(p+0));
     
    ANO_report(fun,tbuf,12);//自定义帧,0XA2
}   



