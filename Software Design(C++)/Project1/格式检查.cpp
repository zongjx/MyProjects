//judge if the equation legal


#include <iostream>
#include <cstdio>
#include <string>
#include <string.h>


using namespace std;


int main()
{
	string s;
	getline(cin,s,'\n');
	int size=s.length();
	if(s.find_first_not_of("0123456789+-*/ ")!=string::npos||s.at(size-1)=='+'||s.at(size-1)=='-'||s.at(size-1)=='*'||s.at(size-1)=='/')//含有不合法字符 
	cout<<"PE"<<endl;
	else if(s.find_first_of("0123456789 ")!=string::npos)
	{
		
		if(s.find_first_of("+-*/")==string::npos)//纯数字检测 
		{
			if(s.find_first_of(" ")==string::npos)//纯数字  符合 
			cout<<s<<endl;
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
					cout<<"PE"<<endl;
				}
				else
				cout<<s<<endl;
			}
		}
		
		
		
		else//表达式检测 
		{
			int back,front;
			int flag=0,flag1=0;
			
			
			
			for(int i=0;i<size-2;i++)
			{
				//if((s.at(i)=='1'||s.at(i)=='2'||s.at(i)=='3'||s.at(i)=='4'||s.at(i)=='5'||s.at(i)=='6'||s.at(i)=='7'||s.at(i)=='8'||s.at(i)=='9'||s.at(i)=='0')&&(s.at(i+1)!='1'||s.at(i+1)!='2'||s.at(i+1)!='3'||s.at(i+1)!='4'||s.at(i+1)!='5'||s.at(i+1)!='6'||s.at(i+1)!='7'||s.at(i+1)!='8'||s.at(i+1)!='9'||s.at(i+1)!='0'))//第一种                                     
				if((s.at(i)!=' '&&s.at(i)!='+'&&s.at(i)!='-'&&s.at(i)!='*'&&s.at(i)!='/')&&s.at(i+1)==' '||s.at(i+1)=='+'||s.at(i+1)=='-'||s.at(i+1)=='*'||s.at(i+1)=='/')//数字间有空格   
				{
					
					
					front=i;
					flag=0,flag1=0;
					
					
					for(int k=i+1;k<size-1;k++)
					{
						if(s.at(k)=='1'||s.at(k)=='2'||s.at(k)=='3'||s.at(k)=='4'||s.at(k)=='5'||s.at(k)=='6'||s.at(k)=='7'||s.at(k)=='8'||s.at(k)=='9'||s.at(k)=='0')
						{
							back=k;
							break;
						} 
					}
					
					
					
					for(int k=i+1;k<=back;k++)
					{
						flag=0;
						flag1=0; 
						if(s.at(k)=='+'||s.at(k)=='-'||s.at(k)=='*'||s.at(k)=='/')
						{
							flag++;
						}
						else if(s.at(k)==' ')
						{
							flag1=1;
							break;
						}
					}
					
					
					
					if(flag==1&&flag1==0)
					{
						cout<<s<<endl;
						break;
					}
					else if(flag==1&&flag1==1)
					{
						cout<<s<<endl;
						break;
					}
					else if(flag==0&&flag1==1)
					{
						cout<<"PE"<<endl;
						break; 
					}
					
					
				}
				
				
				
				
				
				if(s.at(i)=='+'||s.at(i)=='-'||s.at(i)=='*'||s.at(i)=='/') //连续符号 
				{
					for(int k=i+1;k<size;k++)
					{
						if(s.at(k)=='+'||s.at(k)=='-'||s.at(k)=='*'||s.at(k)=='/')
						{
							cout<<"PE"<<endl;
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
					cout<<"PE"<<endl;
					else
					{
						for(int i=1;i<size;i++)
						{
							if(s.at(i)!=' '&&s.at(i)!='+'&&s.at(i)!='-'&&s.at(i)!='*'&&s.at(i)!='/')
							{
								cout<<s<<endl;
								break;
							}
							else if(s.at(i)==' ')
							{
								continue;
							}
							else
							{
								cout<<"PE"<<endl;
								break;
							}
						}
					}
				}
				
				
				
				
					if (s.at(size-1)==' '||s.at(size-1)=='+'||s.at(size-1)=='-'||s.at(size-1)=='*'||s.at(size-1)=='/')//不以符号结尾 
				{
					if(s.at(size-1)=='+'||s.at(size-1)=='-'||s.at(size-1)=='*'||s.at(size-1)=='/')
					cout<<"PE"<<endl;
					else
					{
						for(int i=size-1;i>=1;i--)
						{
							if(s.at(i)!=' '&&s.at(i)!='+'&&s.at(i)!='-'&&s.at(i)!='*'&&s.at(i)!='/')
							{
								cout<<s<<endl;
								break;
							}
							else if(s.at(i)==' ')
							{
								continue;
							}
							else
							{
								cout<<"PE"<<endl;
								break;
							}
						}
					}
				}
				
				
				//if//数字间有空格 
		}
	}
}

