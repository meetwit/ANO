#include "stm32f10x.h"
#include "tim2.h"
#include "usart1.h"
#include "usart2.h"
#include "usart3.h"
#include "stdio.h" 
#include "ANO.h" 
#include "math.h" 


int main(){
	float x=0,xx=0;
	double y=0,yy=0;
	
	/*定时器2初始化*/
	init_tim2();
	
	/*串口1初始化，波特率为9600*/
	usart_init(115200);			//串口1作为监控
	
//	printf("helo\r\n");
	
	while(1){
		
//		Task_Pc();
		if(send_flag>100){
			x+=0.1;
			xx+=0.5;
			y=sin(x);
			yy=sin(xx);
			
			ANO_send(0xF1,y,yy,0);
			send_flag=0;
		}
		
	}

}







