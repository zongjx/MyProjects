//计算表达式 








#include <iostream>
#include <string>
#include <string.h>
#include <iomanip>


using namespace std;
double Ans=0;
int main()
{
	int flag0=0; 
	string s;
	getline(cin,s,'\n');
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
				if(c[i+1]==0)
				{
					flag0=1;
				}
	        	temp=c[i]/c[i+1];
				c[i]=0;
				c[i+1]=temp;
				b[i]=b[i-1];
			}
		}
	}
//	for(int i=1;i<=k+1;i++)
//	{
//		cout<<c[i]<<" ";
//	}
	
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
	
	
	if(flag0==1)
	{
		cout<<"PE"<<endl;
	}
	else
	cout<<fixed<<setprecision(2)<<Ans<<endl;
}






/*

double Cal(string s)
{
	int Ans=0;
	int size,k=0;
	size=s.length();
	string a[1000],b[1000];
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
} */
