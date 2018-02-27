#include <iostream>
#include <string>
#include <stack> 
#include <cmath>
#include <queue>
using namespace std;

string s,sc;

struct leaf{                                                                   ///////////////////////////// 
	leaf *last,*left,*right;
	string data;
	int m;
	int deep; 
};

bool checkpre(string s)                                                        ///////////////////////////// 
{
	int l,flag=0;
	l=s.length();
	int noc=0,non=0;
	for(int i=0;i<l;i++)
	{
		if(!flag)
		{
			if(s[i]=='+'||s[i]=='-'||s[i]=='*'||s[i]=='/'||s[i]=='^')
			noc++;
			else if((s[i]>='0'&&s[i]<='9')||(s[i]>='a'&&s[i]<='z'))
			non++;
			else if(s[i]=='(')
			flag=1;
		}
		else
		{
			if(s[i]==')')
			{
				flag=0;
				non++;
			}
			else if(s[i]=='+'||s[i]=='-'||s[i]=='*'||s[i]=='/'||s[i]=='^')
			{
				return false;
			}
			else if(s[i]>='a'&&s[i]<='z')
			{
				if((s[i+1]>='0'&&s[i+1]<='9')||(s[i+1]>='a'&&s[i+1]<='z')||(s[i-1]>='0'&&s[i-1]<='9')||(s[i-1]>='a'&&s[i-1]<='z'))
				return false;
			}
		}
		if(non-noc>=1&&(s[i+1]=='+'||s[i+1]=='-'||s[i+1]=='*'||s[i+1]=='/'||s[i+1]=='^'))
		return false;
	}
	if(noc-non>=2)
	return false;
	if(non-noc<1)
	return false;
	return true;
}

bool checkin(string s)                                       //检查输入的式子的格式是否有误的函数 
{
	int l = 0,bra = 0;
	l = s.length();
	for (int i = 0 ; i < l ; i++)                          //检查式子中是否有非法字符 
	{ 
		if ( (s[i] < 'a' || s[i] > 'z' ) && (s[i] < 48 || s[i] > 57) && s[i] != '(' && s[i] != ')' && s[i] != '+' && s[i] != '-' && s[i] != '*' && s[i] != '/' && s[i] != '^')
		{
			return false;
			break;
		}
	}
	for (int i = 0 ; i < l ; i++)                          //检查式子的格式是否有误 
	{
		if (s[i] == '(')
		{
			bra++;
		}
		else if (s[i] == ')')
		{
			bra--;
			if (bra < 0)
			return false;
		}
		else if (s[i] == '+' || s[i] == '-' || s[i] == '*' || s[i] == '/' || s[i] == '^')
		{
			if ( (s[i+1] < 'a' || s[i+1] > 'z' ) && (s[i+1] < 48 || s[i+1] > 57) && s[i+1] != '(')
			{
				return false;
			}
		} 
	}
	if ( (s[0] < 'a' || s[0] > 'z' ) && (s[0] < 48 || s[0] > 57) && s[0] != '(' && s[0] != '-')    //检查式子第一个字符 
	return false;                                                    
	if (bra>0)                                             //括号格式检查 
	return false;
	return true;
}

void reset(leaf*);

int deepest=0;

leaf* create(string s)                                                         ///////////////////////// 
{
	leaf *head,*p,*q;
	head=NULL;
	p=new leaf;
	p->last=NULL;
	p->left=NULL;
	p->right=NULL;
	p->deep=1;
	q=p;
	head=p;
	int l;
	l=s.length();
	for(int i=0;i<l;i++)
	{
		if(s[i]=='+'||s[i]=='-'||s[i]=='*'||s[i]=='/'||s[i]=='^')
		{
			if(i==0)
			{
				p->data=s[i];
				p->left=NULL;
				p->right=NULL;
				p->m=0;
				p->deep=1;
				if(p->deep>deepest)
	    		deepest=p->deep;
			}
			else
			{
				p=new leaf;
				while(q->left!=NULL&&q->right!=NULL)
				{
					q=q->last;
				}
				if(q->left==NULL)
				{
					q->left=p;
				}
				else
				{
					q->right=p;
				}
				p->deep=q->deep+1;
	    		p->data=s[i];
	    		p->last=q;
	    		p->left=NULL;
	    		p->right=NULL;
	    		p->m=0;
	    		p->deep=q->deep+1;
	    		q=p;
	    		if(p->deep>deepest)
	    		deepest=p->deep;
			}
		}
		else if((s[i]>='0'&&s[i]<='9')||(s[i]>='a'&&s[i]<='z'))
		{
			p=new leaf;
			while(q->left!=NULL&&q->right!=NULL)
			{
				q=q->last;
			}
			p->last=q;
			p->left=NULL;
			p->right=NULL;
			p->data=s[i];
			if(q->left==NULL)
			q->left=p;
			else if(q->left!=NULL)
			q->right=p;
			p->m=0;
			p->deep=q->deep+1;
			if(p->deep>deepest)
			deepest=p->deep;
		}
		else if(s[i]=='(')
		{
			i++;
			p=new leaf;
			while(q->left!=NULL&&q->right!=NULL)
			{
				q=q->last;
			}
			p->last=q;
			p->left=NULL;
			p->right=NULL;
			while(s[i]!=')')
			{
				p->data+=s[i];
				i++;
			}
			if(q->left==NULL)
			q->left=p;
			else if(q->left!=NULL)
			q->right=p;
			p->m=0;
			p->deep=q->deep+1;
			if(p->deep>deepest)
			deepest=p->deep;
		}
	}
	return head;
}

string inprint(leaf* t1)                                                       ///////////////////////// 
{
	string sk;
	sk="";
	leaf *sp,*t;
	t=t1; 
	t->last=NULL;
	t->m+=1;
	while(t!=NULL)
	{
		if(t->left!=NULL&&t->left->m==0)
		{
		    t=t->left;
		    if(t->data[0]=='+'||t->data[0]=='-')
		    {
		    	if(t->last->data[0]=='*'||t->last->data[0]=='/'||t->last->data[0]=='^')
		    	{
		    		sp=t;
		    		sk+="(";
		    	}
		    }
		    if((t->data[0]>='0'&&t->data[0]<='9')||(t->data[0]>='a'&&t->data[0]<='z'))
		    t->m++;
			t->m++;
			if(t->m==2)
			{
				sk+=t->data;
			}
		}
		else if(t->right!=NULL&&t->right->m==0)
		{
		    t=t->right;
		    if(t->data[0]=='+'||t->data[0]=='-')
		    {
		    	if(t->last->data[0]=='*'||t->last->data[0]=='/'||t->last->data[0]=='^')
		    	{
		    		sp=t;
		    		sk+="(";
		    	}
		    }
		    if((t->data[0]>='0'&&t->data[0]<='9')||(t->data[0]>='a'&&t->data[0]<='z'))
		    t->m++;
			t->m++;
			if(t->m==2)
			{
				sk+=t->data;
			}
		}
		else
		{
			t=t->last;
			if(t==NULL)
			break;
			t->m++;
			if(t->m==2)
			{
				sk+=t->data;
			}
		}
		if(t==sp&&t->m==3)
		{
			sk+=")";
		}
	}
	reset(t1);
	return sk;
}

void reset(leaf* t1)                                                           ///////////////////////// 
{
	leaf *t;
	t=t1;
	t->last=NULL;
	t->m=0;
	while(t!=NULL)
	{
		if(t->left!=NULL&&t->left->m!=0)
		{
			t=t->left;
			t->m=0;
		}
		else if(t->right!=NULL&&t->right->m!=0)
		{
			t=t->right;
			t->m=0;
		}
		else
		{
			t=t->last;
		}
	}
}

int recure(int k,int b)                                                        ////////////////////////// 
{
	if(k==0)
	return b;
	else
	return recure(k-1,2*b+2); 
} 

void print_tree(leaf* t1)                                                      /////////////////////////// 
{
	leaf *y;
	y=t1;
	int de,k,d1,d2;
    de=deepest;
	queue<leaf*> q;
	q.push(t1);
	int d=1;
	while(!q.empty())
	{
		k=de-q.front()->deep;
		if(k<0)
		break;
		k=recure(k,0);
		for(int i=0;i<k;i++)
		cout<<" ";
		cout<<q.front()->data;
		if(q.front()->left!=NULL)
		q.push(q.front()->left);
		else
		{
			leaf* nu=new leaf;
			nu->deep=d+1;
			nu->data=' ';
			nu->left=NULL;
			nu->right=NULL;
			if(q.front()->data[0]!=' '||q.front()->deep!=de)
			q.push(nu);
		}
		if(q.front()->right!=NULL)
		q.push(q.front()->right);
		else
		{
			leaf* nu=new leaf;
			nu->deep=d+1;
			nu->data=' ';
			nu->left=NULL;
			nu->right=NULL;
			if(q.front()->data[0]!=' '||q.front()->deep!=de)
			q.push(nu);
		}
		q.pop();
		k=2*k+3;
		while(!q.empty())
		{
			if(q.front()->deep==d)
			{
				for(int i=0;i<k;i++)
				cout<<" ";
				cout<<q.front()->data;
				if(q.front()->left!=NULL)
				q.push(q.front()->left);
				else
				{
					leaf* nu=new leaf;
					nu->deep=d+1;
					nu->data=' ';
					nu->left=NULL;
					nu->right=NULL;
					if(q.front()->data[0]!=' '||q.front()->deep!=de)
					q.push(nu);
				}
				if(q.front()->right!=NULL)
				q.push(q.front()->right);
				else
				{
					leaf* nu=new leaf;
					nu->deep=d+1;
					nu->data=' ';
					nu->left=NULL;
					nu->right=NULL;
					if(q.front()->data[0]!=' '||q.front()->deep!=de)
					q.push(nu);
				}
				q.pop();
			}
			else
			{
				break;
			}
			
		}
		cout<<endl;
		d++;
	}
	cout<<endl;
}

leaf* ReadExpr(string s)                                                                 //Input character sequence as prefix expression E. 
{
	leaf *head;
	head=create(s);
	return head;
} 

string WriteExpr(leaf *k)                                                                 //Output E as infix expression.
{
    return inprint(k);
}

void Assign(char v,char c='0')                                                            //Assign value c to variable V, which has a default value of 0.
{
	int l;
	l=s.length();
	for(int i=0;i<l;i++)
	{
		if(s[i]==v)
		s[i]=c;
	}
	ReadExpr(s);
}

string Value(string st)                                                                     //Calculate the arithmetic result of expression E.
{
    string ccc;
	if(checkin(st)==true)
	{	
		int l = 0,cnt = 0;
		int front = -1, back = 0, p = -1;
		double c = 0,t = 1;
		double e1 = 0,e2 = 0,ex = 0,res = 0; 
		stack <char> sc;
		stack <double> sd;
		sc.push('#');
		string s = st;
		l = s.length();
		s += '#';
		while (cnt <= l)                                       //遍历 
		{
			c = 0;
			t = 1;
			e1 = 0;
			e2 = 0;
			ex = 0;
			if (s[cnt] < 48 || s[cnt] > 57)                    //遍历到数字的情况 
			{
				
			}
			if (s[cnt] == '.')                                 //遍历到小数点的情况
			{
				p = cnt;
		    }
			if (s[cnt] == '(')                                 //遍历到左括号的情况 
			{
				front = cnt;
				sc.push('(');
			}
			if (s[cnt] == '+')                                 //遍历到加号的情况 
			{
				back = cnt - 1;
				if (p == -1)
				{
					for (int i = 0 ; i < back - front - 1; i++)
					{
						t *= 10;
					}
				}
				else
				{
					for (int i = 0 ; i < p - front - 2; i++)
					{
						t *= 10;
					}
				}
				for (int i = front + 1 ; i <= back ; i++)
				{
					if(i != p)
					{
						c += (s[i] - '0') * t;
				    	t /= 10; 
					}
				}
				if (s[cnt-1] == ')')
				{
					
				}
				else
				{
			    	sd.push(c);				
		    	}
				if (sc.top() == '(' || sc.top() == '#')
				{
					sc.push('+');
				}
				else if (sc.top() == '+' || sc.top() == '-' || sc.top() == '*' || sc.top() == '/' || sc.top() == ')' || sc.top() == '^')
				{
					while (sc.top() == '+' || sc.top() == '-' || sc.top() == '*' || sc.top() == '/' || sc.top() == ')' || sc.top() == '^')
					{
						e2 = sd.top();
						sd.pop();
						e1 = sd.top();
						sd.pop();
						if (sc.top() == '+')
						{
							sd.push(e1 + e2);
						}
						else if (sc.top() == '-')
						{
							sd.push(e1 - e2);
						}
						else if (sc.top() == '*')
						{
							sd.push(e1 * e2);
						}
						else if (sc.top() == '/')
						{
							sd.push(e1 / e2);
						}
						else if (sc.top() == '^')
						{
							ex = pow(e1 , e2);
							sd.push(ex);
						}
						sc.pop();
					}
					sc.push('+');
				}
				front = cnt;
				p = -1;
			}
			if (s[cnt] == '-')                            //遍历到减号的情况 
			{
				back = cnt - 1;
				if (p == -1)
				{
					for (int i = 0 ; i < back - front - 1; i++)
					{
						t *= 10;
					}
				}
				else
				{
					for (int i = 0 ; i < p - front - 2; i++)
					{
						t *= 10;
					}
				}
				for (int i = front + 1 ; i <= back ; i++)
				{
					if(i != p)
					{
						c += (s[i] - '0') * t;
				    	t /= 10; 
					}
				}
				if (s[cnt-1] == ')')
				{
					
				}
				else
				{
			    	sd.push(c);				
		    	}
				if (sc.top() == '(' || sc.top() == '#')
				{
					sc.push('-');
				}
				else if (sc.top() == '+' || sc.top() == '-' || sc.top() == '*' || sc.top() == '/' || sc.top() == ')' || sc.top() == '^')
				{
					while (sc.top() == '+' || sc.top() == '-' || sc.top() == '*' || sc.top() == '/' || sc.top() == ')' || sc.top() == '^')
					{
						e2 = sd.top();
						sd.pop();
						e1 = sd.top();
						sd.pop();
						if (sc.top() == '+')
						{
							sd.push(e1 + e2);
						}
						else if (sc.top() == '-')
						{
							sd.push(e1 - e2);
						}
						else if (sc.top() == '*')
						{
							sd.push(e1 * e2);
						}
						else if (sc.top() == '/')
						{
							sd.push(e1 / e2);
						}
						else if (sc.top() == '^')
						{
							ex = pow(e1 , e2);
							sd.push(ex);
						}
						sc.pop();
					}
					sc.push('-');
				}
				front = cnt;
				p = -1;
			}
		    if (s[cnt] == '*')                            //遍历到乘号的情况 
			{
				back = cnt - 1;
				if (p == -1)
				{
					for (int i = 0 ; i < back - front - 1; i++)
					{
						t *= 10;
					}
				}
				else
				{
					for (int i = 0 ; i < p - front - 2; i++)
					{
						t *= 10;
					}
				}
				for (int i = front + 1 ; i <= back ; i++)
				{
					if(i != p)
					{
						c += (s[i] - '0') * t;
				    	t /= 10; 
					} 
				}
				if (s[cnt-1] == ')')
				{
					
				}
				else
				{
			    	sd.push(c);				
		    	}
				if (sc.top() == '(' || sc.top() == '#' || sc.top() == '+' || sc.top() == '-')
				{
					sc.push('*');
				}
				else if (sc.top() == '*' || sc.top() == '/' || sc.top() == ')' || sc.top() == '^')
				{
					while (sc.top() == '*' || sc.top() == '/' || sc.top() == ')' || sc.top() == '^')
					{
						e2 = sd.top();
						sd.pop();
						e1 = sd.top();
						sd.pop();
						if (sc.top() == '*')
						{
							sd.push(e1 * e2);
						}
						else if (sc.top() == '/')
						{
							sd.push(e1 / e2);
						}
						else if (sc.top() == '^')
						{
					    	ex = pow(e1 , e2);
							sd.push(ex);
						}
						sc.pop();
					}
					sc.push('*');
				}
				front = cnt;
				p = -1;
			}
			if (s[cnt] == '/')                            //遍历到除号的情况 
			{
				back = cnt - 1;
				if (p == -1)
				{
					for (int i = 0 ; i < back - front - 1; i++)
					{
						t *= 10;
					}
				}
				else
				{
					for (int i = 0 ; i < p - front - 2; i++)
					{
						t *= 10;
					}
				}
				for (int i = front + 1 ; i <= back ; i++)
				{
					if(i != p)
					{
						c += (s[i] - '0') * t;
				    	t /= 10; 
					}
				}
				if (s[cnt-1] == ')')
				{
					
				}
				else
				{
			    	sd.push(c);				
		    	}
				if (sc.top() == '(' || sc.top() == '#' || sc.top() == '+' || sc.top() == '-')
				{
					sc.push('/');
				}
				else if (sc.top() == '*' || sc.top() == '/' || sc.top() == ')' || sc.top() == '^')
				{
					while (sc.top() == '*' || sc.top() == '/' || sc.top() == ')' || sc.top() == '^')
					{
						e2 = sd.top();
						sd.pop();
						e1 = sd.top();
						sd.pop();
						if (sc.top() == '*')
						{
							sd.push(e1 * e2);
						}
						else if (sc.top() == '/')
						{
							sd.push(e1 / e2);
						}
						else if (sc.top() == '^')
						{
							ex = pow(e1 , e2);
							sd.push(ex);
						}
						sc.pop();
					}
					sc.push('/');
				}
				front = cnt;
				p = -1;
			}
			if (s[cnt] == ')')                            //遍历到右括号的情况 
			{
				back = cnt - 1;
				if (p == -1)
				{
					for (int i = 0 ; i < back - front - 1; i++)
					{
						t *= 10;
					}
				}
				else
				{
					for (int i = 0 ; i < p - front - 2; i++)
					{
						t *= 10;
					}
				}
				for (int i = front + 1 ; i <= back ; i++)
				{
					if(i != p)
					{
						c += (s[i] - '0') * t;
				    	t /= 10; 
					} 
				}
				if (s[cnt-1] == ')')
				{
					
				}
				else
				{
			    	sd.push(c);				
		    	}
				if (sc.top() == '(' || sc.top() == '#' || sc.top() == '+' || sc.top() == '-' || sc.top() == '*' || sc.top() == '/' || sc.top() == ')' || sc.top() == '^')
				{
					while (sc.top() == '#' || sc.top() == '+' || sc.top() == '-' || sc.top() == '*' || sc.top() == '/' || sc.top() == ')' || sc.top() == '^')
					{
						e2 = sd.top();
						sd.pop();
						e1 = sd.top();
						sd.pop();
						if (sc.top() == '+')
						{
							sd.push(e1 + e2);
						}
						else if (sc.top() == '-')
						{
							sd.push(e1 - e2);
						}
						else if (sc.top() == '*')
						{
							sd.push(e1 * e2);
						}
						else if (sc.top() == '/')
						{
							sd.push(e1 / e2);
						}
						else if (sc.top() == '^')
						{
							ex = pow(e1 , e2);
							sd.push(ex);
						}
						else if (sc.top() == '(')
						{
							
						} 
						sc.pop();
					}
					if(sc.top() == '(')
					sc.pop();
				}
				front = cnt;
				p = -1;
			}
			if (s[cnt] == '^')                            //遍历到乘方号的情况 
			{
				back = cnt - 1;
				if (p == -1)
				{
					for (int i = 0 ; i < back - front - 1; i++)
					{
						t *= 10;
					}
				}
				else
				{
					for (int i = 0 ; i < p - front - 2; i++)
					{
						t *= 10;
					}
				}
				for (int i = front + 1 ; i <= back ; i++)
				{
					if(i != p)
					{
						c += (s[i] - '0') * t;
				    	t /= 10; 
					}
				}
				if (s[cnt-1] == ')')
				{
					
				}
				else
				{
			    	sd.push(c);				
		    	}
				if (sc.top() == '+' || sc.top() == '-' || sc.top() == '*' || sc.top() == '/' || sc.top() == '(' || sc.top() == '#' || sc.top() == '^')
				{
					sc.push('^');
				}
				else if (sc.top() == ')')
				{
					while (sc.top() == ')')
					{
						sc.pop();
					}
					sc.push('^');
				}
				front = cnt;
				p = -1;
			}
			if (s[cnt] == '#')                            //遍历到井号的情况 
			{
				back = cnt - 1;
				if (p == -1)
				{
					for (int i = 0 ; i < back - front - 1; i++)
					{
						t *= 10;
					}
				}
				else
				{
					for (int i = 0 ; i < p - front - 2; i++)
					{
						t *= 10;
					}
				}
				for (int i = front + 1 ; i <= back ; i++)
				{
					if(i != p)
					{
						c += (s[i] - '0') * t;
				    	t /= 10; 
					}
				}
				if (s[cnt-1] == ')')
				{
					
				}
				else
				{
			    	sd.push(c);				
		    	}
				if(sc.top() == '+' || sc.top() == '-' || sc.top() == '*' || sc.top() == '/' || sc.top() == '(' || sc.top() == '^' || sc.top() == ')')
				{
					while (sc.top() == '+' || sc.top() == '-' || sc.top() == '*' || sc.top() == '/' || sc.top() == '(' || sc.top() == '^' || sc.top() == ')')
					{
						e2 = sd.top();
						sd.pop();
						e1 = sd.top();
						sd.pop();
						if (sc.top() == '+')
						{
							sd.push(e1 + e2);
						}
						else if (sc.top() == '-')
						{
							sd.push(e1 - e2);
						}
						else if (sc.top() == '*')
						{
							sd.push(e1 * e2);
						}
						else if (sc.top() == '/')
						{
							sd.push(e1 / e2);
						}
						else if (sc.top() == '^')
						{
							ex = pow(e1 , e2);
							sd.push(ex);
					    }
						sc.pop();
					}
				}
				else if(sc.top() == '#')
				{
					sc.pop();
				}
				p = -1;
			}
			cnt++;
		}
//		cout << sd.top() << endl;
		bool minus=0;
		int lep=sd.top();
		if(lep<0)
		{
			lep*=-1;
			minus=1;
		} 
		while(lep>0)
		{
			char rt;
			rt='0'+lep%10;
		    ccc.insert(0,1,rt);
		    lep/=10;
		}
		if(minus)
    	ccc="-"+ccc;
	}
	if(ccc=="")
	ccc="0";
	return ccc;
}

string CompoundExpr(char oper,string s1,string s2)                                                                      //Return a compound expression (E1)P(E2). P is an operator.
{
	string s; 
	s="("+s1+")"+oper+"("+s2+")";
	return s;
}

string MergeConst(string);

string Diff(string st,char v)                                                                              //Find the partial derivative of function E with respect to variable V.
{
	string s,sm,se;
	s=MergeConst(st); 
	int l;
	l=s.length();
	for(int i=0;i<l;i++)
	{
	    if((s[i]=='+'||s[i]=='-')&&sm!="")
	    sm+=s[i];
		if(s[i]==v)
		{
			if(s[i-1]=='*')
			{
				se="";
				int f;
				for(int k=i-1;k>=0;k--)
				{
					if(s[k-1]=='+'||s[k-1]=='-'||k==0)
					{
						f=k;
						break;
					}
				}
				for(int k=f;k<i-1;k++)
				{
					se+=s[k];
				}
				if(s[i+1]=='^'&&s[i+2]!='0')
				{
					se+='*';
					for(int k=i+2;k<l;k++)
					{
						if(!(s[k]>='0'&&s[k]<='9')&&!(s[k]>='a'&&s[k]<='z')&&!(s[k]=='*'||s[k]=='/'||s[k]=='^'))
						break;
						else
						{
							se+=s[k];
						}
					} 
					for(int k=i-1;k<l;k++)
					{
						if(!(s[k]>='0'&&s[k]<='9'))
						se+=s[k];
						else
						{
							se+=char(s[k]-1);
							break;
						}
					}
				}
				else if(s[i+1]=='*'||s[i+1]=='/')
				{
					int ti=0;
					for(int k=i;k<l;k++)
					{
						if(s[k]=='+'||s[k]=='-')
						break;
						else if(s[k]>='a'&&s[k]<='z'&&s[k]!=v)
						{
							se+=s[k-1];
							se+=s[k];
						}
						if(s[k]=='*'&&s[k+1]==v)
						ti++;
						else if(s[k]=='/'&&s[k+1]==v)
						ti--;
					}
					if(ti>=0)
					{
						se+='*';
						se+=char('0'+ti+1);
						se+='*';
						se+=v;
						se+='^';
						se+=char('0'+ti); 
					}
					else if(ti<0)
					{
						ti*=-1;
						se+='*';
						se+="(-";
						se+=char('0'+ti-1);
						se+=")*";
						se+=v;
						se+="^(-";
						se+=char('0'+ti);
						se+=')'; 
					}
				}
				sm+=se;
				se="";
				for(i;i<l;i++)
				{
					if(s[i]=='+'||s[i]=='-')
					{
						i--;
						break;
					}
				}
			}
			else if(s[i-1]=='/')
			{
				se="";
				int f;
				for(int k=i;k>0;k--)
				{
					if(s[k-1]=='+'||s[k-1]=='-'||k==0)
					{
						f=k;
						break;
					}
				}
				for(int k=f;k<i-1;k++)
				{
					se+=s[k];
				}
				if(s[i-1]=='*'||s[i-1]=='/')
				{
					int ti=0;
					for(int k=i;k<l;k++)
					{
						if(s[k]=='+'||s[k]=='-')
						break;
						else if(s[k]>='a'&&s[k]<='z'&&s[k]!=v)
						{
							se+=s[k-1];
							se+=s[k];
						}
						if(s[k]=='*'&&s[k+1]==v)
						ti++;
						else if(s[k]=='/'&&s[k+1]==v)
						ti--;
					}
					if(ti>0)
					{
						se+='*';
						se+=char('1'+ti);
						se+='*';
						se+=v;
						se+='^';
						se+=char('1'+ti-1); 
					}
					else if(ti<0)
					{
						ti*=-1;
						se+='*';
						se+="(-";
						se+=char('1'+ti);
						se+=")*";
						se+=v;
						se+="^(-";
						se+=char('1'+ti+1);
						se+=')'; 
					}
					else if(ti==0)
					{
						se+="/(";
						se+=v;
						se+="^";
						if(s[i+1]=='^')
						{
							se+=char(s[i+2]+1);
							se+=")*(-1)";
						}
						else
						se+="2)*(-1)";
					}
				}
				else if(s[i+1]=='^'&&s[i+2]!='0')
				{
					se+="*(-";
					for(int k=i+2;k<l;k++)
					{
						if(!(s[k]>='0'&&s[k]<='9')&&!(s[k]>='a'&&s[k]<='z')&&!(s[k]=='*'||s[k]=='/'||s[k]=='^'))
						break;
						else
						{
							se+=s[k];
						}
					}
					se+=')'; 
					for(int k=i-1;k<l;k++)
					{
						if(!(s[k]>='0'&&s[k]<='9'))
						se+=s[k];
						else
						{
							se+=char(s[k]-1);
							break;
						}
					}
				}
				sm+=se;
				se=""; 
				for(i;i<l;i++)
				{
					if(s[i]=='+'||s[i]=='-')
					{
						i--;
						break;
					}
				}
			}
			else
			{
				if(s[i+1]=='*')
				{
					for(int k=i+2;k<l;k++)
					{
						if(!(s[k]>='0'&&s[k]<='9')&&!(s[k]>='a'&&s[k]<='z')&&!(s[k]=='*'||s[k]=='/'||s[k]=='^'))
						break;
						else 
						se+=s[k];
					}
				}
				else if(s[i+1]=='/')
				{
					se+='1';
					se+='/';
					for(int k=i+2;k<l;k++)
					{
						if(!(s[k]>='0'&&s[k]<='9')&&!(s[k]>='a'&&s[k]<='z')&&!(s[k]=='*'||s[k]=='/'||s[k]=='^'))
						break;
						else 
						se+=s[k];
					}
				} 
				else if(s[i+1]=='^'&&s[i+2]!='0')
				{
					for(int k=i+2;k<l;k++)
					{
						if(!(s[k]>='0'&&s[k]<='9')&&!(s[k]>='a'&&s[k]<='z')&&!(s[k]=='*'||s[k]=='/'||s[k]=='^'))
						break;
						else
						{
							se+=s[k];
						}
					} 
					se+='*';
					for(int k=i;k<l;k++)
					{
						if(!(s[k]>='0'&&s[k]<='9'))
						se+=s[k];
						else
						{
							se+=char(s[k]-1);
							break;
						}
					}
				}
				else
				{
					se+='1';
				}
				for(i;i<l;i++)
				{
					if(s[i]=='+'||s[i]=='-')
					{
						i--;
						break;
					}
				}
				sm+=se;
				se="";
			}
		}
	}
	while(sm[sm.length()-1]=='+'||sm[sm.length()-1]=='-'||sm[sm.length()-1]=='*'||sm[sm.length()-1]=='/'||sm[sm.length()-1]=='^')
	sm.erase(sm.length()-1,1); 
	return sm;
}

string merge2(string st)
{
	bool p=0,bra=0;
	int l,b=0;
	string s=st;
	l=st.length();
	for(int i=0;i<l;i++)
	{
		if((st[i]>='0'&&st[i]<='9'))
		{
			p=1; 
		}
		if(st[i]=='^')
		{
			p=0;
			break;
		}
	}
	if(p)
	{
		string sa,saa,sb,sc,sf,sk;
        for(int i=0;i<l;i++)
        {
        	if(s[i]=='(')
        	{
        		if(Value(sk)!="0")
        		sa+=Value(sk);
        		sa+=sb;
        		sb="";
        		if(i!=0)
        		sa+=s[i-1];
				sa+='(';
        		b++;
        	}
        	if(b==2)
        	return "!";
        	if(b==0)
        	{
        		if(s[i]>='a'&&s[i]<='z')
        		{
        			sk+='1';
        			if(i!=0)
        			sb+=s[i-1];
        			else
        			sb+='*';
        			sb+=s[i];
        		}
        		else 
				{
        			sk+=s[i];
				}
        	}
        	else if(b==1)
        	{
        		if(s[i]>='a'&&s[i]<='z')
        		{
        			if(s[i-1]=='^')
        			return "!";
        			else if(s[i-1]=='(')
        			{
        				if(s[i+1]=='+'||s[i+1]=='-')
        				saa+='0';
        				else
        				saa+='1';
        				sf+=s[i];
        			}
					else if(s[i-1]=='+'||s[i-1]=='-')
        			{
        				saa+='0';
        				sc+=s[i-1];
        				sc+=s[i];
        			}
        			else if(s[i-1]=='*'||s[i-1]=='/')
        			{
        				saa+='1';
        				if(sc=="")
        				sc+=s[i-1];
        				sc+=s[i];
        			}
        		}
        		else
        		{
        			saa+=s[i];
        		}
        	}
        	if(s[i]==')')
        	{
        		b--;
        		sa+=sf;
        		if(sf!=""&&Value(saa)[0]!='-')
        		sa+='+';
        		sa+=Value(saa);
        		sa+=sc;
        		sa+=')';
        		sc=""; 
        		saa="";
        	}
        }
        if(sa=="")
        {
        	sa=Value(sk);
        }
        sa+=sb;
        s=sa;
	}
	else 
	return st;
	return s;
}

string MergeConst(string st)                                                                        //Merge all the constants within the expression E. For instance,  E = (2+3-a)*(b+3*4) would return E = (5-a)*(b+12).
{
	int bra=0;
	int l,bb=0;
	string s=st,s1="",s2="";
	l=s.length();
	for(int i=0;i<l;i++)
	if(st[i]=='/')
	return st; 
	for(int i=0;i<l;i++)
	{
		bb=0;
		if(s[i]=='(')
		{
			int k;
		    for(k=i;k<l;k++)
		    {
		    	if(s[k]=='(')
		    	bb++;
		    	else if(s[k]==')'&&bb!=0)
		    	bb--;
		    	if(s[k]==')'&&bb==0)
		    	{
		    		if((s[k+1]=='+'||s[k+1]=='-'||s[k+1]==')'||k==l-1)&&(s[i-1]=='+'||s[i-1]=='-'||s[i-1]=='('||i==0))
		    		{
		    			if(s[i-1]=='-')
		    			for(int p=i;p<k;p++)
		    			{
		    				if(s[p]=='+')
		    				s[p]='-';
		    				else if(s[p]=='-')
		    				s[p]='+';
		    			}
		    			s.erase(k,1);
		    			s.erase(i,1);
		    			i--;
		    			l=s.length();
		    		}
		    		break;
		    	}
		    }
		}
	}                                                                               
	l=s.length();
	for(int i=0;i<l;i++)
	{
		bool noc=0;
		int j;
		string te;
		if((s[i]>='0'&&s[i]<='9')||(s[i]>='a'&&s[i]<='z'))
		{
			if(i==0||s[i-1]=='+'||s[i-1]=='-')
			{
				noc=0;
				int nob=0;
				if(i!=0)
				te+=s[i-1];
				for(j=i;j<l;j++)
				{
					if(s[j]>='a'&&s[j]<='z')
					noc=1;
					if((s[j]=='+'||s[j]=='-')&&nob==0)
					break;
					else
					te+=s[j];
					if(s[j]=='(')
					nob++;
					else if(s[j]==')')
					nob--;
				}
			    if(noc)
			    s2+=te;
			    else
			    s1+=te;
			}
			else if(s[i-1]=='(')
			{
				noc=0;
				int nob=1;
				if(i==1)
				{
					te+=s[i-1];
				}
				else
				{
					te+=s[i-2];
					te+=s[i-1];
				}
				for(j=i;j<l;j++)
				{
					if(s[j]>='a'&&s[j]<='z')
					noc=1;
					if((s[j]=='+'||s[j]=='-')&&nob==0)
					break;
					else
					te+=s[j];
					if(s[j]=='(')
					nob++;
					else if(s[j]==')')
					nob--;
				}
				if(noc)
			    s2+=te;
			    else
			    s1+=te;
			}
			i=j;
		}
	}
	string sf,s3="";
	if(s2[0]=='+')
	s2.erase(0,1);
	s1=Value(s1);
	sf+=s1;
	l=s2.length();
	for(int i=0;i<l;i++)
	{
		int j;
		if(s2[0]=='-'&&i==0)
		{
			i++;
			s3+='-';
		}
		string te="";
		if(i!=0)
		{
			s3+=s2[i];
			i++;
			for(j=i;j<l;j++)
			{
				if(s2[j]=='(')
				{
				    int k,nob1=1;
					string tr="";
					for(k=j;k<l;k++)
					{
						if(s2[k]=='(')
						nob1++; 
						if(s2[k]==')')
						nob1--;
						if(nob1==0&&s2[k]==')')
						{
							tr+=s2[k];
							break;
						}
						tr+=s2[k];
					}
					i=k;
					j=k;
					if(tr[0]!='(')
					te+="("+tr+")";
					else
					te+=tr;
				}
				if(s2[j]=='+'||s2[j]=='-')
				{
					i=j-1;
					break;
				}
				else
				te+=s2[j];
			}
			i=j-1;
			te=merge2(te);
			s3+=te;
		}
		else
		{
			for(j=i;j<l;j++)
			{
				if(s2[j]=='(')
				{
				    int k,nob1=1;
					string tr="";
					for(k=j;k<l;k++)
					{
						if(s2[k]=='(')
						nob1++; 
						if(s2[k]==')')
						nob1--;
						if(nob1==0&&s2[k]==')')
						{
							tr+=s2[k];
							break;
						}
						tr+=s2[k];
					}
					i=k;
					j=k;
					if(tr[0]!='(')
					te+="("+tr+")";
					else 
					te+=tr;
				}
				if(s2[j]=='+'||s2[j]=='-')
				{
					i=j-1;
					break;
				}
				else
				te+=s2[j];
			}
			i=j-1;
			te=merge2(te);
			s3+=te;
		}
	}
	s2=s3;
	if(s2[0]=='-')
	sf+=s2;
	else
	{
		if(sf[0]=='0'&&sf.length()==1)
		sf="";
		if(sf!=""&&s3!="")
		sf+='+';
		sf+=s2;
	}
	return sf;	
}



int main()                                                                               //Main function.
{
	cout<<"**************************************************************************"<<endl;
	cout<<"*                                                                        *"<<endl;
	cout<<"*                                                                        *"<<endl;
	cout<<"*                               计算器                                   *"<<endl;
	cout<<"*                                                                        *"<<endl;
	cout<<"*                                                                        *"<<endl; 
	cout<<"**************************************************************************"<<endl;
	cout<<endl<<endl<<"使用说明：请输入前缀表达式，允许输入的字符有   数字 0~9   小写字母 a~z   运算符号 + - * / ^   "<<endl;
	bool check1=0;
	while(1)
	{
		cout<<endl<<endl<<endl;
		check1=0;
		while(!check1)
		{
			cout<<endl; 
			check1=1;
			cout<<"请输入前缀表达式：   ";
			cin>>s;
			if(checkpre(s))
			{
				
			}
			else
			{
				cout<<"输入的式子格式有误，请重新输入！"<<endl;
				check1=0;
			}
		}
		
		leaf *h;
	    h=ReadExpr(s);
	    sc=WriteExpr(h);
	    
	    char cho='0';
	    int con=0,l,alf;
	    l=sc.length();    	
		cout<<"表达式:   "<<s<<endl<<endl;
		cout<<"二叉树图："<<endl<<endl;
		print_tree(h); 
	    while(!con)
	    {
	    	alf=0;
	    	cout<<endl<<endl;
	    	l=sc.length();
	    	cout<<"输入 1 输出中缀表达式  "<<endl;
	    	for(int i=0;i<l;i++)
	    	{
		    	if(sc[i]>='a'&&sc[i]<='z')
		    	{
		    		alf=1;
		    		break;
		    	}
		    	else
		    	{
		    		alf=0;
		    	}
	    	}
	    	if(alf==0)
	    	{
	    		cout<<"输入 2 输出计算结果  "<<endl<<"输入 3 把两个多项式进行运算  "<<endl<<"输入其他结束本次计算"<<endl;
	    		cin>>cho;
				if(cho=='1')
				{
					cout<<endl;
					cout<<"中缀表达式:"<<sc<<endl<<endl;
				}
				else if(cho=='2')
				{
					cout<<endl<<"计算结果:";
					cout<<Value(sc);
					cout<<endl<<endl;
				}
				else if(cho=='3')
				{
					string s2;
					char op;
					cout<<"请输入要进行的运算的运算符号(+,-,*,/,^): ";
					cin>>op;
					while(op!='+'&&op!='-'&&op!='*'&&op!='/'&&op!='^')
					{
						cout<<"输入的符号有误，请重新输入！"<<endl;
						cout<<"请输入要进行的运算的运算符号(+,-,*,/,^): ";
				    	cin>>op;
					} 
					char op2;
					cout<<"请确定第二个多项式的格式: 输入 1 则输入的格式为中缀 ，输入其他则输入的格式为前缀"<<endl;
					cin>>op2; 
					cout<<"请输入第二个多项式: ";
					cin>>s2;
					if(op2=='1')
					{
						while(!checkin(s2))
						{
							cout<<"输入的多项式格式有误，请重新输入!"<<endl;
							cout<<"请输入第二个多项式: ";
					    	cin>>s2;
						}
						sc=CompoundExpr(op,sc,s2);
					}
					else
					{
						while(!checkpre(s2))
						{
							cout<<"输入的多项式格式有误，请重新输入!"<<endl;
							cout<<"请输入第二个多项式: ";
					    	cin>>s2;
						}
						s2=WriteExpr(ReadExpr(s2));	
						sc=CompoundExpr(op,sc,s2);
					}
					cout<<"合并后:  "<<sc<<endl<<endl; 
				}
				else 
				{
					con=1; 
				}
	    	}
	    	else if(alf==1)
	    	{
	    		cout<<"输入 2 给表达式中的元赋值  "<<endl<<"输入 3 把两个多项式进行运算  "<<endl<<"输入 4 对多项式中的一个变元求偏导  "<<endl<<"输入 5 合并多项式中的常数项  "<<endl<<"输入其他结束本次计算"<<endl;
				cin>>cho;
				if(cho=='1')
				{
					cout<<endl;
					cout<<"中缀表达式:"<<sc<<endl<<endl;
				}
				else if(cho=='2')
				{
					int lsnum,ll;
					bool m=0,n=0;
					string snum;
					char nukn;
					cout<<"请输入要替换的变元(a~z): ";
					cin>>nukn;
					for(int i=0;i<l;i++)
					{
						if(sc[i]==nukn&&(sc[i]>='a'&&sc[i]<='z'))
						{
							m=1;
							break;
						}
					}
					while(!m)
					{
						m=0;
						cout<<"输入的数据有误，请重新输入！"<<endl;
						cin>>nukn;
						for(int i=0;i<l;i++)
						{
							if(sc[i]==nukn&&(sc[i]>='a'&&sc[i]<='z'))
							{
								m=1;
								break;
							}
						}	
					}
					cout<<"请输入要替换该变元的值: ";
					cin>>snum;
					lsnum=snum.length();
					for(int i=0;i<lsnum;i++)
					{
						if(snum[i]<'0'||snum[i]>'9')
						{
							n=1;
							break;
						}
					}
					while(n)
					{
						n=0;
						cout<<"输入的数据有误，请重新输入！"<<endl;
						cin>>snum;
						lsnum=snum.length();
						for(int i=0;i<lsnum;i++)
						{
							if(snum[i]<'0'||snum[i]>'9')
							{
								n=1;
								break;
	
							}
						}
					}
					ll=sc.length();
					for(int i=0;i<ll;i++)
					{
						if(sc[i]==nukn)
						{
							sc.replace(i,1,snum);
						}
						if(s[i]==nukn)
						{
							s.replace(i,1,snum);
						}
					}
				}
				else if(cho=='3')
				{
					string s2;
					char op;
					cout<<"请输入要进行的运算的运算符号(+,-,*,/,^): ";
					cin>>op;
					while(op!='+'&&op!='-'&&op!='*'&&op!='/'&&op!='^')
					{
						cout<<"输入的符号有误，请重新输入！"<<endl;
						cout<<"请输入要进行的运算的运算符号(+,-,*,/,^): ";
				    	cin>>op;
					} 
					char op2;
					cout<<"请确定第二个多项式的格式: 输入 1 则输入的格式为中缀 ，输入其他则输入的格式为前缀"<<endl;
					cin>>op2; 
					cout<<"请输入第二个多项式: ";
					cin>>s2;
					if(op2=='1')
					{
						while(!checkin(s2))
						{
							cout<<"输入的多项式格式有误，请重新输入!"<<endl;
							cout<<"请输入第二个多项式: ";
					    	cin>>s2;
						}
						sc=CompoundExpr(op,sc,s2);
					}
					else
					{
						while(!checkpre(s2))
						{
							cout<<"输入的多项式格式有误，请重新输入!"<<endl;
							cout<<"请输入第二个多项式: ";
					    	cin>>s2;
						}
						s2=WriteExpr(ReadExpr(s2));	
						sc=CompoundExpr(op,sc,s2);
					}
					cout<<"合并后:  "<<sc<<endl<<endl;
				}
				else if(cho=='4')
				{
					char v;
					bool j=0;
					cout<<"请输入要求偏导的变元:"<<endl;
					cin>>v;
					for(int i=0;i<sc.length();i++)
					{
						if(sc[i]==v)
						{
							j=1;
							break;
						}
					}
					if(!j)
					{
						j=0;
						cout<<"输入的变元有误，请重新输入！";
						cout<<"请输入要求偏导的变元:"<<endl;
						cin>>v;
						for(int i=0;i<sc.length();i++)
						{
							if(sc[i]==v)
							{
								j=1;
								break;
							}
						}
					}
					if(checkin(Diff(sc,v))) 
					{
						cout<<endl<<endl<<Diff(sc,v)<<endl<<endl;
						char rep;
						cout<<"输入 1 用此结果替换原式，输入其他则不进行操作"<<endl;
						cin>>rep;
						if(rep=='1')
						sc=Diff(sc,v);
					}
					else
					cout<<endl<<endl<<"求偏导失败"<<endl<<endl;
				}
				else if(cho=='5')
				{
					bool mc1=0;
					string smc;
					smc=MergeConst(sc);
					for(int i=0;i<smc.length();i++)
					{
						if(smc[i]=='!')
						{
							mc1=1;
							break;
						}
					}
					if(!mc1)
					{
						cout<<endl<<smc<<endl<<endl;
						char rep;
						cout<<"输入 1 用此结果替换原式，输入其他则不进行操作"<<endl;
						cin>>rep;
						if(rep=='1')
						sc=smc;
					}
					else
					cout<<"这个好难，我不会。"<<endl;
				}
				else
				{
					con=1;
				}
	    	}
	    }
	}
	return 0;
}
