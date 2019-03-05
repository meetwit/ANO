#include "ANO.h"

#define usart_send_char PcTx_Byte 

//fun:������. 0XA0~0XAF
//data:���ݻ�����,���28�ֽ�!!
//len:data����Ч���ݸ���
void ANO_report(u8 func,u8*data,u8 len)
{
    u8 send_buf[32]={0};
    u8 i;
    if(len>28)return;    //���28�ֽ����� 
    send_buf[len+3]=0;  //У��������
    send_buf[0]=0XAA;   //֡ͷ
    send_buf[1]=0XAA;   
    send_buf[2]=func;    //������
    send_buf[3]=len;    //���ݳ���
    for(i=0;i<len;i++)send_buf[4+i]=data[i];         //��������
    for(i=0;i<len+4;i++)send_buf[len+4]+=send_buf[i];    //����У��� 
    for(i=0;i<len+5;i++)usart_send_char(send_buf[i]);   //�������ݵ�����
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
     
    ANO_report(fun,tbuf,12);//�Զ���֡,0XA2
}   



