#ifndef PLAYERCOMPUTER_H
#define PLAYERCOMPUTER_H
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
#endif
