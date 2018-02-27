/*�ں�c����*/
extern void clear();                               /*�����ⲿ��clear()����,��������*/
extern void inputchar();                           /*�����ⲿ��inputchar()���������ڶ����ַ�*/
extern void printchar();                           /*�����ⲿ��printchar()��������������ַ�*/
extern void printstring();                         /*�����ⲿ��printstring()��������������ַ���*/
extern void setcursor();                           /*�����ⲿ��setcursor()�������������ù��*/
extern void load_prog();                           /*�����ⲿ��load_prog()���������ڼ����ⲿ����*/
extern void run_prog();                            /*�����ⲿ��run_prog()������������ת���ⲿ����*/
extern int put_color_char();                       /*�����ⲿ��put_color_char()���������ڴ�ӡ��ɫ�ַ�*/

/*���½��������ɳ���Ϊ80���ַ�������(��Ļ��󳤶�Ϊ80)�����ڴ����ʾ���*/
char message1[80]="\n Welcome to our team's system!\n";
char message3[80]=" You can input some legal instructions to active the functions\n";
char message4[80]="    If you want to run the program by Batching,input \'batch\'\n";
char message5[80]="       For example: batch 1 2 3 4\n";
char message6[80]="    If you want to run the program by Time-Sharing,input \'time\'\n";
char message7[80]="       For example: time 1 2 3 4\n";
char message8[80]="    If you want to know the information of the program,input \'show\'\n";
char message9[80]="       For example: show\n";
char message10[80]="    If you want to run the default instructions,input \'default\'\n";
char message11[80]="       For example: default\n";
char message12[80]="\n If you want to continue,input \'yes\',otherwise input \'no\'\n";
char message13[80]="\n OS will run instructions \'batch 1 2 3 4\' and \'time 1 2 3 4\'\n";
char message14[80]="    If you want to run the interrupt test program,input \'interrupt\'\n";
char message15[80]="       For example: interrupt\n\n";
char message16[80]="       Show as below:\n";
char message_cmd[80]=" Orz >";
char message_ins1[80]=" User Program1:\n    Name:program_LU  Size:1024byte  Position:part LU\n";
char message_ins2[80]=" User Program2:\n    Name:program_RU  Size:1024byte  Position:part RU\n";
char message_ins3[80]=" User Program3:\n    Name:program_LD  Size:1024byte  Position:part LD\n";
char message_ins4[80]=" User Program4:\n    Name:program_RD  Size:1024byte  Position:part RD\n";
char message_ins5[80]=" Interrupt Program:\n    Name:program_Interrupt  Size:1024byte \n";
char string[80];
char message_error[20]=" Input Error!!!\n";
const char batch_order[20]="batch 1 2 3 4";
const char time_order[80]="time 1 2 3 4";
int len=0;										   /*�����ȵı���*/
int pos=0;										   /*����λ�õı���*/
char ch;										   /*����������ַ�*/
int x=0;										   /*����λ�õı���*/
int y=0;										   /*����λ�õı���*/
int i=0;										   /*���ڼ����ı���*/
int j=0;										   /*���ڼ����ı���*/
int k=0;										   /*���ڼ����ı���*/
int data1=0;									   /*���ݴ洢�ı���*/
int offset_prog=41216;                             /*�û������ƫ������0a10h*10h+0h=37120(��ʼλ��) */
const int offset_prog1=41216;                      /*��һ���û������ƫ�Ƶ�ַ 0a10h*10h+0h=37120*/ 
const int offset_prog2=42240;                      /*�ڶ����û������ƫ�Ƶ�ַ 0a50h*10h+0h=38144*/
const int offset_prog3=43264;                      /*�������û������ƫ�Ƶ�ַ 0a90h*10h+0h=39168*/
const int offset_prog4=44288;                      /*���ĸ��û������ƫ�Ƶ�ַ 0ad0h*10h+0h=40192*/
const int offset_prog_int=45312;                   /*�����жϵ��û������ƫ�Ƶ�ַ 0b10h*10h+0h=45312*/
const int hex600h=1536;                            /*600h��ʮ����,��Ϊ�ڴ��ַ���ڱ���û�����ĵ������*/
int offset_begin=41216;                            /*��ʼλ���ڴ�ƫ����*/
int num_sector=10;                                 /*����������Ϊ10��*/
int pos_sector=2;                                  /*��ʼ�����ı��Ϊ2����һ���������õ�����������*/

char rch;                                          /*��ʾҪ�����һ���ַ���������ʾ��ת�ĸ�*/                                           
int is_rotate,rpx,rpy,rcolor;                      /*���ͱ��������ڼ�¼�ַ���ӡ�����ꡢ��ɫ����ʼ��״̬*/   
int rotate_state;                                  /*���ͱ�����ʾ����ת��״̬*/   
c_rotate(){                                        /*������ת�ĸܵĺ���*/   
	rpx=23;                                        /*�̶�������Ϊ23*/   
	rpy=78;                                        /*�̶�������Ϊ79*/
	rcolor=15;                                     /*��ɫΪ�ڵװ���*/
	put_color_char('O',rpx,68,rcolor);             /*���¼��д���������ת�ĺ��ǰ���Running����*/
	put_color_char('S',rpx,69,rcolor);            
	put_color_char('R',rpx,71,rcolor);            
	put_color_char('u',rpx,72,rcolor);            
	put_color_char('n',rpx,73,rcolor);            
	put_color_char('n',rpx,74,rcolor);            
	put_color_char('i',rpx,75,rcolor);            
	put_color_char('n',rpx,76,rcolor);            
	put_color_char('g',rpx,77,rcolor);            
	if(is_rotate!=1){                              /*������û����ת*/
		rotate_state=1;                            /*��ʼ����ܵ�״̬*/
		is_rotate=1;                               /*�Ѻ������Ϊ��ת״̬*/
	}                                              
	if(rotate_state==1){                           /*���״̬Ϊ1�������Ϊ'-'*/
		rch='-';                                   
		put_color_char(rch,rpx,rpy,rcolor);        /*���'-'*/
		rotate_state++;                            /*״̬��1��Ҳ����ʱ*/
	}                                              
	else if(rotate_state==4){                      /*���״̬Ϊ4�������Ϊ'/'*/
		rch='/';
		put_color_char(rch,rpx,rpy,rcolor);        /*���'/'*/
		rotate_state++;                            /*״̬��1��Ҳ����ʱ*/
	}
	else if(rotate_state==7){                      /*���״̬Ϊ7�������Ϊ'|'*/
		rch='|';
		put_color_char(rch,rpx,rpy,rcolor);        /*���'|'*/
		rotate_state++;                            /*״̬��1��Ҳ����ʱ*/
	}
	else if(rotate_state==10){                     /*���״̬Ϊ10�������Ϊ'\'*/
		rch='\\';
		put_color_char(rch,rpx,rpy,rcolor);        /*���'\'*/
		rotate_state=1;                            /*״̬��1��Ҳ����ʱ*/
	}
	else{                                          /*���������״̬*/
		rotate_state++;                            /*״̬��1��Ҳ����ʱ*/
	}
}

int is_ouch;                                       /*���ͱ����������ж��Ƿ��Ѿ���ʼ��*/
c_ouch(){                                          /*�����ж���ʾOuch����*/
	if(is_ouch==1){                                /*��ʼ��*/
		x=y=pos=0;                                 /*��ʼλ��Ϊ���Ͻ�*/
		is_ouch=0;                                 /*��Ǹ���*/
	}
	printstring("Ouch!");                          /*��ӡ"Ouch!"*/
}


int px,py,pcolor,pdir,pbegin;                      /*���ͱ��������ڼ�¼�ַ���ӡ�����ꡢ��ɫ�����򡢳�ʼ��״̬*/
char pch;                                          /*��ʾҪ��ӡ���ַ��ķ��ű���*/
int pdx[4];                                        /*��ʾ�ַ�ת����������*/
int pdy[4];                                        /*��ʾ�ַ�ת����������*/
c_paint(){                                         /*ʱ���жϻ��߿����*/
	if(pbegin!=1)                                  /*��ʼ��*/
	{
		px=0;                                      /*��ʼ������Ϊ0*/
		py=0;                                      /*��ʼ������*/
		pcolor=1;                                  /*��ʼ��ɫΪ1*/
		pdir=0;                                    /*��ʼ����*/
		pch='Z';                                   /*��ʼ�ַ�Ϊ'Z'*/
		pbegin=1;                                  /*�ı��ʼ����־*/
		pdx[0]=1,pdx[1]=0,pdx[2]=-1,pdx[3]=0;      /*�����������*/
		pdy[0]=0,pdy[1]=1,pdy[2]=0,pdy[3]=-1;      /*�����������*/
	}
	put_color_char(pch,px,py,pcolor);              /*��ʾ�ַ���������ɫ��λ��*/
	pcolor=(pcolor+1)%15+1;                        /*������ɫ*/
	px+=pdx[pdir];                                 /*���������귽��*/
	py+=pdy[pdir];                                 /*���º����귽��*/
	if(pdir==1||pdir==3)                           /*������Ϸ����·���������ʾһ���ַ���������λ��*/
	{	
		if(py>0&&py<79)
		{
			put_color_char(pch,px,py,pcolor);
			px+=pdx[pdir];
			py+=pdy[pdir];	
		}
	}
	if(px==py&&px==0) pch--;                       /*�����ϽǶ������ַ�*/
	if(pch=='A') pch='Z';                          /*���ַ�����'A'��ʱ�򣬱��'Z'*/
	
	if(px==24&&py==0||
		px==24&&py==79||
		px==0&&py==79||
		px==0&&py==0) pdir=(pdir+1)%4;             /*���ĸ��ǵĶ�����������*/
}

int input(){                                       /*���������ַ��ĺ���*/
	inputchar();                                   /*����һ���ַ��ĺ���*/
	if(ch=='\b'){                                  /*���������ַ���ɾ����Backspace*/
		if(y>6&&y<79){                             /*������ĺ���λ������6��79֮��*/
			y--;                                   /*���������һλ*/
			cal_pos();                             /*���¼����������*/
			printchar(' ');                        /*���һ���հ׸�*/
			y--;                                   /*y�����Լ�1*/
			cal_pos();                             /*���¼������λ��*/
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
	num_sector=10;                                 /*����������Ϊ10��*/
	pos_sector=2;                                  /*��ʼ�����ı��Ϊ2*/
	load_prog(offset_begin,num_sector,pos_sector); /*װ���û������ڴ棬�����ж϶�ȡ����*/
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

interrupt1(){                                      /*���ó�����ʾ�ĸ��ж�Ч���ĺ���*/
	clear();                                       /*���������������������ʾ������*/
	offset_begin=offset_prog1;                     /*���ó�ʼλ���ڴ�ƫ�������ڵ�һ���û������ƫ����*/ 
	num_sector=10;                                 /*����������Ϊ10��*/
	pos_sector=2;                                  /*��ʼ�����ı��Ϊ2*/
	load_prog(offset_begin,num_sector,pos_sector); /*װ���û������ڴ棬�����ж϶�ȡ����*/
	offset_prog=offset_prog_int;                   /*���������жϳ���ĺ���(�˴���ʹ��offset_prog����)*/
	run_prog();                                    /*����*/
}

time(){                                            /*ʵ��α��ʱ����ĺ���*/
	clear();                                       /*���������������������ʾ������*/
	offset_begin=offset_prog1;                     /*���ó�ʼλ���ڴ�ƫ�������ڵ�һ���û������ƫ����*/
	num_sector=10;                                 /*����������Ϊ10��*/
	pos_sector=2;                                  /*��ʼ�����ı��Ϊ2*/
	load_prog(offset_begin,num_sector,pos_sector); /*װ���û������ڴ棬�����ж϶�ȡ����*/
	filldata(hex600h,0);                           /*��hex600h(600h)����ڴ�λ�����0����ʾ��һ���û������ݲ�����*/
	filldata(hex600h+2,0);                         /*��hex600h+2(602h)����ڴ�λ�����0����ʾ�ڶ����û������ݲ�����*/
	filldata(hex600h+4,0);                         /*��hex600h+4(604h)����ڴ�λ�����0����ʾ�������û������ݲ�����*/
	filldata(hex600h+6,0);                         /*��hex600h+6(606h)����ڴ�λ�����0����ʾ���ĸ��û������ݲ�����*/
	for(i=0;i<len;++i){                            /*����forѭ���������ַ���(�����ָ��)*/
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
		j+=data1;                                   /*��data��ֵ�ӵ���¼��j��*/
		if(data1){                                  /*���data�е�ֵ��0*/
			offset_prog=offset_prog1;              /*�ѵ�һ���û������ƫ�Ƶ�ַд�뵽��ʼ��ַ������*/
			run_prog();                            /*�������г���ĺ���(�˴���ʹ��offset_prog����)*/
		}
		readdata(hex600h+2);                       /*��ȡhex600h+2(602h)��ַ�е�ֵ��ȡ�������ݽ���浽data������*/
        j+=data1;                                   /*��data��ֵ�ӵ���¼��j��*/
		if(data1){                                  /*���data�е�ֵ��0*/
			offset_prog=offset_prog2;              /*�ѵڶ����û������ƫ�Ƶ�ַд�뵽��ʼ��ַ������*/
			run_prog();
		}		
        readdata(hex600h+4);                       /*��ȡhex600h+4(604h)��ַ�е�ֵ��ȡ�������ݽ���浽data������*/
        j+=data1;                                   /*��data��ֵ�ӵ���¼��j��*/
		if(data1){                                  /*���data�е�ֵ��0*/
			offset_prog=offset_prog3;              /*�ѵ������û������ƫ�Ƶ�ַд�뵽��ʼ��ַ������*/
			run_prog();                            /*�������г���ĺ���(�˴���ʹ��offset_prog����)*/
		}
        readdata(hex600h+6);                       /*��ȡhex600h+6(606h)��ַ�е�ֵ��ȡ�������ݽ���浽data������*/
        j+=data1;                                   /*��data��ֵ�ӵ���¼��j��*/
		if(data1){                                  /*���data�е�ֵ��0*/
			offset_prog=offset_prog4;              /*�ѵ��ĸ��û������ƫ�Ƶ�ַд�뵽��ʼ��ַ������*/
			run_prog();                            /*�������г���ĺ���(�˴���ʹ��offset_prog����)*/
		}
		if(j==0) break;                            /*���4�����ݶ�Ϊ0�����˳�ѭ��*/
	}                                       
}

main(){                                            /*������*/ 
	while(1){                                       /*����whileѭ������ʼ���г���*/
		clear();                                    /*��������*/
		printstring(message1);                      /*��ӡmessage1�ַ���*/
		printstring(message3);                      /*��ӡmessage3�ַ���*/
		printstring(message4);                      /*��ӡmessage4�ַ���*/
		printstring(message5);                      /*��ӡmessage5�ַ���*/
		printstring(message6);                      /*��ӡmessage6�ַ���*/
		printstring(message7);                      /*��ӡmessage7�ַ���*/
		printstring(message8);                      /*��ӡmessage8�ַ���*/
		printstring(message9);                      /*��ӡmessage9�ַ���*/
		printstring(message10);                     /*��ӡmessage10�ַ���*/
		printstring(message11);                     /*��ӡmessage11�ַ���*/
		printstring(message14);                     /*��ӡmessage14�ַ���*/
		printstring(message15);                     /*��ӡmessage15�ַ���*/
		cin_cmd();                                  /*��ʾ������ʾ���������������ָ��*/
		if(string[0]=='b'){                         /*������յ���ָ�����λ�ַ���'b'������ζ�ŵ������������ܵĺ���*/
			batch();                                /*����batch������ʵ����������*/
			printstring(message12);                 /*��ӡmassage12�ַ���*/
			cin_cmd();                              /*��ʾ������ʾ���������������ָ��*/
			if(string[0]=='y') continue;            /*���������ַ�������λ�ַ���'y'�������½���whileѭ��*/
		}
		else if(string[0]=='t'){                    /*������յ���ָ�����λ�ַ���'t'������ζ�ŵ�����α��ʱ���ܵĺ���*/
			time();                                 /*����batch������ʵ����������*/
			printstring(message12);                 /*��ӡmassage12�ַ���*/
			cin_cmd();                              /*��ʾ������ʾ���������������ָ��*/
			if(string[0]=='y') continue;            /*���������ַ�������λ�ַ���'y'�������½���whileѭ��*/
		}
		else if(string[0]=='i'){                    /*������յ���ָ�����λ�ַ���'i'������ζ�ŵ������жϹ��ܵĺ���*/
			interrupt1();                           /*����interrupt������ʵ���ж�*/
			printstring(message12);                 /*��ӡmassage12�ַ���*/
			cin_cmd();                              /*��ʾ������ʾ���������������ָ��*/    
			if(string[0]=='y') continue;            /*���������ַ�������λ�ַ���'y'�������½���whileѭ��*/
		}
		else if(string[0]=='s'){                    /*������յ���ָ�����λ�ַ���'s'������ʾÿ���������Ϣ*/
		    printstring(message_ins1);              /*�����ڴ�ӡ��Щ�ַ�����ʱ�򣬸պô�ӡ���������һҳ���¿������κζ���*/
			printstring(message_ins1);              /*��˶���������ַ�����ҳ��ѹ����һҳ�Ŀ�ͷ*/
			printstring(message1);
			printstring(message_ins1);
			printstring(message_ins1);
			printstring(message16);
			printstring(message_ins1);              /*��ӡmassage_ins1�ַ���*/
			printstring(message_ins2);              /*��ӡmassage_ins2�ַ���*/
			printstring(message_ins3);              /*��ӡmassage_ins3�ַ���*/
			printstring(message_ins4);              /*��ӡmassage_ins4�ַ���*/
			printstring(message_ins5);              /*��ӡmassage_ins5�ַ���*/
			printstring(message12);                 /*��ӡmassage12�ַ���*/
			cin_cmd();                              /*��ʾ������ʾ���������������ָ��*/
			if(string[0]=='y') continue;            /*���������ַ�������λ�ַ���'y'�������½���whileѭ��*/
		}
		else if(string[0]=='d'){                    /*������յ���ָ�����λ�ַ���'d'������ʾÿ���������Ϣ*/
			printstring(message13);                 /*��ӡmassage13�ַ���*/
			printstring(message12);                 /*��ӡmassage12�ַ���*/
			cin_cmd();                              /*��ʾ������ʾ���������������ָ��*/
			if(string[0]=='y'){                     /*���������ַ�������λ�ַ���'y'*/
				for(i=0;i<80;i++){                 /*����forѭ��,���������ܵ�ָ��浽string��*/
					string[i]=batch_order[i];       /*�ַ���(������ָ��)ת��*/
					if(batch_order[i]=='\0'){       /*��������ַ���β��*/
						len=i;                      /*��¼���ַ����ĳ���*/
						break;                      /*����forѭ��*/
					}
				}
				batch();                            /*����batch������ʵ����������*/
				printstring(message12);             /*��ӡmassage12�ַ���*/
				cin_cmd();                          /*��ʾ������ʾ���������������ָ��*/
				if(string[0]!='y') continue;        /*���������ַ�������λ�ַ���'y'���������г���*/
				for(i=0;i<80;i++){                 /*����forѭ��,���������ܵ�ָ��浽string��*/
					string[i]=time_order[i];        /*�ַ���(α��ʱָ��)ת��*/
					if(time_order[i]=='\0'){        /*��������ַ���β��*/
						len=i;                      /*��¼���ַ����ĳ���*/
						break;                      /*����forѭ��*/
					}
				}
				time();   
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
