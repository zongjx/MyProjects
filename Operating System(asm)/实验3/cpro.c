/*�ں�c����*/
extern void clear();                               /*�����ⲿ��clear()����,��������*/
extern void inputchar();                           /*�����ⲿ��inputchar()���������ڶ����ַ�*/
extern void printchar();                           /*�����ⲿ��printchar()��������������ַ�*/
extern void printstring();                         /*�����ⲿ��printstring()��������������ַ���*/
extern void setcursor();                           /*�����ⲿ��setcursor()�������������ù��*/
extern void load_prog();                           /*�����ⲿ��load_prog()���������ڼ����ⲿ����*/
extern void run_prog();                            /*�����ⲿ��run_prog()������������ת���ⲿ����*/
extern void filldata();                            /*�����ⲿ��filldata()������������������*/
extern void readdata();                            /*�����ⲿ��readdata()���������ڶ�������*/

/*���½��������ɳ���Ϊ80���ַ�������(��Ļ��󳤶�Ϊ80)�����ڴ����ʾ���*/
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
char message_cmd[80]=" O(��_��)O >";
char message_ins1[80]="User Program1:\n    Name:program_LU  Size:1024byte  Position:part LU\n";
char message_ins2[80]="User Program2:\n    Name:program_RU  Size:1024byte  Position:part RU\n";
char message_ins3[80]="User Program3:\n    Name:program_LD  Size:1024byte  Position:part LD\n";
char message_ins4[80]="User Program4:\n    Name:program_RD  Size:1024byte  Position:part RD\n";
char string[80];
char message_error[80]="Input Error!!!\n";
const char batch_order[80]="batch 1 2 3 4";
const char time_order[80]="time 1 2 3 4";
int len=0;										   /*�����ȵı���*/
int pos=0;										   /*����λ�õı���*/
char ch;										   /*����������ַ�*/
int x=0;										   /*����λ�õı���*/
int y=0;										   /*����λ�õı���*/
int i=0;										   /*���ڼ����ı���*/
int j=0;										   /*���ڼ����ı���*/
int k=0;										   /*���ڼ����ı���*/
int data=0;										   /*���ݴ洢�ı���*/
int offset_prog=37120;                             /*�û������ƫ������0910h*10h+0h=37120(��ʼλ��) */
const int offset_prog1=37120;                      /*��һ���û������ƫ�Ƶ�ַ 0910h*10h+0h=37120*/ 
const int offset_prog2=38144;                      /*�ڶ����û������ƫ�Ƶ�ַ 0950h*10h+0h=38144*/
const int offset_prog3=39168;                      /*�������û������ƫ�Ƶ�ַ 0990h*10h+0h=39168*/
const int offset_prog4=40192;                      /*���ĸ��û������ƫ�Ƶ�ַ 09d0h*10h+0h=40192*/
const int hex600h=1536;                            /*600h��ʮ����,��Ϊ�ڴ��ַ���ڱ���û�����ĵ������*/
int offset_begin=37120;                            /*��ʼλ���ڴ�ƫ����*/
int num_sector=8;                                  /*����������Ϊ8��*/
int pos_sector=2;                                  /*��ʼ�����ı��Ϊ2����һ���������õ�����������*/

int input(){                                       /*���������ַ��ĺ���*/
	inputchar();                                   /*����һ���ַ��ĺ���*/
	if(ch=='\b'){                                  /*���������ַ���ɾ����Backspace*/
		if(y>8&&y<79){                             /*������ĺ���λ������8��79֮��*/
			y--;                                   /*���������һλ*/
			cal_pos();                             /*���¼����������*/
		}
		return 0;                                  /*����������ɾ�������򷵻�0*/
	}
	else if(ch==13);                               /*�س���*/
	else printchar(ch);                            /*��������������������ʾ�ַ�*/
	return 1;                                      /*�����������������ͷ���1*/
}

cin_cmd(){                                         /*���������ʾ���ĺ���*/
	printstring(message_cmd);                      /*��ӡ�ַ����ĺ���*/
	i=0;                                           /*��ʼ�ַ����±�*/
	while(1){                                      /*whileѭ��*/
		if(input()){                               /*�������Ĳ���ɾ����*/
			if(ch==13) break;                      /*���������ַ��ǻس�����������whileѭ��*/
			string[i++]=ch;                        /*����Ѹ��ַ���ӵ�string��ĩβ*/
		}
		else if(i>0) i--;                          /*����������ɾ��������ɾ��һ���ַ�*/
	}
	for(j=0;j<i;j++)                               /*����forѭ��������string�ַ���*/
		if(string[0]==' '){                        /*����ַ�����λ�ǿո�*/
			for(k=1;k<i;k++) string[k-1]=string[k];/*����λ�ո�ȥ��*/
			i--;                                   /*�ַ������ȼ�1*/
		}
		else break;                                /*����ַ�����λ���ǿո񣬾�����ѭ��*/
	string[i]='\0';                                /*�ַ���ĩβ����һ���ո�Ҳ���԰�i-1*/
	len=i;                                         /*��¼���ַ����ĳ���i*/
	printstring("\n");                             /*����*/
}

cal_pos(){                                         /*�����ַ����������ĺ���*/
	if(y>79){                                      /*����y�������79(�������ұ߽�)*/
		y=0;                                       /*y��Ϊ0��������һ�е���ʼλ��*/
		x++;                                       /*����x��1*/
	}
	if(x>24) clear();                              /*����x����24(�������±߽�)�������Ļ����һҳ*/
	pos=(x*80+y)*2;                                /*���¼���λ��*/
	setcursor();                                   /*���ù��ĺ�������pos��λ�÷��ù��*/
}

batch(){                                           /*ʵ���������ܵĺ���*/
	clear();                                       /*���������������������ʾ������*/
	offset_begin=offset_prog1;                     /*���ó�ʼλ���ڴ�ƫ�������ڵ�һ���û������ƫ����*/
	num_sector=8;                                  /*����������Ϊ8��*/
	pos_sector=2;                                  /*��ʼ�����ı��Ϊ2*/
	load_prog(offset_begin,num_sector,pos_sector); /*װ���û������ڴ棬�����ж϶�ȡ����*/
	filldata(hex600h,0);                           /*��hex600h(600h)����ڴ�λ�����0����ʾ��һ���û������ݲ�����*/
	filldata(hex600h+2,0);                         /*��hex600h+2(602h)����ڴ�λ�����0����ʾ�ڶ����û������ݲ�����*/
	filldata(hex600h+4,0);                         /*��hex600h+4(604h)����ڴ�λ�����0����ʾ�������û������ݲ�����*/
	filldata(hex600h+6,0);                         /*��hex600h+6(606h)����ڴ�λ�����0����ʾ���ĸ��û������ݲ�����*/
    for(i=0;i<len;i++){                            /*����forѭ���������ַ���(�����ָ��)*/
		if(string[i]=='1'){                        /*����ַ����г���'1'�ַ�*/
			offset_prog=offset_prog1;              /*�ѵ�һ���û������ƫ�Ƶ�ַд�뵽��ʼ��ַ������*/
			run_prog();                            /*�������г���ĺ���(�˴���ʹ��offset_prog����)*/
		}
		else if(string[i]=='2'){                   /*����ַ����г���'2'�ַ�*/
			offset_prog=offset_prog2;              /*�ѵڶ����û������ƫ�Ƶ�ַд�뵽��ʼ��ַ������*/
			run_prog();                            /*�������г���ĺ���(�˴���ʹ��offset_prog����)*/
		}
		else if(string[i]=='3'){                   /*����ַ����г���'3'�ַ�*/
			offset_prog=offset_prog3;              /*�ѵ������û������ƫ�Ƶ�ַд�뵽��ʼ��ַ������*/
			run_prog();                            /*�������г���ĺ���(�˴���ʹ��offset_prog����)*/
		}
		else if(string[i]=='4'){                   /*����ַ����г���'4'�ַ�*/
			offset_prog=offset_prog4;              /*�ѵ��ĸ��û������ƫ�Ƶ�ַд�뵽��ʼ��ַ������*/
			run_prog();                            /*�������г���ĺ���(�˴���ʹ��offset_prog����)*/
		}
	}
}

time(){                                            /*ʵ��α��ʱ����ĺ���*/
	clear();                                       /*���������������������ʾ������*/
	offset_begin=offset_prog1;                     /*���ó�ʼλ���ڴ�ƫ�������ڵ�һ���û������ƫ����*/
	num_sector=8;                                  /*����������Ϊ8��*/
	pos_sector=2;                                  /*��ʼ�����ı��Ϊ2*/
	load_prog(offset_begin,num_sector,pos_sector); /*װ���û������ڴ棬�����ж϶�ȡ����*/
	filldata(hex600h,0);                           /*��hex600h(600h)����ڴ�λ�����0����ʾ��һ���û������ݲ�����*/
	filldata(hex600h+2,0);                         /*��hex600h+2(602h)����ڴ�λ�����0����ʾ�ڶ����û������ݲ�����*/
	filldata(hex600h+4,0);                         /*��hex600h+4(604h)����ڴ�λ�����0����ʾ�������û������ݲ�����*/
	filldata(hex600h+6,0);                         /*��hex600h+6(606h)����ڴ�λ�����0����ʾ���ĸ��û������ݲ�����*/
	for(i=0;i<len;i++){                            /*����forѭ���������ַ���(�����ָ��)*/
		if(string[i]=='1')                         /*����ַ����г���'1'�ַ�*/
			filldata(hex600h,1);                   /*��hex600h(600h)����ڴ�λ�����1����ʾ��һ���û����򽫻�����*/
		else if(string[i]=='2')                    /*����ַ����г���'2'�ַ�*/
			filldata(hex600h+2,1);                 /*��hex600h(602h)����ڴ�λ�����1����ʾ�ڶ����û����򽫻�����*/
		else if(string[i]=='3')                    /*����ַ����г���'3'�ַ�*/
			filldata(hex600h+4,1);                 /*��hex600h(604h)����ڴ�λ�����1����ʾ�������û����򽫻�����*/ 
		else if(string[i]=='4')                    /*����ַ����г���'4'�ַ�*/
			filldata(hex600h+6,1);                 /*��hex600h(606h)����ڴ�λ�����1����ʾ���ĸ��û����򽫻�����*/ 
	}
	while(1){                                      /*����whileѭ�������򽫻��ʱ����*/
		j=0;                                       /*��¼��j��ʼΪ0���˴����ڼ�¼�����г�������*/
		readdata(hex600h);                         /*��ȡhex600h(600h)��ַ�е�ֵ��ȡ�������ݽ���浽data������*/
		j+=data;                                   /*��data��ֵ�ӵ���¼��j��*/
		if(data){                                  /*���data�е�ֵ��0*/
			offset_prog=offset_prog1;              /*�ѵ�һ���û������ƫ�Ƶ�ַд�뵽��ʼ��ַ������*/
			run_prog();                            /*�������г���ĺ���(�˴���ʹ��offset_prog����)*/
		}
		readdata(hex600h+2);                       /*��ȡhex600h+2(602h)��ַ�е�ֵ��ȡ�������ݽ���浽data������*/
        j+=data;                                   /*��data��ֵ�ӵ���¼��j��*/
		if(data){                                  /*���data�е�ֵ��0*/
			offset_prog=offset_prog2;              /*�ѵڶ����û������ƫ�Ƶ�ַд�뵽��ʼ��ַ������*/
			run_prog();
		}		
        readdata(hex600h+4);                       /*��ȡhex600h+4(604h)��ַ�е�ֵ��ȡ�������ݽ���浽data������*/
        j+=data;                                   /*��data��ֵ�ӵ���¼��j��*/
		if(data){                                  /*���data�е�ֵ��0*/
			offset_prog=offset_prog2;              /*�ѵ������û������ƫ�Ƶ�ַд�뵽��ʼ��ַ������*/
			run_prog();                            /*�������г���ĺ���(�˴���ʹ��offset_prog����)*/
		}
        readdata(hex600h+6);                       /*��ȡhex600h+6(606h)��ַ�е�ֵ��ȡ�������ݽ���浽data������*/
        j+=data;                                   /*��data��ֵ�ӵ���¼��j��*/
		if(data){                                  /*���data�е�ֵ��0*/
			offset_prog=offset_prog2;              /*�ѵ��ĸ��û������ƫ�Ƶ�ַд�뵽��ʼ��ַ������*/
			run_prog();                            /*�������г���ĺ���(�˴���ʹ��offset_prog����)*/
		}
		if(j==0) break;                            /*���4�����ݶ�Ϊ0�����˳�ѭ��*/
	}                                       
}

cmain(){                                            /*������*/ 
	while(1){                                       /*����whileѭ������ʼ���г���*/
		clear();                                    /*��������*/
		printstring(message1);                      /*��ӡmessage1�ַ���*/
		printstring(message2);                      /*��ӡmessage2�ַ���*/
		printstring(message3);                      /*��ӡmessage3�ַ���*/
		printstring(message4);                      /*��ӡmessage4�ַ���*/
		printstring(message5);                      /*��ӡmessage5�ַ���*/
		printstring(message6);                      /*��ӡmessage6�ַ���*/
		printstring(message7);                      /*��ӡmessage7�ַ���*/
		printstring(message8);                      /*��ӡmessage8�ַ���*/
		printstring(message9);                      /*��ӡmessage9�ַ���*/
		printstring(message10);                     /*��ӡmessage10�ַ���*/
		printstring(message11);                     /*��ӡmessage11�ַ���*/
		cin_cmd();                                  /*��ʾ������ʾ���������������ָ��*/
		if(string[0]=='b'){                         /*������յ���ָ�����λ�ַ���'b'������ζ�ŵ������������ܵĺ���*/
			batch();                                /*����batch������ʵ����������*/
			printstring(message12);                 /*��ӡmassage12�ַ���*/
			cin_cmd();                              /*��ʾ������ʾ���������������ָ��*/
			if(string[0]=='y') continue;            /*���������ַ�������λ�ַ���'y'�������½���whileѭ��*/
		}
		else if(string[0]=='t'){                    /*������յ���ָ�����λ�ַ���'t'������ζ�ŵ�����α��ʱ���ܵĺ���*/
			batch();                                /*����batch������ʵ����������*/
			printstring(message12);                 /*��ӡmassage12�ַ���*/
			cin_cmd();                              /*��ʾ������ʾ���������������ָ��*/
			if(string[0]=='y') continue;            /*���������ַ�������λ�ַ���'y'�������½���whileѭ��*/
		}
		else if(string[0]=='s'){                    /*������յ���ָ�����λ�ַ���'s'������ʾÿ���������Ϣ*/
			printstring(message_ins1);              /*��ӡmassage_ins1�ַ���*/
			printstring(message_ins2);              /*��ӡmassage_ins2�ַ���*/
			printstring(message_ins3);              /*��ӡmassage_ins3�ַ���*/
			printstring(message_ins4);              /*��ӡmassage_ins4�ַ���*/
			cin_cmd();                              /*��ʾ������ʾ���������������ָ��*/
			if(string[0]=='y') continue;            /*���������ַ�������λ�ַ���'y'�������½���whileѭ��*/
		}
		else if(string[0]=='d'){                    /*������յ���ָ�����λ�ַ���'d'������ʾÿ���������Ϣ*/
			printstring(message13);                 /*��ӡmassage13�ַ���*/
			printstring(message12);                 /*��ӡmassage12�ַ���*/
			cin_cmd();                              /*��ʾ������ʾ���������������ָ��*/
			if(string[0]=='y'){                     /*���������ַ�������λ�ַ���'y'*/
				for(i=0;i<len;i++){                 /*����forѭ��,���������ܵ�ָ��浽string��*/
					string[i]=batch_order[i];       /*�ַ���(������ָ��)ת��*/
					if(batch_order[i]=='\0'){       /*��������ַ���β��*/
						len=i;                      /*��¼���ַ����ĳ���*/
						break;                      /*����forѭ��*/
					}
				}
				batch();                            /*����batch������ʵ����������*/
				printstring(message12);             /*��ӡmassage12�ַ���*/
				cin_cmd();                          /*��ʾ������ʾ���������������ָ��*/
				if(string[0]=='y') continue;        /*���������ַ�������λ�ַ���'y'���������г���*/
				for(i=0;i<len;i++){                 /*����forѭ��,���������ܵ�ָ��浽string��*/
					string[i]=time_order[i];        /*�ַ���(α��ʱָ��)ת��*/
					if(time_order[i]=='\0'){        /*��������ַ���β��*/
						len=i;                      /*��¼���ַ����ĳ���*/
						break;                      /*����forѭ��*/
					}
				}
				time();                             /*����time������ʵ����������*/
				printstring(message12);             /*��ӡmassage12�ַ���*/
				cin_cmd();                          /*��ʾ������ʾ���������������ָ��*/
			}		
		}
		else{
			printstring(message_error);             /*��ӡmassage_error�ַ���*/
			printstring(message12);                 /*��ӡmassage12�ַ���*/
			cin_cmd();                              /*��ʾ������ʾ���������������ָ��*/
			if(string[0]=='y') continue;            /*���������ַ�������λ�ַ���'y'���������г���*/
		}
	}                                      
}




