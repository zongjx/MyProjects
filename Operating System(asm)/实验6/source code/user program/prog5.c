extern void printChar();
extern int fork();
extern int wait();
extern int exit(int);
void dmain();
void Delay();


char str[80]="wrq32423r32rerq3rq23r23rwqr3r2r23r23r3r3r3qr32";
int LetterNr=0;
int CountLetter(char *str);
void Print( char* word )
{
	while( *word != '\0' )
	{
		printChar( *word );
		word ++ ;
	}
}
void PrintNum(int num){
	char s[20];
	int cnt=0;
	do{
		s[cnt]=num%10+48;
		num/=10;
		cnt++;
	}while (num>0);
	s[cnt]=0;
	while (cnt--){
		printChar(s[cnt]);
	}
}
void dmain() {
   int pid;
   int ch;
   pid=fork();
   if (pid==-1) {Print("error in fork!");exit(-1);}
   if (pid)  {	
   Print("LetterNr=?        ");
   ch=wait();
   Print("LetterNr=");
   PrintNum(LetterNr);
} 
else {
   LetterNr =CountLetter(str);
   Print("Counting......                                                ");
   exit(0);
    }
   Print("  Program finished");
}

int CountLetter(char *str){
	int cnt=0;
	while (*str!=0){
		cnt++;
		str++;
	}
	return cnt;
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
