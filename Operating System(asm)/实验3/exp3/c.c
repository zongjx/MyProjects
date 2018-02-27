extern void clear();
extern void inputchar();
extern void printchar();
extern void printstring();
extern void setcursor();
extern void load();
extern void jmp();
extern void filldata();
extern void readdata();

char message1[80]="Welcome to use system of Wang Shuocheng\n";
char message2[80]="you can input some legal instructions\n";
char message3[80]="    if you want to run the program by Batching,input \'batch\'\n";
char message4[80]="       for example: batch 1 2 3 4\n";
char message5[80]="    if you want to run the program by Time-Sharing,input \'time\'\n";
char message6[80]="       for example: time 1 2 3 4\n";
char message7[80]="    if you want to know the information of the program,input \'show\'\n";
char message8[80]="       for example: show\n";
char message9[80]="    if you want to run the default instructions,input \'default\'\n";
char message10[80]="       for example: default\n\n";
char message11[80]="If you want to continue,input \'yes\'\n";
char message12[80]="OS will run instructions \'batch 1 2 3 4\' and \'time 1 2 3 4\'\n";
char message_cmd[80]="Orange> ";
char message_show1[80]="USER PROGRAM1:\n   Name:orange1,Size:1024byte,Position:section 2\n";
char message_show2[80]="USER PROGRAM2:\n   Name:orange2,Size:1024byte,Position:section 4\n";
char message_show3[80]="USER PROGRAM3:\n   Name:orange3,Size:1024byte,Position:section 6\n";
char message_show4[80]="USER PROGRAM4:\n   Name:orange4,Size:1024byte,Position:section 8\n";
char string[80];
char message_error[80]="INPUT ERROR!!\n";
const char default1[80]="batch 1 2 3 4";
const char default2[80]="time 1 2 3 4";
int len=0;
int pos=0;
char ch;
int x=0;
int y=0;
int i=0;
int a=0;
int u=0;
int d=0;/*data*/
int offset_user=37120;/*用户程序偏移量*/
const int offset_user1=37120;/*9100h*/
const int offset_user2=38144;/*9500h*/
const int offset_user3=39168;/*9900h*/
const int offset_user4=40192;/*9d00h*/
const int hex600h=1536;/*600h*/
int offset_begin=37120;/*读到内存的偏移量*/
int num_shanqu=8;/*扇区数*/
int pos_shanqu=2;/*起始扇区数*/

int input()
{
	inputchar();/*输入字符*/
	if(ch=='\b'){/*是删除键Backspace*/
		if(y>8&&y<79){
			y--;
			cal_pos();
/*在前一位置显示空格，并显示后回退一个位置*/
			printchar(' ');
			y--;
			cal_pos();
		}
		return 0;
	}
	else if(ch==13);/*是回车*/
	else printchar(ch);/*显示字符*/
	return 1;
}

cin_cmd(){
	printstring(message_cmd);
	i=0;/*初始字符串下标*/
	while(1)
	{
		if(input()){/*不是删除键*/
			if(ch==13) break;/*是回车*/
			string[i++]=ch;
		}
		else if(i>0) i--; /*是删除键，则删除*/
	}
	/*去掉字符串前面的空格*/
	for(a=0;a<i;++a)
		if(string[0]==' '){
			for(u=1;u<i;++u) string[u-1]=string[u];
			i--;
		}
		else break;
	string[i]='\0';/*末尾加空字符*/
	len=i;/*记录字符串长度*/
	printstring("\n");
}

cal_pos()
{	
	if(y>79){
		y=0;
		x++;
	}
	if(x>24) clear();
	pos=(x*80+y)*2;
	setcursor();
}

batch()
{
	clear();/*清屏*/
	offset_begin=offset_user1;/*内存偏移量*/
	num_shanqu=8;/*扇区数目*/
	pos_shanqu=2;/*起始扇区号*/
	load(offset_begin,num_shanqu,pos_shanqu);/*装载用户程序到内存*/
	/*向600h,602h,604h,606h送0*/
	filldata(hex600h,0);
	filldata(hex600h+2,0);
	filldata(hex600h+4,0);
	filldata(hex600h+6,0);
	for(i=0;i<len;++i)/*遍历字符串*/
	{
		if(string[i]=='1')/*跳转到用户程序1*/
		{
			offset_user=offset_user1;
			jmp();
		}
		else if(string[i]=='2')/*跳转到用户程序2*/
		{
			offset_user=offset_user2;
			jmp();
		}
		else if(string[i]=='3')/*跳转到用户程序3*/
		{
			offset_user=offset_user3;
			jmp();
		}
		else if(string[i]=='4')/*跳转到用户程序4*/
		{
			offset_user=offset_user4;
			jmp();
		}
	}
}
time()
{
	clear();
	offset_begin=offset_user1;
	num_shanqu=8;
	pos_shanqu=2;
	load(offset_begin,num_shanqu,pos_shanqu);
	filldata(hex600h,0);
	filldata(hex600h+2,0);
	filldata(hex600h+4,0);
	filldata(hex600h+6,0);
	for(i=0;i<len;++i)
	{
		if(string[i]=='1') filldata(hex600h,1);/*向600h送1*/
		else if(string[i]=='2') filldata(hex600h+2,1);/*向602h送1*/
		else if(string[i]=='3') filldata(hex600h+4,1);/*向604h送1*/
		else if(string[i]=='4') filldata(hex600h+6,1);/*向606h送1*/
	}
	while(1)
	{
		a=0;/*总和为a*/
		readdata(hex600h);/*读600h数据到d*/
		a+=d;/*读取的数据d加到总和a中*/
		if(d)/*如果数据为1，则跳转到用户程序1*/
		{
			offset_user=offset_user1;
			jmp();
		}
		readdata(hex600h+2);
		a+=d;
		if(d)/*如果数据为1，则跳转到用户程序2*/
		{
			offset_user=offset_user2;
			jmp();
		}
		readdata(hex600h+4);
		a+=d;
		if(d)/*如果数据为1，则跳转到用户程序3*/
		{
			offset_user=offset_user3;
			jmp();
		}
		readdata(hex600h+6);
		a+=d;
		if(d)/*如果数据为1，则跳转到用户程序4*/
		{
			offset_user=offset_user4;
			jmp();
		}
		if(a==0) break;/*4个数据都为0,则退出循环*/
	}
}
cmain(){
	while(1)
{
	clear();
	printstring(message1);
	printstring(message2);
	printstring(message3);
	printstring(message4);
	printstring(message5);
	printstring(message6);
	printstring(message7);
	printstring(message8);
	printstring(message9);
	printstring(message10);
	cin_cmd();
	if(string[0]=='b')
	{
		batch();
		printstring(message11);
		cin_cmd();
		if(string[0]=='y') continue;
	}
	else if(string[0]=='t')
	{
		time();
		printstring(message11);
		cin_cmd();
		if(string[0]=='y') continue;
	}
	else if(string[0]=='s')
	{
		printstring(message_show1);
		printstring(message_show2);
		printstring(message_show3);
		printstring(message_show4);
		printstring(message11);
		cin_cmd();
		if(string[0]=='y') continue;
	}
	else if(string[0]=='d')
	{
		printstring(message12);
		printstring(message11);
		cin_cmd();
		if(string[0]=='y')
		{
			for(i=0;i<80;++i){
				string[i]=default1[i];
				if(default1[i]=='\0')
				{
					len=i;
					break;
				}
			}
			batch();
			
			printstring(message11);
			cin_cmd();
			if(string[0]!='y') continue;
			for(i=0;i<80;++i){
				string[i]=default2[i];
				if(default2[i]=='\0')
				{
					len=i;
					break;
				}
			}
			time();
			printstring(message11);
			cin_cmd();
		}
	}
	else{
		printstring(message_error);
		printstring(message11);
		cin_cmd();
		if(string[0]=='y') continue;
	}
}
}

