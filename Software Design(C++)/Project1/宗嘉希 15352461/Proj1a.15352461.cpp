//Project 1


//by Zongjiaxi

#include <iostream>
#include <cstdio>
#include <iomanip>
#include <string.h>
#include <string>
#include <cstring>

using namespace std;


int LegalJudge(string s,int size)//格式检查 
{
	
	int mark=1;

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
						break; 
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




void Cal(string s)//计算函数 
{
	int flag_0=0; 
	
	double Ans=0;
	
	int size,k=0;
	int flag3=0;
	size=s.length();
	string a[1000],b[1000];
	b[0]="+"; 
	
	for(int i=0;i<size;i++)//检测是否只有一个项 
	{
		if(s.at(i)=='+'||s.at(i)=='-'||s.at(i)=='*'||s.at(i)=='/')
		flag3++;
	} 
	
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
	
	if(flag3==0)//若只有一个项，则不进行计算，直接输出 
	{
		Ans=c[1];
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
				flag_0=1;
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
	
	if(flag_0==0)
	cout<<fixed<<setprecision(2)<<Ans<<endl;
	else
	cout<<"PE"<<endl;
} 




void H_Cal(string s)//附加功能：两个整数项的高精度加法、减法、乘法 
{
	char w;
	int pos;
	for(int i=0;i<s.length();i++)
	{
		if(s.at(i)=='+'||s.at(i)=='-'||s.at(i)=='*')
		{
			w=s.at(i);
			pos=i;
			break;
		}
	}
	int c[101]={},d[101]={};
	int r[210]={};
	int sizea,sizeb;
   	sizea=pos;
   	sizeb=s.length()-pos-1;
	for(int i=0;i<sizea;i++)
   	{
 		c[i]=s.at(sizea-i-1)-'0';
   	}
   	for(int i=0;i<sizeb;i++)
  	{
   		d[i]=s.at(pos+sizeb-i)-'0';
  	}
  	
	if(w=='*')//乘法 
	{
    	int e=0;
    	for(int i=0;i<sizea;i++)
    	{
    		int mark=i;
    		for(int k=0;k<sizeb;k++)
    		{
	    		r[mark]+=c[i]*d[k];
    			if(r[mark]>=10)
    			{
    				r[mark+1]+=r[mark]/10;
    				r[mark]%=10;
	    		}
    			mark++;
    		}
      	} 
       	int k=209;
       	for(;k>=0;k--)
       	{
       		if(r[k])
      	    break;
       	}
        for(;k>=0;k--)
       	{
       		cout<<r[k];
       	}
        	cout<<".00"<<endl;
   	}
   	
   	
   	else if(w=='+')//加法 
   	{
   		int e=0;	
        for(int i=0;i<101;i++)
        {
   		    r[i]=c[i]+d[i]+e;
       		if(r[i]>=10)
       		{
   	    		e=r[i]/10;
			  	r[i]=r[i]-e*10;
        	}
      		else
   	    	e=0;
       	}
		   	
      	int k=100;
   	    for(;k>0;k--)
       	{
       		if(r[k])
   	    	break;
	    }
       	for(;k>=0;k--)
       	{
         	cout<<r[k];
   	    }
   	    cout<<".00"<<endl;
   	}
    	
    	
	else if(w=='-')//减法 
    {
    	int g[210]={};
    	int e=0;
    	int mark1=0,mark2,mark;
	    if(sizea>sizeb)
	    {
	    	mark2=1;
	    	mark=sizea;
	    }
	    else if(sizea<sizeb)
	    {
	    	mark2=2;
	    	mark=sizeb;
	    }
	    else if(sizea==sizeb)
	    {
	    	mark2=0;
	    	mark=sizea;
	    }
	    if(mark2==1)
	    {
	    	for(int i=0;i<mark;i++)
	    	{
	    		if(i!=mark-1)
	    		{
	    			r[i]=c[i]-d[i]-e;
	    			if(r[i]<0)
	    			{
	    				r[i]=r[i]+10;
	    				e=1;
	    			}
	    			else
	    			{
	    				e=0;
	    			}
	    		}
	    		else
	    		r[i]=c[i]-d[i]-e;
	    	}
	    }
	    else if(mark2==2)
	    {
	    	for(int i=0;i<mark;i++)
	    	{
	    		if(i!=mark-1)
	    		{
	    			r[i]=d[i]-c[i]-e;
	    			if(r[i]<0)
	    			{
	    				r[i]=r[i]+10;
	    				e=1;
	    			}
	    			else
	    			{
	    				e=0;
	    			}
	    		}
	    		else
	    		r[i]=d[i]-c[i]-e;
	    	}
	    }
	    else if(mark2==0)
	    {
	    	int e=0;
	    	for(int i=0;i<mark;i++)
	    	{
	    		if(i!=mark-1)
	    		{
	    			g[i]=c[i]-d[i]-e;
	    			if(g[i]<0)
	    			{
	    				g[i]=g[i]+10;
	    				e=1;
	    			}
	    			else
	    			{
	    				e=0;
	    			}
	    		}
	    		else
	    		g[i]=c[i]-d[i]-e;
	    	}
	    	int k=mark;
	    	for(;k>=0;k--)
	    	{
	    		if(g[k]!=0)
	    		break;
	    	}
	    	if(g[k]>0)
	    	{
	    		mark1=0;
	    		for(int i=0;i<=mark;i++)
	          	{
	    	    	if(i!=mark)
	    		    {
	    			    r[i]=c[i]-d[i]-e;
	    	    		if(r[i]<0)
	    		    	{
	        				r[i]=r[i]+10;
	    	    			e=1;
	    		    	}
	        			else
	    	    		{
	    		    		e=0;
	        			}
	    	    	}
	    		    else
	    	    	r[i]=c[i]-d[i]-e;
	    	    }
	    	}
	    	else if(g[k]<0)
	    	{
	    		mark1=1;
	    		for(int i=0;i<=mark;i++)
	        	{
	    	    	if(i<mark)
	    	    	{
	    	    		r[i]=d[i]-c[i]-e;
	    	    		if(r[i]<0)
	    		    	{
	    		    		r[i]=r[i]+10;
	    	    			e=1;
	    		    	}
	        			else
	    	    		{
	    		    		e=0;
	    			    }
	    	    	}
	    	    	else
	    	    	r[i]=d[i]-c[i]-e;
	    	    }
	    	}
	    }
	    if(mark2==2)
	    {
	    	cout<<"-";
	    	int i=mark;
     	    for(;i>=0;i--)
	        {
	        	if(r[i]!=0)
	    	    break;
    	    }
	        for(;i>=0;i--)
	        {
	        	cout<<r[i];
	        } 
	    }
	    else if(mark2==1)
	    {
	    	int i=mark;
     	    for(;i>=0;i--)
	        {
	        	if(r[i]!=0)
	    	    break;
    	    }
	        for(;i>=0;i--)
	        {
	        	cout<<r[i];
	        } 
	    }
	    else if(mark2==0)
	    {
	    	if(mark1==1)
	    	{
	    		cout<<"-";
	    	}
	    	int i=mark;
	    	if(mark1==1)
	    	r[0]+=1;
	    	for(;i>=0;i--)
	    	{
	    		if(r[i]!=0)
	    		break;
	    		else if(i==0)
	    		{
	    			cout<<"0";
	    		}
	    	}
	    	for(;i>=0;i--)
	    	{
	    		cout<<r[i];
	    	}
	    }
	    cout<<".00"<<endl;
	}
}

int main()
{ 

	int n;
	cin>>n;
	getchar(); 
	string str;
	while(n--)
	{
		getline(cin,str,'\n');//输入运算表达式 
	int size;
	size=str.length();
	
    int mark,count=0;
	mark=LegalJudge(str,size) ;
	if(mark==1)
	{
		str=TrueEquation(str,size);
		
		size=str.length();
		
        for(int i=0;i<size;i++)
		{
			if(str.at(i)=='+'||str.at(i)=='-'||str.at(i)=='*')
			count++;
		}

		if(count==1)
		{
			H_Cal(str);
		}
		else
		Cal(str);
		//cout<<fixed<<setprecision(2)<<Answer<<endl;
	} 
	else
	{
	   cout<<"PE"<<endl;
	}
	}
	system("pause");
}

