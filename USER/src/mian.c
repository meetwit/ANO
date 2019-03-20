/*
ANO应用示例
*/

#include "stm32f10x.h"
#include "usart1.h"
#include "stdio.h" 
#include "ANO.h" 
#include "math.h" 

void delay(void){
	u16 n,m;
	for(n=0;n<1000;n++)
	for(m=0;m<1000;m++)
		{
			;
		}
}

int main(){
	
	float f1[3];
	int 	f2[3];
	float index = 0;
	
	/*串口1初始化，波特率为115200*/
	usart_init(115200);
	
	
	while(1){
		
			index+=0.1;
		
			f1[0]=sin(index);
			f1[1]=sin(index)+1;
			f1[2]=sin(index)-1;
		
			f2[0]=-2;
			f2[1]=0;
			f2[2]=2;
			
			ANO_send(0xf1,(unsigned char *)f1,sizeof(float),sizeof(f1));
			ANO_send(0xf2,(unsigned char *)f2,sizeof(	 int),sizeof(f2));
			
		delay();
	}

}







