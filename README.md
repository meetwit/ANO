# ANO  
ANO应用说明  
	·移植和修改说明  
		··1.添加ANO.h和ANO.c文件到你的工程  
		··2.ANO.c 中修改下文中A&B两处  
	·实例demo  
		包含ANO.h头文件  
		float s[3];  
		int ss[3];  
		s&&ss在这里赋值，然后下面两行是调用  
		ANO_send(0xf1,(unsigned char *)s,sizeof(float),sizeof(s));  
		ANO_send(0xf2,(unsigned char *)ss,sizeof(int),sizeof(ss));  
	·ANO上位机设置  
		··1.高级收码界面使能对用的功能帧  
		··2.设置帧格式，根据你定义的数据来设定  
		··3.设定数据来源，保存设置  
		··4.打开数据波形，选择用户数据，开启对应通道  
作	者：meetwit  
日	期：2019年3月20日  
