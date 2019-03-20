/*
# ANO  
ANOӦ��˵��  
	����ֲ���޸�˵��  
		����1.���ANO.h��ANO.c�ļ�����Ĺ���  
		����2.ANO.c ���޸�������A&B����  
	���鿴ʵ��demo  
	��ANO��λ������  
		����1.�߼��������ʹ�ܶ��õĹ���֡  
		����2.����֡��ʽ�������㶨����������趨  
		����3.�趨������Դ����������  
		����4.�����ݲ��Σ�ѡ���û����ݣ�������Ӧͨ��  
��	�ߣ�meetwit  
��	�ڣ�2019��3��20��  
*/
#include "ANO.h"

/*
A�����޸�Ϊ���ֽڷ��ͺ�����ͷ�ļ�
*/
#include "usart1.h"

/*
B�����޸�Ϊ���ֽڷ��ͺ���
*/
#define usart_send_char PcTx_Byte 

/*
��������ANO_report
��	����u8 func 						������,�Զ��壬0xF1-0xFF
				u8*data							Ҫ���͵����ݲ���,
				u8 len							Ҫ�������ݵĳ��ȣ���λ��byte	
��	�ܣ�����������֡ͷ���������Լ�У��Ͳ��ҷ��͵�ANO��λ��
��	�ڣ�2019��3��20��
��	�ߣ�meetwit
*/
void ANO_report(u8 func,u8*data,u8 len)
{
    u8 send_buf[85]={0},i;
    if(len>80)return;   																		//���80�ֽ����� 
    send_buf[len+3]=0;  																		//У��������
    send_buf[0]=0XAA;   																		//֡ͷ
    send_buf[1]=0XAA;   
    send_buf[2]=func;    																		//������
    send_buf[3]=len;    																		//���ݳ���
    for(i=0;i<len;i++)send_buf[4+i]=data[i];         				//��������
    for(i=0;i<len+4;i++)send_buf[len+4]+=send_buf[i];    		//����У��� 
    for(i=0;i<len+5;i++)usart_send_char(send_buf[i]);  			//�������ݵ�����
}

/*
��������ANO_send
��	����u8 fun 							������,�Զ��壬0xF1-0xFF
				unsigned char * sp	��ʾ���ݵĵ�ַ,
				u8 sizenum					�������ͳ���,
				u8 len							�����ܳ��ȣ���λ��byte	
��	�ܣ�����������ݷ��͵���������Ҫ������ѡ�ö�Ӧ���ȵĽ���
				�������Ҫ�������ݸ��ݳ��ȣ�n byte����Ϊ�������飬�ֱ��ò�ͬ�Ĺ����ַ���
��	�ڣ�2019��3��20��
��	�ߣ�meetwit
*/
void ANO_send(u8 fun,unsigned char * sp,u8 sizenum,u8 len)
{
    u8 tbuf[80]={0},i,j; 
    unsigned char *p;
		for(i=0;i<len/sizenum;i++){															//ѭ���������ɸ�����
			p=sp+sizenum*i;																				//���ݵ�ַƫ��	
			for(j=0;j<sizenum;j++){
				tbuf[j+4*i]=(unsigned char)(*(p+3-j));							//һ�����������ֽڣ��ȷ��͸��ֽڣ�ѭ�����ͣ��������ֽڵ�ַƫ��
			}
		}
    ANO_report(fun,tbuf,len);																//����ANO_report����
}   


