#include <iostream>
#include <string>
#include <string.h>
#include <cstdlib>
#include <ctime>
using namespace std;


//**************************************************************************** class digits
class digits
{
	public:
		digits();                                                          //constructor of four digits
		digits(int digits);                                                //constructor of four digits
		~digits();                                                         //distructor of four digits
		void display();                                                    //display the digits
		void setDigits(int);                                               //set digits 
		bool checkFormat(string);                                          //check the format of the digits
		bool checkFormat(int);                                             //check the format of the digits
		int getDig0();                                                     //return the first number of the digits
		int getDig1();                                                     //return the first number of the digits
		int getDig2();                                                     //return the first number of the digits
		int getDig3();                                                     //return the first number of the digits
		void compare(digits);                                              //computer function
		int getValueOnly();                                                //return the number of right value but wrong position
		int getValueAndPosition();                                         //return the number of right value and right position
		void set_getValueOnly();                                           //set the number of right but wrong position value to 0
		void set_getValueAndPosition();                                    //set the number of right value and right position to 0
		digits& operator=(digits&);                                        //reload function
	private:
		int dig[4];                                                        //storge every bits of the digits
		int valueOnly;                                                     //storge the number of A
		int valueAndPosition;                                              //storge the number of B
};
//**************************************************************************** class digits

digits::digits()
{
	int seed;
	seed=time(NULL);
	srand(seed);
	dig[0]=rand()%10;
	dig[1]=rand()%10;
	while(dig[1]==dig[0])
	dig[1]=rand()%10;
	dig[2]=rand()%10;
	while(dig[2]==dig[0]||dig[2]==dig[1])
	dig[2]=rand()%10;
	dig[3]=rand()%10;
	while(dig[3]==dig[0]||dig[3]==dig[1]||dig[3]==dig[2])
	dig[3]=rand()%10;
	valueOnly=0;
    valueAndPosition=0;
}

digits::digits(int digits)
{
	dig[3]=digits%10;
	dig[2]=(digits/10)%10;
	dig[1]=(digits/100)%10;
	dig[0]=(digits/1000)%10;
	valueOnly=0;
    valueAndPosition=0;
}

digits::~digits()
{
	
}

void digits::display()
{
	cout<<dig[0]<<dig[1]<<dig[2]<<dig[3]<<" ";
}

bool digits::checkFormat(string in)
{
	if(in.length()!=4)
	return false;
	else
	{
		int d0,d1,d2,d3;
		d3=in[3]+'0'-96;
		d2=in[2]+'0'-96;
		d1=in[1]+'0'-96;
		d0=in[0]+'0'-96;
		if(d0==d1||d0==d2||d0==d3||d1==d2||d1==d3||d2==d3)
		return false;
		else
		return true;
	}
}

bool digits::checkFormat(int d)
{
	if(9999-d<=0)
	return false;
	else
	{
		int d0,d1,d2,d3;
		d3=d%10;
		d2=(d/10)%10;
		d1=(d/100)%10;
		d0=(d/1000)%10;
		if(d0==d1||d0==d2||d0==d3||d1==d2||d1==d3||d2==d3)
		return false;
		else
		return true;
	}
}

void digits::setDigits(int digits)
{
	dig[3]=digits%10;
	dig[2]=(digits/10)%10;
	dig[1]=(digits/100)%10;
	dig[0]=(digits/1000)%10;
}

int digits::getDig0()
{
	return dig[0];
}

int digits::getDig1()
{
	return dig[1];
}
int digits::getDig2()
{
	return dig[2];
}

int digits::getDig3()
{
	return dig[3];
}

void digits::compare(digits otherdigits)
{
	if(dig[0]==otherdigits.getDig0())
	valueAndPosition++;
	else if(dig[0]==otherdigits.getDig1()||dig[0]==otherdigits.getDig2()||dig[0]==otherdigits.getDig3())
	valueOnly++;
	if(dig[1]==otherdigits.getDig1())
	valueAndPosition++;
	else if(dig[1]==otherdigits.getDig0()||dig[1]==otherdigits.getDig2()||dig[1]==otherdigits.getDig3())
	valueOnly++;
	if(dig[2]==otherdigits.getDig2())
	valueAndPosition++;
	else if(dig[2]==otherdigits.getDig0()||dig[2]==otherdigits.getDig1()||dig[2]==otherdigits.getDig3())
	valueOnly++;
	if(dig[3]==otherdigits.getDig3())
	valueAndPosition++;
	else if(dig[3]==otherdigits.getDig0()||dig[3]==otherdigits.getDig1()||dig[3]==otherdigits.getDig2())
	valueOnly++;
}

int digits::getValueOnly()
{
	return valueOnly;
}

int digits::getValueAndPosition()
{
	return valueAndPosition;
}

void digits::set_getValueOnly()
{
	valueOnly=0;
}

void digits::set_getValueAndPosition()
{
	valueAndPosition=0;
}

digits& digits::operator=(digits& d)
{
	dig[0]=d.getDig0();
	dig[1]=d.getDig1();
	dig[2]=d.getDig2();
	dig[3]=d.getDig3();
	valueOnly=d.getValueOnly();
    valueAndPosition=d.getValueAndPosition();
	return *this;
}


//**************************************************************************** class player
class player                                                              //base class
{
	public:
		player();                                                         //constructor of player
		player(string&);                                                  //constructor of player
	    ~player();                                                        //distructor of player
	    void inputDigits(digits&);                                        //input digits;
	    string getName();                                                 //return name
	private:
		string name;                                                      //storge the name of the player
		digits inputDigits_;                                              //storge the number which player inputed
};
//**************************************************************************** class player

player::player()
{
	name="player";
}

player::player(string& name_)
{
	name=name_;
}

player::~player()
{
	
}

void player::inputDigits(digits& d)
{
	inputDigits_=d;
}

string player::getName()
{
	return name;
}


//**************************************************************************** class playerHuman
class playerHuman:public player                                           //derived class
{
	public:
		playerHuman(string&);                                             //constructor of playerHuman
	    ~playerHuman();                                                   //distructor of playerHuman
};
//**************************************************************************** class playerHuman

playerHuman::playerHuman(string& s):player(s)
{
	
}

playerHuman::~playerHuman()
{
	
}


//**************************************************************************** class playerComputer
class playerComputer:public player                                        //devired class
{
	public:
		playerComputer();                                                 //constructor of playerComputer
		playerComputer(string& s);                                        //constructor of playerComputer
	    ~playerComputer();                                                //distructor of playerComputer
	    int inputDigits_AI();                                             //AI input digits
	    void getInformation(int digits,int Anumber,int Bnumber);          //analise and get information
	    void getInformation_(int digits);                                 //analise and get information
		int getCount();                                                   //return count
	    int getCount2();                                                  //return count2
	    int getWrong();                                                   //return wrong
	    int getUnorderd();                                                //return unorder
	    void set3ADigits(int n);                                          //set the digits which is 3A 
	    void setCount2();                                                 //count2 +1
	    void setCount();                                                  //count +1
	    void setWrong();                                                  //wrong +1
	    void setUnorderd();                                               //unorderd +1
	    int trans(int a,int b,int c,int d);                               //transform the numbers to digits
	private:
		int wrongDig[10];                                                 //storge the wrong single digits 
		int wrongCount;                                                   //storge the number of the wrong digits
		int ABDigits;                                                     //storge the digits which A+B=4
		int ADigits;                                                      //storge the number which is 3A
		int dmark;                                                        //a mark that used to analyse the imformation
		int count;                                                        //storge the number of wrong digits
		int count2;                                                       //storge the number of the possible digits
		int unorderd;                                                     //storge the number of nuordered digits which is A+B=4
		int nearDig[100];                                                 //storge the possible digits
		int unorderdDigits[25];                                           //storge the nuordered digits which is A+B=4
		int dig_al[100000];                                               //storge the wrong digits
		int dig[4];                                                       //storge the input digits
		int tempDig[4];                                                   //a temporary memory to storge digits
		int sDig[4];                                                      //storge the four true number which are belong to the answer
};
//**************************************************************************** class playerComputer

playerComputer::playerComputer():player()
{
	count=0;
	dmark=0;
	count2=0;
	wrongCount=0;
	ABDigits=0;
} 

playerComputer::playerComputer(string& s):player(s)
{
	count=0;
	dmark=0;
	count2=0;
	wrongCount=0;
	ABDigits=0;
}

playerComputer::~playerComputer()
{
	
}

int playerComputer::getWrong()
{
	return wrongCount;
}

int playerComputer::getUnorderd()
{
	return unorderd;
}

void playerComputer::setUnorderd()
{
	unorderd++;
}

int playerComputer::getCount2()
{
	return count2;
}

void playerComputer::setCount2()
{
	count2++;
}

void playerComputer::setWrong()
{
	wrongCount++;
}

void playerComputer::set3ADigits(int n)
{
	ADigits=n;
}

int playerComputer::inputDigits_AI()
{
	int seed,num=0;
	seed=time(0);
	srand(seed);
	bool check=0;
	if(ABDigits!=0)
	{
		while(check==0)
		{
			check=1;
			num=unorderdDigits[rand()%getUnorderd()];
	    	if(num==0)
	    	check=0;
			for(int i=0;i<getCount();i++)
			{
				if(num==dig_al[i])
				check=0;
			}
		}
	}
	else
	{
		if(dmark==0)
		{
		    while(check==0)
	    	{
				check=1;
				int markw=1;
				dig[0]=rand()%10;
			   	for(int i=0;i<getWrong();i++)
			    {
			   		if(dig[0]==wrongDig[i])
			   		markw=0;
			   	}
				while(markw==0)
				{
					markw=1;
					dig[0]=rand()%10;
					for(int i=0;i<getWrong();i++)
				    {
			    		if(dig[0]==wrongDig[i])
			    		{
			    			markw=0;
			    			break;
						}
			    	}
				}
				dig[1]=rand()%10;
				for(int i=0;i<getWrong();i++)
			    {
			   		if(dig[1]==wrongDig[i])
			   		markw=0;
			   	}
				while(markw==0)
				{
					markw=1;
					dig[1]=rand()%10;
					for(int i=0;i<getWrong();i++)
				    {
			    		if(dig[1]==wrongDig[i])
			    		{
			    			markw=0;
			    			break;
						}
			    	}
				}
				while(dig[1]==dig[0])
				{
		    		dig[1]=rand()%10;
					for(int i=0;i<getWrong();i++)
				    {
				   		if(dig[1]==wrongDig[i])
				   		markw=0;
				   	}
					while(markw==0)
					{
						markw=1;
						dig[1]=rand()%10;
						for(int i=0;i<getWrong();i++)
					    {
				    		if(dig[1]==wrongDig[i])
				    		{
				    			markw=0;
				    			break;
							}
				    	}
					}
				} 
				dig[2]=rand()%10;
				for(int i=0;i<getWrong();i++)
			    {
			   		if(dig[2]==wrongDig[i])
			   		markw=0;
			   	}
				while(markw==0)
				{
					markw=1;
					dig[2]=rand()%10;
					for(int i=0;i<getWrong();i++)
				    {
			    		if(dig[2]==wrongDig[i])
			    		{
			    			markw=0;
			    			break;
						}
			    	}
				}
				while(dig[2]==dig[0]||dig[2]==dig[1])
				{
			    	dig[2]=rand()%10;
					for(int i=0;i<getWrong();i++)
				    {
				   		if(dig[2]==wrongDig[i])
				   		markw=0;
				   	}
					while(markw==0)
					{
						markw=1;
						dig[2]=rand()%10;
						for(int i=0;i<getWrong();i++)
					    {
				    		if(dig[2]==wrongDig[i])
				    		{
				    			markw=0;
				    			break;
							}
				    	}
					}
				}
				dig[3]=rand()%10;
				for(int i=0;i<getWrong();i++)
			    {
			   		if(dig[3]==wrongDig[i])
			   		markw=0;
			   	}
				while(markw==0)
				{
					markw=1;
					dig[3]=rand()%10;
					for(int i=0;i<getWrong();i++)
				    {
			    		if(dig[3]==wrongDig[i])
			    		{
			    			markw=0;
			    			break;
						}
			    	}
				}
				while(dig[3]==dig[0]||dig[3]==dig[1]||dig[3]==dig[2])
				{
					dig[3]=rand()%10;
					for(int i=0;i<getWrong();i++)
				    {
				   		if(dig[3]==wrongDig[i])
				   		markw=0;
				   	}
					while(markw==0)
					{
						markw=1;
						dig[3]=rand()%10;
						for(int i=0;i<getWrong();i++)
					    {
				    		if(dig[3]==wrongDig[i])
				    		{
				    			markw=0;
				    			break;
							}
				    	}
					}
				}
				num=dig[0]*1000+dig[1]*100+dig[2]*10+dig[3];
				for(int i=0;i<getCount();i++)
				{
					if(num==dig_al[i])
					{
						check=0;
					}
				}
	    	}
		}
		else if(dmark==1||dmark==2)
		{
			while(check==0)
	    	{
				check=1;
				num=nearDig[rand()%getCount2()];
				for(int i=0;i<getCount();i++)
				{
					if(num==dig_al[i])
					check=0;
				}
				if(num==0)
			    check=0;
				int d0,d2,d3,d1;
				d3=num%10;
				d2=(num/10)%10;
				d1=(num/100)%10;
				d0=(num/1000)%10;
				if(d0==d1||d0==d2||d0==d3||d1==d2||d1==d3||d2==d3)
				{
					for(int i=0;i<getCount2();i++)
					{
						if(num==nearDig[i])
						{
							nearDig[i]=0;
							break;
						}
					}
					check=0;
				}
	    	}
		}
		else if(dmark==3)
		{
			num=0;
			while(check==0)
			{
				int markw=1;
				num=0;
				check=1;
				if(sDig[0]==99)
				{
					int k=rand()%10;
					for(int i=0;i<getWrong();i++)
				    {
				   		if(k==wrongDig[i])
				   		markw=0;
				   	}
					while(markw==0)
					{
						markw=1;
						k=rand()%10;
						for(int i=0;i<getWrong();i++)
					    {
				    		if(k==wrongDig[i])
				    		{
				    			markw=0;
				    			break;
							}
				    	}
					}
					while(k==sDig[1]||k==sDig[2]||k==sDig[3])
					{
						k=rand()%10;
						for(int i=0;i<getWrong();i++)
				        {
					   		if(k==wrongDig[i])
					   		markw=0;
					   	}
						while(markw==0)
						{
							markw=1;
							k=rand()%10;
							for(int i=0;i<getWrong();i++)
						    {
					    		if(k==wrongDig[i])
					    		{
					    			markw=0;
					    			break;
								}
					    	}
						}
					}
					num+=k*1000+sDig[1]*100+sDig[2]*10+sDig[3];
				}
				else if(sDig[1]==99)
				{
					int k=rand()%10;
					for(int i=0;i<getWrong();i++)
				    {
				   		if(k==wrongDig[i])
				   		markw=0;
				   	}
					while(markw==0)
					{
						markw=1;
						k=rand()%10;
						for(int i=0;i<getWrong();i++)
					    {
				    		if(k==wrongDig[i])
				    		{
				    			markw=0;
				    			break;
							}
				    	}
					}
					while(k==sDig[0]||k==sDig[2]||k==sDig[3])
					{
						for(int i=0;i<getWrong();i++)
					    {
					   		if(k==wrongDig[i])
					   		markw=0;
					   	}
						while(markw==0)
						{
							markw=1;
							k=rand()%10;
							for(int i=0;i<getWrong();i++)
						    {
					    		if(k==wrongDig[i])
					    		{
					    			markw=0;
					    			break;
								}
					    	}
						}
					}
					num+=k*100+sDig[0]*1000+sDig[2]*10+sDig[3];
				}
				else if(sDig[2]==99)
				{
					int k=rand()%10;
					for(int i=0;i<getWrong();i++)
				    {
				   		if(k==wrongDig[i])
				   		markw=0;
				   	}
					while(markw==0)
					{
						markw=1;
						k=rand()%10;
						for(int i=0;i<getWrong();i++)
					    {
				    		if(k==wrongDig[i])
				    		{
				    			markw=0;
				    			break;
							}
				    	}
					}
					while(k==sDig[1]||k==sDig[0]||k==sDig[3])
					{
						for(int i=0;i<getWrong();i++)
					    {
					   		if(k==wrongDig[i])
					   		markw=0;
					   	}
						while(markw==0)
						{
							markw=1;
							k=rand()%10;
							for(int i=0;i<getWrong();i++)
						    {
					    		if(k==wrongDig[i])
					    		{
					    			markw=0;
					    			break;
								}
					    	}
						}
					}
					num+=k*10+sDig[1]*100+sDig[0]*1000+sDig[3];
				}
				else if(sDig[3]==99)
				{
					int k=rand()%10;
					for(int i=0;i<getWrong();i++)
				    {
				   		if(k==wrongDig[i])
				   		markw=0;
				   	}
					while(markw==0)
					{
						markw=1;
						k=rand()%10;
						for(int i=0;i<getWrong();i++)
					    {
				    		if(k==wrongDig[i])
				    		{
				    			markw=0;
				    			break;
							}
				    	}
					}
					while(k==sDig[1]||k==sDig[2]||k==sDig[0])
					{
						for(int i=0;i<getWrong();i++)
					    {
					   		if(k==wrongDig[i])
					   		markw=0;
					   	}
						while(markw==0)
						{
							markw=1;
							k=rand()%10;
							for(int i=0;i<getWrong();i++)
						    {
					    		if(k==wrongDig[i])
					    		{
					    			markw=0;
					    			break;
								}
					    	}
						}
					}
					num+=k+sDig[1]*100+sDig[2]*10+sDig[0]*1000;
				}
				for(int i=0;i<getCount();i++)
				{
					if(num==dig_al[i])
					check=0;
				}
			}
		}
	}
	return num;
}

void playerComputer::getInformation_(int digits)
{
	bool check=0;
	int d=digits,temp;
	for(int i=0;i<getCount();i++)
	{
		if(d==dig_al[i])
		{
			check=1;
			break;
		}
	} 
	if(check==0)
	{
		dig_al[getCount()]=digits;
    	setCount();
	}
}



void playerComputer::getInformation(int digits,int Anumber,int Bnumber)
{
	bool check=0;
	int d=digits,temp;
	for(int i=0;i<getCount();i++)
	{
		if(d==dig_al[i])
		{
			check=1;
			break;
		}
	} 
	if(Anumber+Bnumber==0)
	{
		wrongDig[getWrong()]=d%10;
		setWrong();
		wrongDig[getWrong()]=(d/10)%10;
		setWrong();
		wrongDig[getWrong()]=(d/100)%10;
		setWrong();
		wrongDig[getWrong()]=(d/1000)%10;
		setWrong();
	}
	if(Anumber==3)
	check=0;
	if(Anumber+Bnumber==4)
	{
		if(ABDigits==0)
		{
			int d[4]; 
			ABDigits=digits;
			d[3]=digits%10;
			d[2]=(digits/10)%10;
			d[1]=(digits/100)%10;
			d[0]=(digits/1000)%10;
			for(int i=0;i<4;i++)
			{
				for(int j=0;j<4;j++)
				{
					for(int k=0;k<4;k++)
					{
						for(int l=0;l<4;l++)
						{
							if(i==j||i==k||i==l||j==k||j==l||k==l)
							{
								continue;
							}
							else
							{
								unorderdDigits[getUnorderd()]=trans(d[i],d[j],d[k],d[l]);
								setUnorderd();
							}
						}
					}
				}
			}
		}
		else
		{
			for(int i=0;i<getUnorderd();i++)
			{
				if(unorderdDigits[i]==digits)
				unorderdDigits[i]=0;
			}
		}
	} 
	if(check==0)
	{
		dig_al[getCount()]=digits;
		setCount();
		tempDig[3]=d%10;
		tempDig[2]=(d/10)%10;
		tempDig[1]=(d/100)%10;
		tempDig[0]=(d/1000)%10;
		if(Anumber==0)
		{
			for(int i=0;i<10;i++)
			{
				for(int j=0;j<10;j++)
				{
					for(int k=0;k<10;k++)
					{
						tempDig[1]=i;
						tempDig[2]=j;
						tempDig[3]=k;
						temp=trans(tempDig[0],tempDig[1],tempDig[2],tempDig[3]);
						dig_al[getCount()]=temp;
						setCount();
					}
				}
			}
	    	tempDig[1]=(d/100)%10;
			for(int i=0;i<10;i++)
			{
				for(int j=0;j<10;j++)
				{
					for(int k=0;k<10;k++)
					{
						tempDig[0]=i;
						tempDig[2]=j;
						tempDig[3]=k;
						temp=trans(tempDig[0],tempDig[1],tempDig[2],tempDig[3]);
						dig_al[getCount()]=temp;
						setCount();
					}
				}
			}
	    	tempDig[2]=(d/10)%10;
			for(int i=0;i<10;i++)
			{
				for(int j=0;j<10;j++)
				{
					for(int k=0;k<10;k++)
					{
						tempDig[0]=i;
						tempDig[1]=j;
						tempDig[3]=k;
						temp=trans(tempDig[0],tempDig[1],tempDig[2],tempDig[3]);
						dig_al[getCount()]=temp;
						setCount();
					}
				}
			}
			tempDig[3]=d%10;
			for(int i=0;i<10;i++)
			{
				for(int j=0;j<10;j++)
				{
					for(int k=0;k<10;k++)
					{
						tempDig[0]=i;
						tempDig[1]=j;
						tempDig[2]=k;
						temp=trans(tempDig[0],tempDig[1],tempDig[2],tempDig[3]);
						dig_al[getCount()]=temp;
						setCount();
					}
				}
			}
		}
		else if(Anumber==1)
		{
			for(int i=0;i<10;i++)
			{
				for(int j=0;j<10;j++)
				{
					tempDig[2]=i;
					tempDig[3]=j;
				    temp=trans(tempDig[0],tempDig[1],tempDig[2],tempDig[3]);
					dig_al[getCount()]=temp;
					setCount();
				}
			}
		    tempDig[2]=(d/10)%10;
		    tempDig[0]=(d/1000)%10;
			for(int i=0;i<10;i++)
			{
				for(int j=0;j<10;j++)
				{
					tempDig[1]=i;
					tempDig[3]=j;
				    temp=trans(tempDig[0],tempDig[1],tempDig[2],tempDig[3]);
					dig_al[getCount()]=temp;
					setCount();
				}
			}
			tempDig[3]=d%10;
		    tempDig[0]=(d/1000)%10;
			for(int i=0;i<10;i++)
			{
				for(int j=0;j<10;j++)
				{
					tempDig[1]=i;
					tempDig[2]=j;
				    temp=trans(tempDig[0],tempDig[1],tempDig[2],tempDig[3]);
					dig_al[getCount()]=temp;
					setCount();
				}
			}
			tempDig[3]=d%10;
	    	tempDig[1]=(d/100)%10;
			for(int i=0;i<10;i++)
			{
				for(int j=0;j<10;j++)
				{
					tempDig[0]=i;
					tempDig[2]=j;
				    temp=trans(tempDig[0],tempDig[1],tempDig[2],tempDig[3]);
					dig_al[getCount()]=temp;
					setCount();
				}
			}
			tempDig[3]=d%10;
	    	tempDig[2]=(d/10)%10;
			for(int i=0;i<10;i++)
			{
				for(int j=0;j<10;j++)
				{
					tempDig[0]=i;
					tempDig[1]=j;
				    temp=trans(tempDig[0],tempDig[1],tempDig[2],tempDig[3]);
					dig_al[getCount()]=temp;
					setCount();
				}
			}
		}
		else if(Anumber==2)
		{
			if(dmark==0)
			{
				for(int i=0;i<10;i++)
				{
					tempDig[0]=i;
					temp=trans(tempDig[0],tempDig[1],tempDig[2],tempDig[3]);
				    dig_al[getCount()]=temp;
					setCount();
				}
				tempDig[3]=d%10;
		    	tempDig[2]=(d/10)%10;
		    	tempDig[0]=(d/1000)%10;
				for(int i=0;i<10;i++)
				{
					tempDig[1]=i;
					temp=trans(tempDig[0],tempDig[1],tempDig[2],tempDig[3]);
				    dig_al[getCount()]=temp;
					setCount();
				}
				tempDig[3]=d%10;
		    	tempDig[1]=(d/100)%10;
		    	tempDig[0]=(d/1000)%10;
				for(int i=0;i<10;i++)
				{
					tempDig[2]=i;
					temp=trans(tempDig[0],tempDig[1],tempDig[2],tempDig[3]);
				    dig_al[getCount()]=temp;
					setCount();
				}
		    	tempDig[2]=(d/10)%10;
		    	tempDig[1]=(d/100)%10;
		    	tempDig[0]=(d/1000)%10;
				for(int i=0;i<10;i++)
				{
					tempDig[3]=i;
					temp=trans(tempDig[0],tempDig[1],tempDig[2],tempDig[3]);
				    dig_al[getCount()]=temp;
					setCount();
				}
			} 
			else if(dmark==1||dmark==2)
			{
				dmark=2;
				if(ADigits%10!=d%10)
				{
					for(int i=0;i<10;i++)
			    	{
			    		tempDig[3]=i;
			    		temp=trans(tempDig[0],tempDig[1],tempDig[2],tempDig[3]);
			    		for(int i=0;i<getCount2();i++)
			    		if(nearDig[i]==temp)
			    		nearDig[i]=0;
			    	}
				}
				else if((ADigits/10%10)!=(d/10)%10)
				{
					for(int i=0;i<10;i++)
			    	{
			    		tempDig[2]=i;
			    		temp=trans(tempDig[0],tempDig[1],tempDig[2],tempDig[3]);
			    		for(int i=0;i<getCount2();i++)
			    		if(nearDig[i]==temp)
			    		nearDig[i]=0;
			    	}
				}
				else if((ADigits/100)%10!=(d/100)%10)
				{
					for(int i=0;i<10;i++)
			    	{
			    		tempDig[1]=i;
			    		temp=trans(tempDig[0],tempDig[1],tempDig[2],tempDig[3]);
			    		for(int i=0;i<getCount2();i++)
			    		if(nearDig[i]==temp)
			    		nearDig[i]=0;
			    	}
				}
				else if((ADigits/1000)%10!=(d/1000)%10)
				{
					for(int i=0;i<10;i++)
			    	{
			    		tempDig[0]=i;
			    		temp=trans(tempDig[0],tempDig[1],tempDig[2],tempDig[3]);
			    		for(int i=0;i<getCount2();i++)
			    		if(nearDig[i]==temp)
			    		nearDig[i]=0;
			        }
				}
			}
		}
		else if(Anumber==3)
		{
			if(dmark==0)
			{
				dmark=1;
				set3ADigits(digits);
				for(int i=0;i<10;i++)
				{
					tempDig[0]=i;
					temp=trans(tempDig[0],tempDig[1],tempDig[2],tempDig[3]);
					nearDig[getCount2()]=temp;
					setCount2();
				}
				tempDig[0]=(digits/1000)%10;
				for(int i=0;i<10;i++)
				{
					tempDig[1]=i;
					temp=trans(tempDig[0],tempDig[1],tempDig[2],tempDig[3]);
					nearDig[getCount2()]=temp;
					setCount2();
				}
				tempDig[1]=(digits/100)%10;
				for(int i=0;i<10;i++)
				{
					tempDig[2]=i;
					temp=trans(tempDig[0],tempDig[1],tempDig[2],tempDig[3]);
					nearDig[getCount2()]=temp;
					setCount2();
				}
				tempDig[2]=(digits/10)%10;
				for(int i=0;i<10;i++)
				{
					tempDig[3]=i;
					temp=trans(tempDig[0],tempDig[1],tempDig[2],tempDig[3]);
					nearDig[getCount2()]=temp;
					setCount2();
				}
				tempDig[3]=digits%10;
			}
			else if(dmark==1||dmark==2)
			{
				dig_al[getCount()]=d;
				setCount();
				dmark=3;
				if(ADigits%10!=d%10)
				{
					sDig[0]=(d/1000)%10;
					sDig[1]=(d/100)%10;
					sDig[2]=(d/10)%10;
					sDig[3]=99;
				}
				else if((ADigits/10)%10!=(d/10)%10)
				{
					sDig[0]=(d/1000)%10;
					sDig[1]=(d/100)%10;
					sDig[3]=d%10;
					sDig[2]=99;
				}
				else if((ADigits/100)%10!=(d/100)%10)
				{
					sDig[0]=(d/1000)%10;
					sDig[3]=d%10;
					sDig[2]=(d/10)%10;
					sDig[1]=99;
				}
				else if((ADigits/1000)%10!=(d/1000)%10)
				{
					sDig[3]=d%10;
					sDig[1]=(d/100)%10;
					sDig[2]=(d/10)%10;
					sDig[0]=99;
				}
			}
		}
	}
}

int playerComputer::trans(int a,int b,int c,int d)
{
	return a*1000+b*100+c*10+d;
}

int playerComputer::getCount()
{
	return count;
}

void playerComputer::setCount()
{
	count++;
}


//**************************************************************************** class game 
class game
{
	public:
		game();                                                           //constructor of the game
		~game();                                                          //distructor of the game
		void gameCreate();                                                //create a game
		void gameMode_CH();                                               //Human vs Computer
		void gameMode_HH();                                               //Human vs Human
		void gameMode_CC();                                               //Computer vs Computer
		void gameMode_H();                                                //Single player(Human)
		digits getAnswer();                                               //return the digits which is the answer
		int chooseDifficulty; 
		int toInt(string);                                                //transform the string to int
	private:
		int round;                                                        //stroge the number of rounds
		string player1;                                                   //the name of player1
		string player2;                                                   //the name of player2
		string winner;                                                    //the name of the winner
		string loser;                                                     //the name of loser
		int step;                                                         //storge the step of the guess
		digits answer;                                                    //storge the answer of the digits
};
//**************************************************************************** class game 

game::game()
{
	round=0;
	player1="none";
	player2="none";
	winner="none";
	loser="none";
	chooseDifficulty=0;
	step=0;
	cout<<"***************************************************************************"<<endl<<"                        欢 迎 来 玩 猜 数 字 ！ ！ ！ !"<<endl<<"***************************************************************************"<<endl;
	cout<<endl<<endl<<endl;
}

game::~game()
{
	
}

int game::toInt(string s)
{
	int d1,d2,d3,d0;
  	d3=s[3]+'0'-96;
	d2=s[2]+'0'-96;
	d1=s[1]+'0'-96;
	d0=s[0]+'0'-96;
	return d0*1000+d1*100+d2*10+d3;
}

void game::gameCreate()
{
    char choose1='0';
	char choose2='Y';
	while(choose2=='Y'||choose2=='y')
	{
	    digits newdigits;
		answer=newdigits;
		round++;
		step=0;
		cout<<"                                   Round "<<round<<endl<<endl;
		cout<<"请选择游戏模式 : 输入 0 进行单人模式   输入 1 进行人人对战模式   输入 2 进行人机对战模式   输入 3 进行电脑与电脑的对战模式"<<endl; 
		cin>>choose1;
		while(choose1!='0'&&choose1!='1'&&choose1!='2'&&choose1!='3')
		{
			cout<<"输入有误！请重新输入！"<<endl;
			cout<<"请选择游戏模式 : 输入 0 进行单人模式   输入 1 进行人人对战模式   输入 2 进行人机对战模式   输入 3 进行电脑与电脑的对战模式"<<endl; 
	    	cin>>choose1;
		}
		if(choose1=='0')
		gameMode_H();
		else if(choose1=='1')
		gameMode_HH();
		else if(choose1=='2')
		gameMode_CH();
		else if(choose1=='3')
		gameMode_CC();
		cout<<"再来一盘？ （输入 Y 或 y 再来一盘 ， 输入 N 或 n 结束游戏）"<<endl;
		cin>>choose2;
		while(choose2!='Y'&&choose2!='y'&&choose2!='N'&&choose2!='n')
		{
			cout<<"输入有误！请重新输入！"<<endl;
			cout<<"再来一盘？ （输入 Y 或 y 再来一盘 ， 输入 N 或 n 结束游戏）"<<endl;
	    	cin>>choose2;
		}
	}
}

void game::gameMode_HH()
{
    cout<<endl<<endl;
	cout<<"                                               "<<"Step"<<"    Number     "<<"A and B"<<endl; 
	player1="player1";
	player2="player2";
	int correct=0;
	playerHuman p1(player1),p2(player2);
	digits p1d,p2d;
	string in;
	int p1_in,p2_in;
	while(correct!=4)
	{
		step++;
		cout<<"Player 1   Please enter your digits:";
		cin>>in;
		while(p1d.checkFormat(in)!=true)
		{
			cout<<"Digits illegal\nPlayer 1   Please enter your digits:";
			cin>>in;
		}
		p1_in=toInt(in);
		p1d.setDigits(p1_in);
		p1d.compare(getAnswer());
		cout<<"                                                 "<<step<<"       ";
		p1d.display();
		cout<<"     "<<p1d.getValueAndPosition()<<"A"<<p1d.getValueOnly()<<"B"<<endl;
		if(p1d.getValueAndPosition()==4)
		{
			cout<<p1.getName()<<" Win!"<<endl;
			winner=p1.getName();
			break;
		}
		p1d.set_getValueOnly();
		p1d.set_getValueAndPosition();
		step++;
		cout<<"Player 2   Please enter your digits:";
		cin>>in;
		while(p2d.checkFormat(in)!=true)
		{
			cout<<"Digits illegal\nPlayer 2   Please enter your digits:";
			cin>>in;
		}
		p2_in=toInt(in);
		p2d.setDigits(p2_in);
		p2d.compare(getAnswer());
		cout<<"                                                 "<<step<<"       ";
		p2d.display();
		cout<<"     "<<p2d.getValueAndPosition()<<"A"<<p2d.getValueOnly()<<"B"<<endl;
		if(p2d.getValueAndPosition()==4)
		{
			cout<<p2.getName()<<" Win!"<<endl;
			winner=p2.getName();
			break;
		}
		p2d.set_getValueOnly();
		p2d.set_getValueAndPosition();
	}
	cout<<"Winner："<<winner<<"!  Congratulations!!"<<endl; 
}

void game::gameMode_CH()
{
	char first='0'; 
	int correct=0;
	cout<<"请选择难度：    输入 1 菜鸟难度      输入 2 困难难度"<<endl;
	cin>>chooseDifficulty;
	while(chooseDifficulty!=1&&chooseDifficulty!=2)
	{
		cout<<"输入有误！请重新输入！"<<endl;
		cout<<"请选择难度：    输入 1 菜鸟难度      输入 2 困难难度"<<endl;
		cin>>chooseDifficulty;
	} 
	cout<<"请决定哪方先猜：      输入 1 玩家先猜       输入 2 电脑先猜"<<endl;
	cin>>first;
	while(first!='1'&&first!='2')
	{
		cout<<"输入有误！请重新输入！"<<endl;
		cout<<"请决定哪方先猜：      输入 1 玩家先猜       输入 2 电脑先猜"<<endl;
		cin>>first;
	}
	cout<<endl<<endl;
	cout<<"                                               "<<"Step"<<"    Number     "<<"A and B"<<endl; 
	if(first=='1')
	{
		player1="player Human";
	    player2="player Computer";
		playerHuman p1(player1);
		playerComputer p2(player2);
		digits p1d,p2d;
		string in;
		int p1_in,p2_in;
		while(correct!=4)
		{
			step++;
			cout<<"Player 1   Please enter your digits:";
			cin>>in;
			while(p1d.checkFormat(in)!=true)
			{
				cout<<"Digits illegal\nPlayer 1   Please enter your digits:";
				cin>>in;
			}
			p1_in=toInt(in);
			p1d.setDigits(p1_in);
			p1d.compare(getAnswer());
			cout<<"                                                 "<<step<<"       ";
			p1d.display();
			cout<<"     "<<p1d.getValueAndPosition()<<"A"<<p1d.getValueOnly()<<"B"<<endl;
			if(chooseDifficulty==2)
			p2.getInformation(p1_in,p1d.getValueAndPosition(),p1d.getValueOnly());
			else if(chooseDifficulty==1)
			p2.getInformation_(p1_in);
			if(p1d.getValueAndPosition()==4)
			{
				cout<<p1.getName()<<" Win!"<<endl;
				winner=p1.getName();
				break;
			}
			p1d.set_getValueOnly();
			p1d.set_getValueAndPosition();
			step++;
			cout<<"Player 2   Please enter your digits:";
			p2_in=p2.inputDigits_AI();
			p2d.setDigits(p2_in);
			p2d.display();
			while(p2d.checkFormat(p2_in)!=true)
    		{
	     		cout<<"\nDigits illegal\nPlayer 2   Please enter your digits:";
 	    		p2_in=p2.inputDigits_AI();
 	    		p2d.setDigits(p2_in);
			    p2d.display();
     		}
			p2d.compare(getAnswer());
			cout<<endl;
			cout<<"                                                 "<<step<<"       ";
			p2d.display();
			cout<<"     "<<p2d.getValueAndPosition()<<"A"<<p2d.getValueOnly()<<"B"<<endl;
			if(chooseDifficulty==2)
			p2.getInformation(p2_in,p2d.getValueAndPosition(),p2d.getValueOnly());
			else if(chooseDifficulty==1)
			p2.getInformation_(p2_in);
			if(p2d.getValueAndPosition()==4)
			{
				cout<<p2.getName()<<" Win!"<<endl;
				winner=p2.getName();
				break;
			}
			p2d.set_getValueOnly();
			p2d.set_getValueAndPosition();
		}
	}
	else if(first=='2')
	{
		player2="player Human";
	    player1="player Computer";
	    playerComputer p1(player1);
		playerHuman p2(player2);
		digits p1d,p2d;
		string in;
		int p1_in,p2_in;
		while(correct!=4)
		{
			step++;
			cout<<"Player 1   Please enter your digits:";
			p1_in=p1.inputDigits_AI();
			p1d.setDigits(p1_in);
			p1d.display();
			while(p1d.checkFormat(p1_in)!=true)
	    	{
    			cout<<"\nDigits illegal\nPlayer 1   Please enter your digits:";
	    		p1_in=p1.inputDigits_AI();
	    		p1d.setDigits(p1_in);
			    p1d.display();
	    	}
			cout<<endl;
			p1d.compare(getAnswer());
			cout<<"                                                 "<<step<<"       ";
			p1d.display();
			cout<<"     "<<p1d.getValueAndPosition()<<"A"<<p1d.getValueOnly()<<"B"<<endl;
			if(chooseDifficulty==2)
			p1.getInformation(p1_in,p1d.getValueAndPosition(),p1d.getValueOnly());
			else if(chooseDifficulty==1)
			p1.getInformation_(p1_in);
			if(p1d.getValueAndPosition()==4)
			{
				cout<<p1.getName()<<" Win!"<<endl;
				winner=p1.getName();
				break;
			}
			p1d.set_getValueOnly();
			p1d.set_getValueAndPosition();
			step++;
			cout<<"Player 2   Please enter your digits:";
			cin>>in;
			while(p2d.checkFormat(in)!=true)
			{
				cout<<"Digits illegal\nPlayer 2   Please enter your digits:";
				cin>>in;
			}
			p2_in=toInt(in);
			p2d.setDigits(p2_in);
			p2d.compare(getAnswer());
			cout<<"                                                 "<<step<<"       ";
			p2d.display();
			cout<<"     "<<p2d.getValueAndPosition()<<"A"<<p2d.getValueOnly()<<"B"<<endl;
			if(chooseDifficulty==2)
			p1.getInformation(p2_in,p2d.getValueAndPosition(),p2d.getValueOnly());
			else if(chooseDifficulty==1)
			p1.getInformation_(p2_in);
			if(p2d.getValueAndPosition()==4)
			{
				cout<<p2.getName()<<" Win!"<<endl;
				winner=p2.getName();
				break;
			}
			p2d.set_getValueOnly();
			p2d.set_getValueAndPosition();
		}
	}
	cout<<"Winner："<<winner<<"!  Congratulations!!"<<endl<<endl; 
	if(winner=="player Human")
	cout<<"You Win! You beat the Computer!"<<endl<<endl;
	else if(winner=="player Computer")
	cout<<"You Lose! That's a pity!"<<endl<<endl;
}

void game::gameMode_CC()
{ 
    int chooseDifficulty1=0,chooseDifficulty2=0; 
	int correct=0;
	cout<<"请选择电脑1的难度：    输入 1 菜鸟难度      输入 2 困难难度"<<endl;
	cin>>chooseDifficulty1;
	while(chooseDifficulty1!=1&&chooseDifficulty1!=2)
	{
		cout<<"输入有误！请重新输入！"<<endl;
		cout<<"请选择电脑1的难度：    输入 1 菜鸟难度      输入 2 困难难度"<<endl;
		cin>>chooseDifficulty1;
	}
	cout<<"请选择电脑2的难度：    输入 1 菜鸟难度      输入 2 困难难度"<<endl;
	cin>>chooseDifficulty2;
	while(chooseDifficulty2!=1&&chooseDifficulty2!=2)
	{
		cout<<"输入有误！请重新输入！"<<endl;
		cout<<"请选择电脑2的难度：    输入 1 菜鸟难度      输入 2 困难难度"<<endl;
		cin>>chooseDifficulty2;
	}
	cout<<endl<<endl;
	cout<<"                                               "<<"Step"<<"    Number     "<<"A and B"<<endl; 
	player1="player Computer1";
    player2="player Computer2";
	playerComputer p1(player1);
	playerComputer p2(player2);
	digits p1d,p2d;
	string in;
	int p1_in,p2_in;
	while(correct!=4)
	{
		step++;
		cout<<"Player 1   Please enter your digits:";
		p1_in=p1.inputDigits_AI();
		p1d.setDigits(p1_in);
		p1d.display();
		while(p1d.checkFormat(p1_in)!=true)
		{
			cout<<"\nDigits illegal\nPlayer 1   Please enter your digits:";
			p1_in=p1.inputDigits_AI();
			p1d.setDigits(p1_in);
		    p1d.display();
		}
		p1d.compare(getAnswer());
		cout<<endl;
		cout<<"                                                 "<<step<<"       ";
		p1d.display();
		cout<<"     "<<p1d.getValueAndPosition()<<"A"<<p1d.getValueOnly()<<"B"<<endl;
		if(chooseDifficulty1==2)
		p1.getInformation(p1_in,p1d.getValueAndPosition(),p1d.getValueOnly());
		else if(chooseDifficulty1==1)
		p1.getInformation_(p1_in);
		if(chooseDifficulty2==2)
		p2.getInformation(p1_in,p1d.getValueAndPosition(),p1d.getValueOnly());
		else if(chooseDifficulty2==1)
		p2.getInformation_(p1_in);
		if(p1d.getValueAndPosition()==4)
		{
			cout<<p1.getName()<<" Win!"<<endl;
			winner=p1.getName();
			break;
		}
		p1d.set_getValueOnly();
		p1d.set_getValueAndPosition();
		step++;
		cout<<"Player 2   Please enter your digits:";
		p2_in=p2.inputDigits_AI();
		p2d.setDigits(p2_in);
		p2d.display();
		while(p2d.checkFormat(p2_in)!=true)
		{
			cout<<"\nDigits illegal\nPlayer 2   Please enter your digits:";
			p2_in=p2.inputDigits_AI();
			p2d.setDigits(p2_in);
		    p2d.display();
		}
		p2d.compare(getAnswer());
		cout<<endl;
		cout<<"                                                 "<<step<<"       ";
		p2d.display();
		cout<<"     "<<p2d.getValueAndPosition()<<"A"<<p2d.getValueOnly()<<"B"<<endl;
		if(chooseDifficulty1==2)
		p1.getInformation(p2_in,p2d.getValueAndPosition(),p2d.getValueOnly());
		else if(chooseDifficulty1==1)
		p1.getInformation_(p2_in);
		if(chooseDifficulty2==2)
		p2.getInformation(p2_in,p2d.getValueAndPosition(),p2d.getValueOnly());
		else if(chooseDifficulty2==1)
		p2.getInformation_(p2_in);
		if(p2d.getValueAndPosition()==4)
		{
			cout<<p2.getName()<<" Win!"<<endl;
			winner=p2.getName();
			break;
		}
		p2d.set_getValueOnly();
		p2d.set_getValueAndPosition();
	}
}

void game::gameMode_H()
{
	cout<<endl<<endl;
	cout<<"                                               "<<"Step"<<"    Number     "<<"A and B"<<endl; 
	player1="player";
	playerHuman p1(player1);
	int correct=0;
	digits p1d;
	string in;
	int p1_in;
	while(correct!=4)
	{
		step++;
		cout<<"Player   Please enter your digits:";
		cin>>in;
		while(p1d.checkFormat(in)!=true)
		{
			cout<<"Digits illegal\nPlayer   Please enter your digits:";
			cin>>in;
		}
		p1_in=toInt(in);
		p1d.setDigits(p1_in);
		p1d.compare(getAnswer());
		cout<<"                                                 "<<step<<"       ";
		p1d.display();
		cout<<"     "<<p1d.getValueAndPosition()<<"A"<<p1d.getValueOnly()<<"B"<<endl;
		if(p1d.getValueAndPosition()==4)
		{
			cout<<"You Win!"<<endl;
			winner=p1.getName();
			break;
		}
		p1d.set_getValueOnly();
		p1d.set_getValueAndPosition();
	}
	cout<<"Winner："<<winner<<"!  Congratulations!!"<<endl; 
}

digits game::getAnswer()
{
	return answer;
}

 
int main()                                                                //main function
{
	game g1;
	g1.gameCreate();
	cout<<endl<<endl<<"****************游戏结束！欢迎下次再来玩！****************"<<endl; 
	system("pause");
	return 0;
}
