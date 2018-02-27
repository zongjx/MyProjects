/*内核c程序*/
extern void clear();                               /*连接外部的clear()函数,用于清屏*/
extern void inputchar();                           /*连接外部的inputchar()函数，用于读入字符*/
extern void printchar();                           /*连接外部的printchar()函数，用于输出字符*/
extern void printstring();                         /*连接外部的printstring()函数，用于输出字符串*/
extern void setcursor();                           /*连接外部的setcursor()函数，用于设置光标*/
extern void load_prog();                           /*连接外部的load_prog()函数，用于加载外部程序*/
extern void run_prog();                            /*连接外部的run_prog()函数，用于跳转到外部程序*/
extern void filldata();                            /*连接外部的filldata()函数，用于填入数据*/
extern void readdata();                            /*连接外部的readdata()函数，用于读入数据*/

/*以下将创建若干长度为80的字符串变量(屏幕最大长度为80)，用于存放提示语句*/
char message1[80]="Welcome to our team's system!\n";
char message2[80]="Coded by Zongjiaxi Zhonglingshan Zhouchancheng\n";
char message3[80]="You can input some legal instructions to active the functions\n";
char message4[80]="    If you want to run the program by Batching,input \'batch\'\n";
char message5[80]="       For example: batch 1 2 3 4\n";
char message6[80]="    If you want to run the program by Time-Sharing,input \'time\'\n";
char message7[80]="       For example: time 1 2 3 4\n";
char message8[80]="    If you want to know the information of the program,input \'show\'\n";
char message9[80]="       For example: show\n";
char message10[80]="    If you want to run the default instructions,input \'default\'\n";
char message11[80]="       For example: default\n\n";
char message12[80]="If you want to continue,input \'yes\',otherwise input \'no\'\n";
char message13[80]="OS will run instructions \'batch 1 2 3 4\' and \'time 1 2 3 4\'\n";
char message_cmd[80]=" O(∩_∩)O >";
char message_ins1[80]="User Program1:\n    Name:program_LU  Size:1024byte  Position:part LU\n";
char message_ins2[80]="User Program2:\n    Name:program_RU  Size:1024byte  Position:part RU\n";
char message_ins3[80]="User Program3:\n    Name:program_LD  Size:1024byte  Position:part LD\n";
char message_ins4[80]="User Program4:\n    Name:program_RD  Size:1024byte  Position:part RD\n";
char string[80];
char message_error[80]="Input Error!!!\n";
const char batch_order[80]="batch 1 2 3 4";
const char time_order[80]="time 1 2 3 4";
int len=0;										   /*代表长度的变量*/
int pos=0;										   /*代表位置的变量*/
char ch;										   /*代表输入的字符*/
int x=0;										   /*纵向位置的变量*/
int y=0;										   /*横向位置的变量*/
int i=0;										   /*用于计数的变量*/
int j=0;										   /*用于计数的变量*/
int k=0;										   /*用于计数的变量*/
int data=0;										   /*数据存储的变量*/
int offset_prog=37120;                             /*用户程序的偏移量，0910h*10h+0h=37120(初始位置) */
const int offset_prog1=37120;                      /*第一个用户程序的偏移地址 0910h*10h+0h=37120*/ 
const int offset_prog2=38144;                      /*第二个用户程序的偏移地址 0950h*10h+0h=38144*/
const int offset_prog3=39168;                      /*第三个用户程序的偏移地址 0990h*10h+0h=39168*/
const int offset_prog4=40192;                      /*第四个用户程序的偏移地址 09d0h*10h+0h=40192*/
const int hex600h=1536;                            /*600h的十进制,作为内存地址用于标记用户程序的调用情况*/
int offset_begin=37120;                            /*初始位置内存偏移量*/
int num_sector=8;                                  /*扇区的总数为8个*/
int pos_sector=2;                                  /*起始扇区的编号为2，第一个扇区放置的是引导程序*/

int input(){                                       /*控制输入字符的函数*/
	inputchar();                                   /*读入一个字符的函数*/
	if(ch=='\b'){                                  /*如果读入的字符是删除键Backspace*/
		if(y>8&&y<79){                             /*如果光标的横向位置是在8到79之间*/
			y--;                                   /*光标向左移一位*/
			cal_pos();                             /*重新计算光标的坐标*/
		}
		return 0;                                  /*如果输入的是删除键，则返回0*/
	}
	else if(ch==13);                               /*回车键*/
	else printchar(ch);                            /*如果不是以上情况，就显示字符*/
	return 1;                                      /*如果不是以上情况，就返回1*/
}

cin_cmd(){                                         /*输出命令提示符的函数*/
	printstring(message_cmd);                      /*打印字符串的函数*/
	i=0;                                           /*初始字符串下标*/
	while(1){                                      /*while循环*/
		if(input()){                               /*如果输入的不是删除键*/
			if(ch==13) break;                      /*如果输入的字符是回车键，则跳出while循环*/
			string[i++]=ch;                        /*否则把该字符添加到string的末尾*/
		}
		else if(i>0) i--;                          /*如果输入的是删除键，就删除一个字符*/
	}
	for(j=0;j<i;j++)                               /*进入for循环，遍历string字符串*/
		if(string[0]==' '){                        /*如果字符串首位是空格*/
			for(k=1;k<i;k++) string[k-1]=string[k];/*把首位空格去掉*/
			i--;                                   /*字符串长度减1*/
		}
		else break;                                /*如果字符串首位不是空格，就跳出循环*/
	string[i]='\0';                                /*字符串末尾补上一个空格，也可以把i-1*/
	len=i;                                         /*记录下字符串的长度i*/
	printstring("\n");                             /*换行*/
}

cal_pos(){                                         /*计算字符或光标的坐标的函数*/
	if(y>79){                                      /*假如y方向大于79(到达了右边界)*/
		y=0;                                       /*y变为0，到达下一行的起始位置*/
		x++;                                       /*行数x加1*/
	}
	if(x>24) clear();                              /*假如x大于24(到达了下边界)，清空屏幕到下一页*/
	pos=(x*80+y)*2;                                /*重新计算位置*/
	setcursor();                                   /*放置光标的函数，在pos的位置放置光标*/
}

batch(){                                           /*实现批处理功能的函数*/
	clear();                                       /*清屏，清除引导程序所显示的内容*/
	offset_begin=offset_prog1;                     /*设置初始位置内存偏移量等于第一个用户程序的偏移量*/
	num_sector=8;                                  /*扇区的总数为8个*/
	pos_sector=2;                                  /*起始扇区的编号为2*/
	load_prog(offset_begin,num_sector,pos_sector); /*装载用户程序到内存，利用中断读取扇区*/
	filldata(hex600h,0);                           /*向hex600h(600h)这个内存位置填进0，表示第一个用户程序暂不运行*/
	filldata(hex600h+2,0);                         /*向hex600h+2(602h)这个内存位置填进0，表示第二个用户程序暂不运行*/
	filldata(hex600h+4,0);                         /*向hex600h+4(604h)这个内存位置填进0，表示第三个用户程序暂不运行*/
	filldata(hex600h+6,0);                         /*向hex600h+6(606h)这个内存位置填进0，表示第四个用户程序暂不运行*/
    for(i=0;i<len;i++){                            /*进入for循环，遍历字符串(输入的指令)*/
		if(string[i]=='1'){                        /*如果字符串中出现'1'字符*/
			offset_prog=offset_prog1;              /*把第一个用户程序的偏移地址写入到初始地址变量中*/
			run_prog();                            /*调用运行程序的函数(此处将使用offset_prog变量)*/
		}
		else if(string[i]=='2'){                   /*如果字符串中出现'2'字符*/
			offset_prog=offset_prog2;              /*把第二个用户程序的偏移地址写入到初始地址变量中*/
			run_prog();                            /*调用运行程序的函数(此处将使用offset_prog变量)*/
		}
		else if(string[i]=='3'){                   /*如果字符串中出现'3'字符*/
			offset_prog=offset_prog3;              /*把第三个用户程序的偏移地址写入到初始地址变量中*/
			run_prog();                            /*调用运行程序的函数(此处将使用offset_prog变量)*/
		}
		else if(string[i]=='4'){                   /*如果字符串中出现'4'字符*/
			offset_prog=offset_prog4;              /*把第四个用户程序的偏移地址写入到初始地址变量中*/
			run_prog();                            /*调用运行程序的函数(此处将使用offset_prog变量)*/
		}
	}
}

time(){                                            /*实现伪分时处理的函数*/
	clear();                                       /*清屏，清除引导程序所显示的内容*/
	offset_begin=offset_prog1;                     /*设置初始位置内存偏移量等于第一个用户程序的偏移量*/
	num_sector=8;                                  /*扇区的总数为8个*/
	pos_sector=2;                                  /*起始扇区的编号为2*/
	load_prog(offset_begin,num_sector,pos_sector); /*装载用户程序到内存，利用中断读取扇区*/
	filldata(hex600h,0);                           /*向hex600h(600h)这个内存位置填进0，表示第一个用户程序暂不运行*/
	filldata(hex600h+2,0);                         /*向hex600h+2(602h)这个内存位置填进0，表示第二个用户程序暂不运行*/
	filldata(hex600h+4,0);                         /*向hex600h+4(604h)这个内存位置填进0，表示第三个用户程序暂不运行*/
	filldata(hex600h+6,0);                         /*向hex600h+6(606h)这个内存位置填进0，表示第四个用户程序暂不运行*/
	for(i=0;i<len;i++){                            /*进入for循环，遍历字符串(输入的指令)*/
		if(string[i]=='1')                         /*如果字符串中出现'1'字符*/
			filldata(hex600h,1);                   /*向hex600h(600h)这个内存位置填进1，表示第一个用户程序将会运行*/
		else if(string[i]=='2')                    /*如果字符串中出现'2'字符*/
			filldata(hex600h+2,1);                 /*向hex600h(602h)这个内存位置填进1，表示第二个用户程序将会运行*/
		else if(string[i]=='3')                    /*如果字符串中出现'3'字符*/
			filldata(hex600h+4,1);                 /*向hex600h(604h)这个内存位置填进1，表示第三个用户程序将会运行*/ 
		else if(string[i]=='4')                    /*如果字符串中出现'4'字符*/
			filldata(hex600h+6,1);                 /*向hex600h(606h)这个内存位置填进1，表示第四个用户程序将会运行*/ 
	}
	while(1){                                      /*进入while循环，程序将会分时运行*/
		j=0;                                       /*记录器j初始为0，此处用于记录是有有程序运行*/
		readdata(hex600h);                         /*读取hex600h(600h)地址中的值，取出的数据将会存到data变量中*/
		j+=data;                                   /*将data的值加到记录器j中*/
		if(data){                                  /*如果data中的值非0*/
			offset_prog=offset_prog1;              /*把第一个用户程序的偏移地址写入到初始地址变量中*/
			run_prog();                            /*调用运行程序的函数(此处将使用offset_prog变量)*/
		}
		readdata(hex600h+2);                       /*读取hex600h+2(602h)地址中的值，取出的数据将会存到data变量中*/
        j+=data;                                   /*将data的值加到记录器j中*/
		if(data){                                  /*如果data中的值非0*/
			offset_prog=offset_prog2;              /*把第二个用户程序的偏移地址写入到初始地址变量中*/
			run_prog();
		}		
        readdata(hex600h+4);                       /*读取hex600h+4(604h)地址中的值，取出的数据将会存到data变量中*/
        j+=data;                                   /*将data的值加到记录器j中*/
		if(data){                                  /*如果data中的值非0*/
			offset_prog=offset_prog2;              /*把第三个用户程序的偏移地址写入到初始地址变量中*/
			run_prog();                            /*调用运行程序的函数(此处将使用offset_prog变量)*/
		}
        readdata(hex600h+6);                       /*读取hex600h+6(606h)地址中的值，取出的数据将会存到data变量中*/
        j+=data;                                   /*将data的值加到记录器j中*/
		if(data){                                  /*如果data中的值非0*/
			offset_prog=offset_prog2;              /*把第四个用户程序的偏移地址写入到初始地址变量中*/
			run_prog();                            /*调用运行程序的函数(此处将使用offset_prog变量)*/
		}
		if(j==0) break;                            /*如果4个数据都为0，则退出循环*/
	}                                       
}

cmain(){                                            /*主函数*/ 
	while(1){                                       /*进入while循环，开始运行程序*/
		clear();                                    /*清屏操作*/
		printstring(message1);                      /*打印message1字符串*/
		printstring(message2);                      /*打印message2字符串*/
		printstring(message3);                      /*打印message3字符串*/
		printstring(message4);                      /*打印message4字符串*/
		printstring(message5);                      /*打印message5字符串*/
		printstring(message6);                      /*打印message6字符串*/
		printstring(message7);                      /*打印message7字符串*/
		printstring(message8);                      /*打印message8字符串*/
		printstring(message9);                      /*打印message9字符串*/
		printstring(message10);                     /*打印message10字符串*/
		printstring(message11);                     /*打印message11字符串*/
		cin_cmd();                                  /*显示命令提示符，并接收输入的指令*/
		if(string[0]=='b'){                         /*如果接收到的指令的首位字符是'b'，则意味着调用了批处理功能的函数*/
			batch();                                /*调用batch函数，实现批处理功能*/
			printstring(message12);                 /*打印massage12字符串*/
			cin_cmd();                              /*显示命令提示符，并接收输入的指令*/
			if(string[0]=='y') continue;            /*如果输入的字符串的首位字符是'y'，则重新进入while循环*/
		}
		else if(string[0]=='t'){                    /*如果接收到的指令的首位字符是't'，则意味着调用了伪分时功能的函数*/
			batch();                                /*调用batch函数，实现批处理功能*/
			printstring(message12);                 /*打印massage12字符串*/
			cin_cmd();                              /*显示命令提示符，并接收输入的指令*/
			if(string[0]=='y') continue;            /*如果输入的字符串的首位字符是'y'，则重新进入while循环*/
		}
		else if(string[0]=='s'){                    /*如果接收到的指令的首位字符是's'，则显示每个程序的信息*/
			printstring(message_ins1);              /*打印massage_ins1字符串*/
			printstring(message_ins2);              /*打印massage_ins2字符串*/
			printstring(message_ins3);              /*打印massage_ins3字符串*/
			printstring(message_ins4);              /*打印massage_ins4字符串*/
			cin_cmd();                              /*显示命令提示符，并接收输入的指令*/
			if(string[0]=='y') continue;            /*如果输入的字符串的首位字符是'y'，则重新进入while循环*/
		}
		else if(string[0]=='d'){                    /*如果接收到的指令的首位字符是'd'，则显示每个程序的信息*/
			printstring(message13);                 /*打印massage13字符串*/
			printstring(message12);                 /*打印massage12字符串*/
			cin_cmd();                              /*显示命令提示符，并接收输入的指令*/
			if(string[0]=='y'){                     /*如果输入的字符串的首位字符是'y'*/
				for(i=0;i<len;i++){                 /*进入for循环,将批处理功能的指令存到string中*/
					string[i]=batch_order[i];       /*字符串(批处理指令)转移*/
					if(batch_order[i]=='\0'){       /*如果到达字符串尾部*/
						len=i;                      /*记录下字符串的长度*/
						break;                      /*跳出for循环*/
					}
				}
				batch();                            /*调用batch函数，实现批处理功能*/
				printstring(message12);             /*打印massage12字符串*/
				cin_cmd();                          /*显示命令提示符，并接收输入的指令*/
				if(string[0]=='y') continue;        /*如果输入的字符串的首位字符是'y'，继续运行程序*/
				for(i=0;i<len;i++){                 /*进入for循环,将批处理功能的指令存到string中*/
					string[i]=time_order[i];        /*字符串(伪分时指令)转移*/
					if(time_order[i]=='\0'){        /*如果到达字符串尾部*/
						len=i;                      /*记录下字符串的长度*/
						break;                      /*跳出for循环*/
					}
				}
				time();                             /*调用time函数，实现批处理功能*/
				printstring(message12);             /*打印massage12字符串*/
				cin_cmd();                          /*显示命令提示符，并接收输入的指令*/
			}		
		}
		else{
			printstring(message_error);             /*打印massage_error字符串*/
			printstring(message12);                 /*打印massage12字符串*/
			cin_cmd();                              /*显示命令提示符，并接收输入的指令*/
			if(string[0]=='y') continue;            /*如果输入的字符串的首位字符是'y'，继续运行程序*/
		}
	}                                      
}




