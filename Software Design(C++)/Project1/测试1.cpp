//Project 1

#include <iostream>
#include <cstdio>
#include <iomanip>
#include <string.h>
#include <string>
#include <cstring>
#include <ctype.h>

using namespace std;


int LegalJudge(string s,int size)//格式检查 
{
	int mark=1;
	/*string s;
	getline(cin,s,'\n');
	int size=s.length();*/
	if(s.find_first_not_of("0123456789+-*/ ")!=string::npos||s.at(size-1)=='+'||s.at(size-1)=='-'||s.at(size-1)=='*'||s.at(size-1)=='/')//含有不合法字符 
	mark=0;//cout<<"PE"<<endl;
	else if(s.find_first_of("0123456789 ")!=string::npos)
	{
		
		if(s.find_first_of("+-*/")==string::npos)//纯数字检测 
		{
			if(s.find_first_of(" ")==string::npos)//纯数字  符合 
			mark=1;//cout<<s<<endl;
			else if(s.find_first_of(" ")!=string::npos)//含有空格  判断 
			{
				bool flagn=0;
				for(int i=0;i<size-1;i++)
				{
					if(s.at(i)==' '&&s.at(i+1)!=' ')
					{
						for(int k=0;k<i;k++)
						{
							if(s.at(k)!=' ')
							{
								flagn=1;
							}
						}
					}
				}
				if(flagn==1)
				{
					mark=0;//cout<<"PE"<<endl;
				}
				else
				mark=1;//cout<<s<<endl;
			}
		}
				
		else//表达式检测 
		{
			int back,front;
			int flag=0,flag1=0;
			
			for(int i=0;i<size-2;i++)
			{
				//if((s.at(i)=='1'||s.at(i)=='2'||s.at(i)=='3'||s.at(i)=='4'||s.at(i)=='5'||s.at(i)=='6'||s.at(i)=='7'||s.at(i)=='8'||s.at(i)=='9'||s.at(i)=='0')&&(s.at(i+1)!='1'||s.at(i+1)!='2'||s.at(i+1)!='3'||s.at(i+1)!='4'||s.at(i+1)!='5'||s.at(i+1)!='6'||s.at(i+1)!='7'||s.at(i+1)!='8'||s.at(i+1)!='9'||s.at(i+1)!='0'))//第一种                                     
				if(s.at(i)!=' '&&s.at(i)!='+'&&s.at(i)!='-'&&s.at(i)!='*'&&s.at(i)!='/'&&s.at(i+1)==' '||s.at(i+1)=='+'||s.at(i+1)=='-'||s.at(i+1)=='*'||s.at(i+1)=='/')//数字间有空格   
				{
									
					front=i;
					
					for(int k=i+1;k<size-1;k++)
					{
						if(s.at(k)=='1'||s.at(k)=='2'||s.at(k)=='3'||s.at(k)=='4'||s.at(k)=='5'||s.at(k)=='6'||s.at(k)=='7'||s.at(k)=='8'||s.at(k)=='9'||s.at(k)=='0')
						{
							back=k;
							break;
						} 
					}
					
					for(int k=i+1;k<back;k++)
					{
						if(s.at(k)=='+'||s.at(k)=='-'||s.at(k)=='*'||s.at(k)=='/')
						{
							flag++;
						}
						if(s.at(k)==' ')
						{
							flag1=1;
						}
					}
						
					if(flag==1&&flag1==0)
					{
						mark=1;//cout<<s<<endl;
						break;
					}
					else if(flag==1&&flag1==1)
					{
						mark=1;//cout<<s<<endl;
						break;
					}
					else if(flag==0&&flag1==1)
					{
						mark=0;//cout<<"PE"<<endl;
					}	
				}
					
				if(s.at(i)=='+'||s.at(i)=='-'||s.at(i)=='*'||s.at(i)=='/') //连续符号 
				{
					for(int k=i+1;k<size;k++)
					{
						if(s.at(k)=='+'||s.at(k)=='-'||s.at(k)=='*'||s.at(k)=='/')
						{
							mark=0;//cout<<"PE"<<endl;
							break;
						}
						else if(s.at(k)!='+'&&s.at(k)!='-'&&s.at(k)!='*'&&s.at(k)!='/'&&s.at(k)!=' ')
						{
							break;
						}
					}
				}
			}
	
			if (s.at(0)==' '||s.at(0)=='+'||s.at(0)=='-'||s.at(0)=='*'||s.at(0)=='/')//不以符号开头 
			{
				if(s.at(0)=='+'||s.at(0)=='-'||s.at(0)=='*'||s.at(0)=='/')
				mark=0;//cout<<"PE"<<endl;
				else
				{
					for(int i=1;i<size;i++)
					{
						if(s.at(i)!=' '&&s.at(i)!='+'&&s.at(i)!='-'&&s.at(i)!='*'&&s.at(i)!='/')
						{
							mark=1;//cout<<s<<endl;
							break;
						}
						else if(s.at(i)==' ')
						{
							continue;
						}
						else
						{
							mark=0;//cout<<"PE"<<endl;
							break;
						}
					}
				}
			}
						
			if (s.at(size-1)==' '||s.at(size-1)=='+'||s.at(size-1)=='-'||s.at(size-1)=='*'||s.at(size-1)=='/')//不以符号结尾 
			{
				if(s.at(size-1)=='+'||s.at(size-1)=='-'||s.at(size-1)=='*'||s.at(size-1)=='/')
				    mark=0;//cout<<"PE"<<endl;
				else
				{
					for(int i=size-1;i>=1;i--)
					{
						if(s.at(i)!=' '&&s.at(i)!='+'&&s.at(i)!='-'&&s.at(i)!='*'&&s.at(i)!='/')
						{
							mark=1;//cout<<s<<endl;
							break;
						}
						else if(s.at(i)==' ')
						{
							continue;
						}
						else
						{
							mark=0;//cout<<"PE"<<endl;
							break;
						}
					}
				}
			}
		}
	}
	return mark;
}


string TrueEquation(string s,int size)//转换成标准的格式 
{
	for(int i=0;i<size;i++)
	{
		if(s.at(i)==' ')
		{
			s.replace(i,1,"");
			size--;
			i--;
		}
	} 
	return s;
} 




double Cal(string s)
{
	int Ans=0;
	int size,k=0;
	size=s.length();
	string a[1000],b[1000];
	b[0]="+"; 
	for(int i=0;i<size;i++)// 把各项存到一个数组中，把运算符号存到另一数组中 
	{
		if(s.at(i)!='+'&&s.at(i)!='-'&&s.at(i)!='*'&&s.at(i)!='/')
		{
			a[k+1]+=s.at(i);
		}
		else
		{
			b[k+1]+=s.at(i);
			k++;
		}
	}
	double c[1000]={0};
	int length; 
	for(int i=1;i<=k+1;i++)//把数组中字符串转化为双精度型 
	{
		length=a[i].length();
		double n,times=1;
		for(int t=length-1;t>=0;t--)
		{
			n=a[i].at(t)-48;
			n=n*times;
			c[i]+=n;
			times=times*10;
		}
	}

	for(int i=1;i<=k+1;i++)//先乘除 
	{
		if(b[i]=="*"||b[i]=="/")
		{
			double temp;
			if(b[i]=="*")
			{
				temp=c[i]*c[i+1];
				c[i]=0;
				c[i+1]=temp;
				b[i]=b[i-1];
			}
			else if(b[i]=="/")
			{
				temp=c[i]/c[i+1];
				c[i]=0;
				c[i+1]=temp;
				b[i]=b[i-1];
			}
		}
	}
	
	
	for(int i=1;i<=k+1;i++)//后加减 
	{
		if(b[i]=="+"||b[i]=="-")
		{
			double temp;
			if(b[i]=="+")
			{
				temp=c[i]+c[i+1];
				c[i]=0;
				c[i+1]=temp;
				Ans=c[i+1];
			}
			else if(b[i]=="-")
			{
				temp=c[i]-c[i+1];
				c[i]=0;
				c[i+1]=temp;
				Ans=c[i+1];
			}
		}
	}
	return Ans;
} 


int main()
{
cout<<"o(^▽^)o您好！！欢迎使用本计算器！！"<<endl;//欢迎界面 
	cout<<endl<<endl<<endl<<endl; 
	cout<<"请输入计算式:";
	 
	string str;
	getline(cin,str,'\n');//Input the equation
	int size;
	size=str.length();
	
    int mark;
	mark=LegalJudge(str,size) ;
	if(mark==1)
	{
		str=TrueEquation(str,size);
    
	    double Answer;
	    Answer=Cal(str);
	
	    cout<<endl<<endl<<endl<<endl<<endl; 
	    cout<<"答案：";
	    cout<<fixed<<setprecision(2)<<Answer<<endl;
	} 
	else
	{
		cout<<endl<<endl<<endl<<endl<<endl; 
		cout<<"      "<<"PE"<<"   "<<"(Sorry!输入的计算式子格式错误！)"<<endl;
	}
	//cout<<mark<<endl;
    
	
	//cout<<str<<endl;
    
    
    
	/*	if(str.find_first_not_of("0123456789+- * /")!=string::npos)//Check if there are any illegal characters in the equation
	cout<<"PE"<<endl;
	else if(str.find_first_of("1234567890")!=string::npos)//Check if the equation is just a number (1)
	{
		cout<<str<<endl;
	}
	else
	{
		int size_ori;
		size_ori=str.length();//The original length of string(str)
		cout<<size_ori<<endl;
		
		for(int i=0;i<size_ori-2;i++)
		{
			if(isdigit(str.at(i)))
			{
				if(str.at(i+1)==' ')
				{
					for(int k=i+2;k<size_ori;k++)
			    	{
					    if(str.at(k)=='+'||str.at(k)=='-'||str.at(k)=='*'||str.at(k)=='/')
					    break;
					    else if()
			    	}
				}
				else if(i==size-1)
			}
		}
	}*/ 
	
	
	
	
	
}


