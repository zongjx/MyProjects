//代码说明：直接输入两个多项式的相加、相减或相乘的表达式，分别用英式小括号（不要用中文输入法输入小括号）括住两个多项式（例  (x^2+5x^3)*(4+6x^5-6x)） 
//按回车键直接输出得数，下一步可以选择进行链式输出、求导或输入值计算结果，也可以选择返回上一步进行下一次计算 


#include <iostream>  
#include <string>
using namespace std;

struct List                    //创建链表结构体 
{
	double coe;
	int exp;
	List *next;
};

List* create(int k)            //创建链表的函数 
{
	int i=1;
	List *h,*p,*q;
	h=NULL;
	p=new List;
	q=p;
	while(i)
	{
		p->coe=0;
		p->exp=i-1;
		if(h==NULL)
		h=p;
		else
		q->next=p;
		q=p;
		p=new List;
		i++;
		if(i>k)
		break;
	}
	q->next=NULL;
	p->exp=-1;
	p->coe=k-1;
	p->next=h;
	h=p;
	return h;
}

void dele(List* th)              //删除链表释放空间的函数 
{
	List *h=th;
	while(th!=NULL)
	{
		h=th;
		th=th->next;
		delete h;
	}
}

List* insert(List *th,int e)     //插入新链结点的函数 
{
	List *h=th,*p;
	h->coe+=1;
	h=h->next;
	while(h->exp<e&&h->next!=NULL)
	{
		h=h->next;
	}
	p=new List;
	p->coe=0;
	p->exp=e;
	p->next=h->next;
	h->next=p;
	return th;
} 

List* trans(string s1,string s2,char cal,List *th,char a)        //把输入的多项式存到链表里的函数 
{
	bool add=0,minus=0,skip=0,mskip=0,ze=0;
	List *h;
	h=th;
	char qe,lcal='+';
	int l1,l2;
	l1=s1.length();
	l2=s2.length();
	for(int i=0;i<l1;i++)
	{
		if(s1[i]>=65&&s1[i]<=90||s1[i]>=97&&s1[i]<=122)
		{
			qe=s1[i];
			break;
		}
	}
	for(int i=0;i<l2;i++)
	{
		if(s2[i]>=65&&s2[i]<=90||s2[i]>=97&&s2[i]<=122)
		{
			qe=s2[i];
			break;
		}
	}
	int front=0,back=0,c1=0,p=0;
	double n1=0;
	bool chang=0,fu=0;
	if(s1[0]=='-')
	{
		skip=1;
		mskip=1;
	}
	for(int i=0;i<l1;i++)
	{
		h=th;
		if(s1[i]>=48&&s1[i]<=57)
		{
			chang=1;
			if(s1[i]==48)
			ze=1;
		}
		else if(s1[i]==qe)
		{
			chang=0;
			bool f1=0;
			p=0;
			double time=1;
			n1=0;
			back=i;
			for(int k=front;k<back;k++)
			{
			    if(s1[k]=='.')
			    {
			    	p++;
			    	f1=1;
			    	break;
			    }
			    else 
			    p++;
			}
			if(f1==1)
			{
				for(int y=2;y<p;y++)
		    	time*=10;
			}
			else
			{
				for(int y=1;y<back-front;y++)
		    	time*=10;
			}
			for(int k=front;k<back;k++)
			{
				if(k-front+1==p)
				{
					if(f1==1)
					{
						
					}
					else
					{
						if(s1[k]!='-')
						n1+=(s1[k]-'0')*time;
			            time/=10;
					}
				}
				else 
				{
					if(s1[k]!='-')
					n1+=(s1[k]-'0')*time;
			        time/=10;
				}				
			}
		}
		else if(s1[i]=='+'||s1[i]=='-'||s1[i]==')')
		{    
		    if(skip==1)
		    {
		    	skip=0;
		    }
		    else
		    {
			   	add=0;
				c1=0;
				int time=1;
				back=i;
				for(int y=1;y<back-front;y++)
				time*=10;
				if(s1[i-1]==a)
				{
					c1=1;
				} 
				else
				{
					for(int k=front;k<back;k++)
					{
						if(s1[k]!='-')
						{
							c1+=(s1[k]-'0')*time;
						}
						time/=10;
					}
				}
				if(minus==1)
				c1*=-1;
				if(n1==0&&ze==1)
				{
					
				}
				else
				{
					if(chang==1&&fu==0)
					{
						n1=c1;
						c1=0;
					}
					else
					{	
					    if(n1==0)
					    n1=1;
					}
				}
				if(mskip==1)
				{
					mskip=0;
					n1*=-1;
				}
			    while(h!=NULL)
			    {
			    	if(h->exp==c1)
			    	{
			    		add=1;
			    		break;
			    	}
			    	h=h->next;
			    }
			    if(add==0)
			    insert(th,c1);
			    h=th;
				while(h->exp!=c1)
				{
					h=h->next;
		    	}
				if(lcal=='+')
				h->coe+=n1;
				else if(lcal=='-')
				h->coe-=n1;
				front=i+1;
				lcal=s1[i];
				fu=0;
				chang=0;
				minus=0;
				if(h->coe==0)
				th->coe--;
		    }	
			ze=0;
		}
		else if(s1[i]=='^')
		{
			fu=1;
			front=i+1;
			if(s1[i+1]=='-')
			{
				minus=1;
			    skip=1;
			}
		}
		if(s1[i+1]==a)
		n1=1;
	
	}
	front=0;
	back=0;
	lcal='+';
	chang=0;
	fu=0;
	minus=0;
	skip=0;
	n1=0;
	ze=0;
	if(s2[0]=='-')
	{
		skip=1;
		mskip=1;
	}
	for(int i=0;i<l2;i++)
	{
		h=th;
		if(s2[i]>=48&&s2[i]<=57)
		{
			chang=1;
			if(s2[i]==48)
			ze=1;
		}
		else if(s2[i]==qe)
		{
			chang=0;
			bool f1=0;
			p=0;
		    double time=1;
			n1=0;
			back=i;
			for(int k=front;k<back;k++)
			{
			    if(s2[k]=='.')
			    {
			    	p++;
			    	f1=1;
			    	break;
			    }
			    else 
			    p++;
			}
			if(f1==1)
			{
				for(int y=2;y<p;y++)
		    	time*=10;
			}
			else
			{
				for(int y=1;y<back-front;y++)
				{
					time*=10;
				}
		    	
			}
			for(int k=front;k<back;k++)
			{
				if(k-front+1==p)
				{
					if(f1==1)
					{
						
					}
					else
					{
						if(s2[k]!='-')
						n1+=(s2[k]-'0')*time;
			            time/=10;
					}
				}
				else 
				{
					if(s2[k]!='-')
					n1+=(s2[k]-'0')*time;
		    	    time/=10;
				}   
			}
		}
		else if(s2[i]=='+'||s2[i]=='-'||s2[i]==')')
		{
			if(skip==1)
			{
				skip=0;
			}
			else
			{
				add=0;
				c1=0;
				int time=1;
				back=i;
				for(int y=1;y<back-front;y++)
				time*=10;
				if(s2[i-1]==a)
				{
					c1=1;
				} 
				else
				{
					for(int k=front;k<back;k++)
					{
						if(s2[k]!='-')
						{
						    c1+=(s2[k]-'0')*time;   
					    } 
						time/=10;
					}
				}
				//h=th;
				if(minus==1)
				c1*=-1;
				if(n1==0&&ze==1)
				{
					
				}
				else
				{
					if(chang==1&&fu==0)
					{
						n1=c1;
						c1=0;
					}
					else
					{
						if(n1==0)
				    	n1=1;
					}
				}
				if(mskip==1)
				{
					mskip=0;
					n1*=-1;
				}
				while(h!=NULL)
			    {
			    	if(h->exp==c1)
			    	{
			    		add=1;
			    		break;
			    	}
			    	h=h->next;
			    }
			    if(add==0)
			    insert(th,c1);
			    h=th;
				while(h->exp!=c1)
				{
					h=h->next;    
				}
				if(cal=='+')
				{
					if(lcal=='+')
					h->coe+=n1;
					else if(lcal=='-')
					h->coe-=n1;
				}
				else if(cal=='-')
				{
					if(lcal=='+')
					h->coe-=n1;
					else if(lcal=='-')
					h->coe+=n1;
				}
				front=i+1;
				lcal=s2[i];
				fu=0;
				chang=0;
				minus=0;
				if(h->coe==0)
			    th->coe--;
			}
			ze=0;
		}
		else if(s2[i]=='^')
		{
			fu=1;
			front=i+1;
			if(s2[i+1]=='-')
			{
				minus=1;
				skip=1;
			}
		}
		if(s2[i+1]==a)
		n1=1;
	}
    h=th;
    while(h->exp!=0)
	{
		h=h->next;
	} 
	if(h->coe!=0)
	th->coe+=1;
	return th;
}

void print_link(List *th)                     //输出多项式的函数 
{
	List *h=th;
	cout<<"共有"<<h->coe<<"项"<<endl;
	h=h->next; 
	while(h!=NULL)
	{
		if(h->coe!=0)
		{
			cout<<"系数:"<<h->coe<<"   指数:"<<h->exp<<endl; 
		}
		h=h->next;
	}
}

void print(List *th,char a)                   //输出多项式的函数 
{
	bool nu=0,nk=0;
	List *h=th;
	h=h->next;
	if(h->coe!=0)
	{
		if(h->coe>0)
		cout<<h->coe;
		else
		cout<<h->coe;
		nu=1;
		nk=1;
	}
	h=h->next;
	while(h!=NULL)
	{
		if(h->coe<0)
		{
		    if(h->coe==-1)
		    cout<<"-"<<a;
		    else
			cout<<h->coe<<a;
			if(h->exp==1)
			{
				
			}
			else
			cout<<"^"<<h->exp;
			nk=1;
		}
		else if(h->coe>0)
		{
			if(nu==0)
			{
				if(h->coe==1)
				{
					cout<<a;
				}
				else
				cout<<h->coe<<a;
				if(h->exp==1)
				{
					
				}
				else
				cout<<"^"<<h->exp;
				nu=1;
				nk=1;
			}
			else
			{
				if(h->coe==1)
				cout<<"+"<<a;
				else
				cout<<"+"<<h->coe<<a;
				if(h->exp==1)
				{
					
				}
				else
				cout<<"^"<<h->exp;
				nk=1;
			}
		}
		h=h->next;
	}
	if(nk==0)
	cout<<0;
	cout<<endl;
}

List* mul_1(string s1,string s2,List *th,char a)               //计算多项式乘法的函数 
{
	bool add,minus=0,skip=0,mskip=0,ze=0;
	char cal='+';
	List *h,*h1,*h2,*h1x,*h2x;
	h1=create(1);
	h2=create(1);
	h=th;
	h1x=h1;
	h2x=h2;
	char qe,lcal='+';
	int l1,l2;
	l1=s1.length();
	l2=s2.length();
	for(int i=0;i<l1;i++)
	{
		if(s1[i]>=65&&s1[i]<=90||s1[i]>=97&&s1[i]<=122)
		{
			qe=s1[i];
			break;
		}
	}
	for(int i=0;i<l2;i++)
	{
		if(s2[i]>=65&&s2[i]<=90||s2[i]>=97&&s2[i]<=122)
		{
			qe=s2[i];
			break;
		}
	}
	int front=0,back=0,c1=0,p=0;
	double n1=0;
	bool chang=0,fu=0;
	if(s1[0]=='-')
	{
		skip=1;
		mskip=1;
	}
	for(int i=0;i<l1;i++)
	{
		h1x=h1;
		if(s1[i]>=48&&s1[i]<=57)
		{
			chang=1;
			if(s1[i]==48)
			ze=1;
		}
		else if(s1[i]==qe)
		{
			chang=0;
			bool f1=0;
			p=0;
			double time=1;
			n1=0;
			back=i;
			for(int k=front;k<back;k++)
			{
			    if(s1[k]=='.')
			    {
			    	p++;
			    	f1=1;
			    	break;
			    }
			    else 
			    p++;
			}
			if(f1==1)
			{
				for(int y=2;y<p;y++)
		    	time*=10;
			}
			else
			{
				for(int y=1;y<back-front;y++)
		    	time*=10;
			}
			for(int k=front;k<back;k++)
			{
				if(k-front+1==p)
				{
					if(f1==1)
					{
						
					}
					else
					{
						if(s1[k]!='-')
						n1+=(s1[k]-'0')*time;
			            time/=10;
					}
				}
				else 
				{
					if(s2[k]!='-')
					n1+=(s1[k]-'0')*time;
			        time/=10;
				}				
			}
		}
		else if(s1[i]=='+'||s1[i]=='-'||s1[i]==')')
		{
			if(skip==1)
			{
				skip=0;
			}
			else
			{
				add=0;
				c1=0;
				int time=1;
				back=i;
				for(int y=1;y<back-front;y++)
				time*=10;
				if(s1[i-1]==a)
				{
					c1=1;
				} 
				else
				{
					for(int k=front;k<back;k++)
					{
						if(s1[k]!='-')
						{
							c1+=(s1[k]-'0')*time;
						}
					    time/=10;
					}
				}
				if(minus==1)
				c1*=-1;
				if(n1==0&&ze==1)
				{
					
				}
				else
				{
					if(chang==1&&fu==0)
					{
						n1=c1;
						c1=0;
					}
					else
					{	
					    if(n1==0)
					    n1=1;
					}
				}
				//h=th;
				if(mskip==1)
				{
					mskip=0;
					n1*=-1;
				}
			    while(h1x!=NULL)
			    {
			    	if(h1x->exp==c1)
			    	{
			    		add=1;
			    		break;
			    	}
			    	h1x=h1x->next;
			    }
			    if(add==0)
			    insert(h1,c1);
			    h1x=h1;
				while(h1x->exp!=c1)
				{
					h1x=h1x->next;
				}
				if(lcal=='+')
				h1x->coe+=n1;
				else if(lcal=='-')
				h1x->coe-=n1;
				front=i+1;
				lcal=s1[i];
				fu=0;
				chang=0;
				if(h->coe==0)
				th->coe--;
			}
			ze=0;
		}
		else if(s1[i]=='^')
		{
			fu=1;
			front=i+1;
			if(s1[i+1]=='-')
			{
				minus=1;
				skip=1;
			}
		}
		if(s1[i+1]==a)
		n1=1;
	}
	front=0;
	back=0;
	lcal='+';
	chang=0;
	minus=0;
	fu=0;
    if(s2[0]=='-')
    {
    	skip=1;
    	mskip=1;
    }
	for(int i=0;i<l2;i++)
	{
		h2x=h2;
		if(s2[i]>=48&&s2[i]<=57)
		{
			chang=1;
		}
		else if(s2[i]==qe)
		{
			chang=0;
			bool f1=0;
			p=0;
		    double time=1;
			n1=0;
			back=i;
			for(int k=front;k<back;k++)
			{
			    if(s2[k]=='.')
			    {
			    	p++;
			    	f1=1;
			    	break;
			    }
			    else 
			    p++;
			}
			if(f1==1)
			{
				for(int y=2;y<p;y++)
		    	time*=10;
			}
			else
			{
				for(int y=1;y<back-front;y++)
		    	time*=10;
			}
			for(int k=front;k<back;k++)
			{
				if(k-front+1==p)
				{
					if(f1==1)
					{
						
					}
					else
					{
						if(s2[k]!='-')
						n1+=(s2[k]-'0')*time;
			            time/=10;
					}
				}
				else 
				{
					if(s2[k]!='-')
					n1+=(s2[k]-'0')*time;
		    	    time/=10;
				}   
			}
		}
		else if(s2[i]=='+'||s2[i]=='-'||s2[i]==')')
		{
			if(skip==1)
			{
				skip=0;
			}
			else
			{
				add=0;
				c1=0;
				int time=1;
				back=i;
				for(int y=1;y<back-front;y++)
				time*=10;
				if(s1[i-1]==a)
				{
					c1=1;
				} 
				else
				{
					for(int k=front;k<back;k++)
					{
						if(s2[k]!='-')
						{
						    c1+=(s2[k]-'0')*time;
						}
					    time/=10;
					}
				}
				//h=th;
				if(minus==1)
				c1*=-1;
				if(chang==1&&fu==0)
				{
					n1=c1;
					c1=0;
				}
				else
				{
					if(n1==0)
			    	n1=1;
				}
				if(mskip==1)
				{
					mskip=0;
					n1*=-1;
				}
				while(h2x!=NULL)
			    {
			    	if(h2x->exp==c1)
			    	{
			    		add=1;
			    		break;
			    	}
			    	h2x=h2x->next;
			    }
			    if(add==0)
			    insert(h2,c1);
			    h2x=h2;
				while(h2x->exp!=c1)
				{
					h2x=h2x->next;    
				}
				if(cal=='+')
				{
					if(lcal=='+')
					h2x->coe+=n1;
					else if(lcal=='-')
					h2x->coe-=n1;
				}
				else if(cal=='-')
				{
					if(lcal=='+')
					h2x->coe-=n1;
					else if(lcal=='-')
					h2x->coe+=n1;
				}
				front=i+1;
				lcal=s2[i];
				fu=0;
				chang=0;
				minus=0;
				if(h->coe==0)
				th->coe--;
			}
		}
		else if(s2[i]=='^')
		{
			fu=1;
			front=i+1;
			if(s2[i+1]=='-')
			{
				minus=1;
				skip=1;
			}
		}
		if(s2[i+1]==a)
		n1=1;
	}
    add=0;
    h1x=h1;
    h2x=h2;
    h1x=h1x->next;
    h2x=h2x->next;
    while(h2x!=NULL)
    {
    	if(h2x->coe!=0)
    	{
    		h1x=h1->next;
    		while(h1x!=NULL)
    		{
    			if(h1x->coe!=0)
    			{
    				h=th;
					add=0;
    				while(h!=NULL)
    				{
    					if(h->exp==h1x->exp+h2x->exp)
    					{
    						add=1;
    						break;
    					}
    					h=h->next;
    				}
    				if(add==0)
    				{
    					insert(th,h1x->exp+h2x->exp);
    				}
    				h=th;
    				while(h->exp!=h1x->exp+h2x->exp) 
    				{
    					h=h->next;
    				}
    				h->coe=h1x->coe*h2x->coe;
    			}
    			h1x=h1x->next;
    		}
    	}
    	h2x=h2x->next;
    }
    h=th;
    while(h->exp!=0)
	{
		h=h->next;
	} 
	if(h->coe!=0)
	th->coe+=1;
    print(th,a);
	return th;
}


void cal_1(List *th,double x)                        //输入一个数求多项式的结果的函数 
{
	List *h=th;
	h=h->next;
	long double ans=0;
	while(h!=NULL)
	{
		double t=1;
		if(h->exp>0)
		{
			for(int i=0;i<h->exp;i++)
			{
				t*=x;
			}
		}
		else if(h->exp<0)
		{
			for(int i=1;i<=-h->exp;i++)
			{
				t*=x;
			}
			t=1/t;
		}
		t=t*h->coe;
		ans+=t;
		h=h->next;
	}
	cout<<"answer is :"<<ans<<endl;
}

void deri(List *th,char a)                          //多项式求导的函数 
{
	List *h,*hn,*k;
	hn=create(1);
	k=hn;
	h=th;
	h=h->next->next;
	while(h!=NULL)
	{
		insert(hn,h->exp-1);
		h=h->next;
	}
	h=th->next->next;
	k=hn->next->next;
	while(h!=NULL)
	{
		k->coe=h->coe*h->exp;
		h=h->next;
		k=k->next;
	}
    hn->next=hn->next->next;
	print(hn,a);
}



bool check(string s)                                //检查输出的多项式是否有格式错误的函数 
{
	int l;
	bool m=0;
	int cnt=0;
	l=s.length();
	for(int i=0;i<l;i++)
	{
		if(s[i]=='('&&cnt==0||cnt==2)
		{
			cnt++;
			if(s[i+1]==')')
			return false;
		}
		else if(s[i]==')'&&cnt==1||cnt==3)
		{
			cnt++;
			if(cnt==1)
			{
				if(s[i+1]!=43||s[i+1]!=45||s[i+2]!='(')
				{
					cout<<"2"<<endl;
					return false;
				}
			}
	    }
	}
	if(cnt!=4)
	{
		cout<<"4"<<endl;
		return false;
    }
	if(s[s.length()-1]!=')')
	{
		cout<<"5"<<endl;
		return false;
	}
	char op;
	for(int i=0;i<l;i++)
	{
		if(s[i]>=65&&s[i]<=90||s[i]>=97&&s[i]<=122)
		{
			if(m==0)
			{
			    m=1;
			    op=s[i];
			}
			else if(m==1&&s[i]!=op)
			{
				cout<<"6"<<endl;
				return false;
			}
		}
		if(s[i]!=43&&s[i]!=45&&s[i]<48&&s[i]>57&&s[i]<65&&s[i]>90&&s[i]<97&&s[i]>122&&s[i]!=94&&s[i]!='.')
		{
			cout<<"7"<<endl;
			return false;
		}
	}
	return true;
}


List *head; 


int main()                                   //主函数 
{
	char tn;
	bool flag=0;
	int len;
	cout<<"         A Unary Sparse Polynomial Calculator!"<<endl;
	while(1)
	{
		string s1,s2,s3;
		head=create(1);                                              //创建链表头 
		cout<<"请按照格式输入两个相加或相减的多项式"<<endl<<"两个多项式请分别用两个小括号括起来"<<endl<<"可以计算两个多项式的 加法，减法 或 乘法"<<endl; 
		cin>>s3;
		flag=0;
		flag= check(s3);                                             //检查输入的多项式的格式是否有误 
		while(flag!=true)
		{
			cout<<"输入的多项式子格式有误，请重新输入!"<<endl<<endl<<endl;
			cout<<"请按照格式输入两个相加或相减的多项式"<<endl<<"两个多项式请分别用两个小括号括起来"<<endl<<"可以计算两个多项式的 加法，减法 或 乘法"<<endl; 
			cin>>s3;
			flag=0;
			flag=check(s3);
		}
		len=s3.length();
		int st=0,s1k=0,s2k=0;
		char cal;
		for(int i=0;i<len;i++)
		{
			if(s3[i]=='('&&st==0)
			st=1;
			else if(s3[i]==')'&&st==1)
			st=2;
			else if(s3[i]=='('&&st==2)
			st=3;
			else if(s3[i]==')'&&st==3)
			st=4;
			if(st==1)
			{
				if(s3[i]!='(')
				{
					s1+=s3[i];
					s1k++;
				}
			}
			else if(st==3)
			{
				if(s3[i]!='(')
				{
					s2+=s3[i];
					s2k++;
				}
			}
			else if(st==2)
			cal=s3[i];
			else
			break;
		} 
		for(int p=0;p<len;p++)
		{
			if(s3[p]>=65&&s3[p]<=90||s3[p]>=97&&s3[p]<=122)
			{
				tn=s3[p];
				break;
			}
		}
		s1+=')';
		s2+=')';
        if(cal=='*')                                               //判断是做多项式乘法还是加减法
        {
        	head=mul_1(s1,s2,head,tn);                                 
        }
        else
        {
        	head=trans(s1,s2,cal,head,tn);
			print(head,tn);
        }
        char cho='1';
		while(cho=='1'||cho=='2'||cho=='3')
		{
			cout<<endl<<endl<<"输入 1 顺序输出多项式各个项，输入 2 提供该多项式的元的值并计算结果，输入 3 对该多项式进行求导，输入其他则进行下一次计算"<<endl;
			cin>>cho;
			if(cho=='1')
			{
				print_link(head);                                          //链式输出 
			} 
			else if(cho=='2')
			{
				int xx;
				cout<<"请输入该多项式的元的值:"<<endl;                     //求值 
				cin>>xx;
				cal_1(head,xx);
			}
			else if(cho=='3')
			{
				deri(head,tn);                                             //求导 
			}
		}
		dele(head);                                                        //释放链表 
	}
	return 0;
} 
