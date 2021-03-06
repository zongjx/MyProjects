extern void printChar();
extern void put_color_char();
extern void getChar();
extern void show_Time();
extern void show_Date();
extern void cls();
extern void Run();
extern void int33h();
extern void int34h();
extern void int35h();
extern void int36h();
extern void Fun_Upper(char* word);
extern void Fun_Lower(char* word);
extern int  String_to_Num(char* word);
extern void Num_to_String(int word);
extern void Binary_to_Decimal(char* word);
extern void Print_String( char* word,char row,char col );
extern void Load_Int21();
extern void Print_CoLor_String( char* word,char row,char col );
extern int  If_Equal( char* word1,char* word2 );
extern void Show_Orch();
extern void setClock();
extern void another_load(int segment,int offset);
extern void Open_Key_Int();
extern void Close_Key_Int();
extern void memcpy();
extern void PCB_Restart();

int Segment = 0x2000;

#include "kdata.h"

#define BUFLEN 1000
char *disp_pos;
char input;
char Buffer[BUFLEN];
char TempBuffer[BUFLEN];

int ColorOfOuch;
int index;
char century,year,month,day;
char hour,minute,second;
int century1,year1,month1,day1;
int hour1,minute1,second1;
int i,j;
int bl;
int ASCII_Num;
char Pro;
char Function_Num;
int StringLen;
int StringLen2;
int Num;
char row,col;
int dir;


void GetInput();
void Print( char* word );
int check( char* word,char* goal );
void Transfor( int num );
void PrintTime();
void PrintDate();
void Initial();
void CheckASCII();
void RunProgram();
void PrintIns();
int BCDdecode( int n );
void Print_Int( int n );
void Bin_to_Dec( char* word );
char String_to_Int( char* word );
void GetInput2();
void Call_Int21();
void start();
int String_to_Int2( char* word );
int If_NumString( char* word );
int If_Binary( char* word );
void Random_Load();
void load_test();
void init_Pro();
void Delay();
void Delay2();

int px,py,pcolor,pdir,pbegin;                      /*整型变量，用于记录字符打印的坐标、颜色、方向、初始化状态*/
char pch;                                          /*表示要打印的字符的符号变量*/
int pdx[4];                                        /*表示字符转弯的数组变量*/
int pdy[4];                                        /*表示字符转弯的数组变量*/
c_paint(){                                         /*时钟中断画边框程序*/
	if(pbegin!=1)                                  /*初始化*/
	{
		px=0;                                      /*初始纵坐标为0*/
		py=0;                                      /*初始横坐标*/
		pcolor=1;                                  /*初始颜色为1*/
		pdir=0;                                    /*初始方向*/
		pch='Z';                                   /*初始字符为'Z'*/
		pbegin=1;                                  /*改变初始化标志*/
		pdx[0]=1,pdx[1]=0,pdx[2]=-1,pdx[3]=0;      /*定义数组变量*/
		pdy[0]=0,pdy[1]=1,pdy[2]=0,pdy[3]=-1;      /*定义数组变量*/
	}
	put_color_char(pch,px,py,pcolor);              /*显示字符，更新颜色和位置*/
	pcolor=(pcolor+1)%15+1;                        /*更新颜色*/
	px+=pdx[pdir];                                 /*更新纵坐标方向*/
	py+=pdy[pdir];                                 /*更新横坐标方向*/
	if(pdir==1||pdir==3)                           /*如果在上方或下方，就再显示一个字符，并更新位置*/
	{	
		if(py>0&&py<79)
		{
			put_color_char(pch,px,py,pcolor);
			px+=pdx[pdir];
			py+=pdy[pdir];	
		}
	}
	if(px==py&&px==0) pch--;                       /*在左上角顶点变更字符*/
	if(pch=='A'-1) pch='Z';                          /*当字符到达'A'的时候，变回'Z'*/
	
	if(px==24&&py==0||
		px==24&&py==79||
		px==0&&py==79||
		px==0&&py==0) pdir=(pdir+1)%4;             /*在四个角的顶点出变更方向*/
}


void cmain()
{
	cls();
	int33h();
	int34h();
	int35h();
	int36h();
	Load_Int21();
	Initial();
	setClock();
	while(1)
	{
		print("\n Orz >");
		GetInput();
		init_Pro();
		if( check( Buffer,"time" ) )
		{
			show_Time();
			PrintTime();
		}
		else if( check( Buffer,"date" ) )
		{
			show_Date();
			PrintDate();
		}
		else if( check( Buffer,"cls") )
		{
			cls();
			Initial();
		}
		else if( check( Buffer,"ascii") )
			CheckASCII();
		else if( check( Buffer,"pro" ) )
		{
			Print(" Key in the program you want to excute(1-5, 5 is a test for interupt): ");
		    GetInput();
			cls();
			Random_Load();
			Delay();
			cls();
			Initial();
		}
		else if( check ( Buffer,"help" ) )
			PrintIns();
		else if( Buffer[0] == '\0' )
			continue;
		else if( check(Buffer,"int21") )
		{
			Call_Int21();
			cls();
			Initial();
		}
		else if( check( Buffer,"test" ) )
		{
			cls();
			load_test();
			Delay();
			cls();
			Initial();
		}
		else
		{
			Print("\n Invalid Instruction!\r\n");
			Print(" You can key in \"help\" to check the specific command!\r\n");
		}
	}
}




void GetInput()
{
	index = 0;
	getChar();
	printChar(input);
	while( input != '\n'&& input != '\r' )
	{
		if(input=='\b'){
			if(index>0){
				index--;
				printChar(' ');
				printChar(input);
			}
			getChar();
			if(input=='\b'){
				if(index>0) printChar(input);
			}
			else
			printChar(input);
		}
		else{
			Buffer[index] = input;
			index ++;
			getChar();
			printChar(input);
		}
	}
	Buffer[index] = '\0';
	Print("\n");
	StringLen = index;
}

void GetInput2()
{
	index = 0;
	getChar();
	printChar(input);
	while( input != '\n'&& input != '\r' )
	{
		if(input=='\b'){
			if(index>0){
				index--;
				printChar(' ');
				printChar(input);
			}
			getChar();
			if(input=='\b'){
				if(index>0) printChar(input);
			}
			else
			printChar(input);
		}
		else{
			TempBuffer[index] = input;
			index ++;
			getChar();
			printChar(input);
		}
	}
	TempBuffer[index] = '\0';
	Print("\n");
	StringLen2 = index;
}

void Print( char* word )
{
	while( *word != '\0' )
	{
		printChar( *word );
		word ++ ;
	}
}



int check( char *word,char* goal )
{
	while(*word != '\0' && *goal != '\0')
	{
		if( *word != *goal )
			return 0;
		else
		{
			word ++;
			goal ++;
		}
	}
	if( *word == '\0' && *goal == '\0' )
		return 1;
	return 0;
}


int BCDdecode(int n) {
    return n / 16 * 10 + n % 16;
}

void Transfor( int num )
{
	if(num>99){
		Buffer[0] = num/100 + '0';
		Buffer[1] = (num/10)%10 + '0';
		Buffer[2] = num%10 + '0';
		Buffer[3] = '\0';
	}
	else{
		Buffer[0] = num/10 + '0';
		Buffer[1] = num%10 + '0';
		Buffer[2] = '\0';
	}
}

void PrintTime()
{
	hour1 = hour;
	minute1 = minute;
	second1 = second;

	Print("\nTime: ");
	Transfor( BCDdecode(hour1) );
	Print(Buffer);
	Print(":");

	Transfor( BCDdecode(minute1) );
	Print(Buffer);
	Print(":");

	Transfor( BCDdecode(second1) );
	Print(Buffer);
	print("\r\n");
}

void PrintDate()
{
	century1 = century;
	year1 = year;
	month1 = month;
	day1 = day;

	Print("\nDate: ");
	Transfor(BCDdecode(century1));
	Print(Buffer);

	Transfor( BCDdecode(year1) );
	Print(Buffer);
	Print("/");

	Transfor(BCDdecode(month1));
	Print(Buffer);
	Print("/");

	Transfor(BCDdecode(day1));
	Print(Buffer);
	print("\r\n");
}

void Initial()
{
	Print("                         \n\n  Welcome to use MyOS ! \r\n\n");
	Print("                 Please key in commands to execute functions! \r\n\n"); 
	Print("           Key in \"help\" to know what functions are available in MyOS!\r\n");
}

void CheckASCII()
{
	Print("\r\n Key in the character you want to check for ASCII Number:");
	getChar();
	printChar(input);
	ASCII_Num = input;
	Transfor( ASCII_Num );
	Print("\r\n The ASCII Number of ");
	PrintChar(input);
	Print(" is ");
	Print(Buffer);
	Print(".\r\n");
}


void RunProgram()
{
	int i = 0;
	int j = 0;
	bl = 0;
	Print(" Key in the number of program(1-3) you want to excute in any order,and you can\r\n");
	Print(" run any amount of programs (like 123 or 2313... ) :");
	GetInput();

	while( Buffer[i] != '\0' )
	{
		if( Buffer[i] == ' ' )
		{
			i++;
			continue;
		}
		else if( Buffer[i] < '1' || Buffer[i] > '3' )
		{
			bl = 1;
			return;
		}
		else
			i++;
	}

	while( Buffer[j] != '\0' )
	{
		if( Buffer[j] == ' ' )
		{
			j++;
			continue;
		}
		if( Buffer[j] >= '1' && Buffer[j] <='3' )
		{
			Pro = Buffer[j] -'0' + 4;
			Run();
			j++;
		}
	}
	return;
}

void PrintIns()
{
	Print(" time         - Print the System Time.\r\n");
	Print(" date         - Print the System Date.\r\n");
	Print(" ascii        - Query the ASCII Number of a character.\r\n");
	Print(" cls          - Clear the screen.\r\n");
	Print(" pro          - Creat Process and excute Process.\r\n");
	Print(" int21        - Call Interupt 21h!\r\n");
	Print(" test         - Call the test Process and test\r\n");
}

void Print_Int( int n )
{
	int temp = n;
	int mod = 0;
	int i = 0;
	int j;
	while( temp > 0 )
	{
		mod = temp % 10;
		temp /= 10;
		TempBuffer[i] = mod + '0';
		i++;
	}
	j = i-1;
	for( ;j>=0;j-- )
		printChar( TempBuffer[j] );
}

void Bin_to_Dec( char* word )
{
	int i = 0;
	int num = 0;
	while( word[i] != '\0' )
	{
		num *= 2;
		num += word[i] - '0';
		i++;
	}
	if( num == 0 )
		Print("0");
	Print_Int( num );
}

char String_to_Int( char* word )
{
	int i = 0;
	char temp = 0;
	while( word[i] != '\0' )
	{
		temp *=10;
		temp += word[i] - '0';
		i++;
	}
	return temp;
}
int String_to_Int2( char* word )
{
	int i = 0;
	int temp = 0;
	while( word[i] != '\0' )
	{
		temp *=10;
		temp += word[i] - '0';
		i++;
	}
	return temp;
}
void start()
{
	cls();
	Print("\r\n                       Welcome To Use Interupt 21h ! ");
	Print("\r\n\n Functions list of the Interupt 21h : ");
	Print("\r\n Function Number            Function Instruction    ");
	Print("\r\n    0              - Print\"OUCH!OUCH!\" in the center of screen");
	Print("\r\n    1              - Transform lower case letters in a string into upper case                        leters");
	Print("\r\n    2              - Transform upper case letters in a string into lower case                        leters");
	Print("\r\n    3              - Transform a string into a number ");
	Print("\r\n    4              - Transform a number into a string ");
	Print("\r\n    5              - Show a string in any position you want ");
	Print("\r\n    6              - Transform Binary number into Decimal number");
	Print("\r\n    7              - Show a color string in any position you want ");
	Print("\r\n    8              - Judging whether two strings are equal ");
	Print("\r\n    q              - Quit the Interupt 21h\r\n\n ");
}
void Call_Int21()
{
	ColorOfOuch=1;
	start();
	while(1)
	{
		Print(" Key in the Function Number : ");
			getChar();
			printChar(input);
			if( input == '0' )
			{
				cls();
				start();
				Show_Orch();
				ColorOfOuch++;
				if(ColorOfOuch==16) ColorOfOuch=1;
			}
			else if( input == '1' )
			{
				Print("\r\n Key in the String : ");
				GetInput();
				if( StringLen == 0 )
				{
					cls();
				        start();
					continue;
				}
				Fun_Upper(Buffer);
				cls();
				start();
				Print(" The upper string is : ");
				Print(Buffer);
				Print("\r\n\n");
			}
			else if ( input == '2' )
			{
				Print("\r\n Key in the String : ");
				GetInput();
				if( StringLen == 0 )
				{
					cls();
				        start();
					continue;
				}
				Fun_Lower(Buffer);
				cls();
				start();
				Print(" The lower string is : ");
				Print(Buffer);
				Print("\r\n\n");
			}
			else if ( input == '3' )
			{
				Print("\r\n Key in the String ( 0 - 32767 ) : ");
				GetInput();
				if( StringLen == 0 )
				{
					cls();
				        start();
					continue;
				}
				if( If_NumString( Buffer ) == 0 )
				{
					cls();
					start();
					Print(" Invalid Input ! \r\n\n");
					continue;
				}
				Num = String_to_Num(Buffer);
				cls();
				start();
				Print(" The number you key in is : ");
			        Print_Int( Num );
				Print("\r\n\n");
			}
			else if ( input == '4' )
			{
				Print("\r\n Key in the Number ( 0 - 32767 ) : ");
				GetInput();
				if( StringLen == 0 )
				{
					cls();
				        start();
					continue;
				}
				if( If_NumString( Buffer ) == 0 )
				{
					cls();
					start();
					Print(" Invalid Input ! \r\n\n");
					continue;
				}
				cls();
				start();
				Print(" The number you key in is : ");
				Num = String_to_Int2(Buffer);
				Num_to_String(Num);
				Print("\r\n\n");
			}
			else if ( input == '5' )
			{
				Print("\r\n Key in the row number(0-24) you want the string to show: ");
				GetInput();
				row = String_to_Int(Buffer);
				Print(" Key in the column number(0-79) you want the string to show: ");
				GetInput();
				col = String_to_Int(Buffer);
				Print(" Key in the String : ");
				GetInput();
				if( StringLen == 0 )
				{
					cls();
				        start();
					continue;
				}
				cls();
				start();
				Print_String( Buffer,row,col );
				Print("\r\n");
			}
			else if ( input == '6' )
			{
				Print("\r\n Key in the String : ");
				GetInput();
				if( StringLen == 0 )
				{
					cls();
				        start();
					continue;
				}
				if( If_Binary( Buffer ) == 0 )
				{
					cls();
				        start();
					Print(" Invalid Input ! !\r\n\n");
					continue;
				}
				cls();
				start();
				Print(" The Decimal Number of the Binary you key in is : ");
			        Binary_to_Decimal(Buffer);
				Print("\r\n\n");
			}
			else if ( input == '7' )
			{
				Print("\r\n Key in the row number(0-24) you want the color string to show: ");
				GetInput();
				row = String_to_Int(Buffer);
				Print(" Key in the column number(0-79) you want the color string to show: ");
				GetInput();
				col = String_to_Int(Buffer);
				Print(" Key in the String : ");
				GetInput();
				if( StringLen == 0 )
				{
					cls();
				        start();
					continue;
				}
				cls();
				start();
				Print_Color_String( Buffer,row,col );
				Print("\r\n");
			}
			else if ( input == '8' )
			{
				Print("\r\n Key in the String A : ");
				GetInput();
				if( StringLen == 0 )
				{
					cls();
				        start();
					Print(" Not Empty String!  \r\n\n");
					continue;
				}
				Print(" Key in thr String B : ");
				GetInput2();
				if( StringLen2 == 0 )
				{
					cls();
				        start();
					Print(" Not Empty String!  \r\n\n");
					continue;
				}
				cls();
				start();
				if( If_Equal(Buffer,TempBuffer)==0 )
					Print(" Two strings are not Equal!\r\n\n");
				if( If_Equal(Buffer,TempBuffer)==1 )
					Print(" Two strings are Equal!\r\n\n");
			}
			else if ( input == 'q' )
				break;
			else
			{
				cls();
				start();
				Print("\r\n Invalid Input!\r\n");
			}
	}
}

int If_NumString( char* word )
{
	int i = 0;
	while( word[i] != '\0' )
	{
		if( word[i] <'0' || word[i] >'9' )
			return 0;
		i++;
	}
	return 1;
}

int If_Binary( char* word )
{
	int i = 0;
	while( word[i] != '\0' )
	{
		if( word[i] != '0' && word[i] != '1' )
			return 0;
		i++;
	}
	return 1;
}

void Random_Load()
{
	int i = 0;
	int j = 0;
	for( i=0; i<StringLen;i++ )
		if( Buffer[i]!=' ' && (Buffer[i]<'1' || Buffer[i]>'6') )
		{
			Print("Error Input!");
			Delay2();
			return;
		}
	for( i=0; i<StringLen;i++ )
	{
		if( Buffer[i] ==' ' )
			continue;
		else
		{
			j = Buffer[i] - '0';
			if( Segment > 0x6000 )
			{
				Print(" There have been 5 Processes !");
				break;
			}
			another_load(Segment,2*j+4);
			Segment += 0x1000;
			Program_Num ++;
		}
	}
}

void load_test()
{
	Program_Num ++;
	another_load(Segment,16);
	Segment += 0x1000;
}

void init_Pro()
{
	init(&pcb_list[0],0x1000,0x100,0);
	init(&pcb_list[1],0x2000,0x100,1);
	init(&pcb_list[2],0x3000,0x100,2);
	init(&pcb_list[3],0x4000,0x100,3);
	init(&pcb_list[4],0x5000,0x100,4);
	init(&pcb_list[5],0x6000,0x100,5);
	init(&pcb_list[6],0x7000,0x100,6);
}

void Delay()
{
	int i = 0;
	int j = 0;
	for( i=0;i<30000;i++ )
		for( j=0;j<3000;j++ )
		{
			j++;
			j--;
		}
}

void Delay2()
{
	int i = 0;
	int j = 0;
	for( i=0;i<15000;i++ )
		for( j=0;j<30000;j++ )
		{
			j++;
			j--;
		}
}
