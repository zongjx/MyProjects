#include <iostream>
#include <string>
#include <queue>
using namespace std;

string s,sc;

struct leaf{
	leaf *last,*left,*right;
	string data;
	int m,deep;
};


leaf* create(string s)
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
		}
	}
	return head;
}

void reset(leaf* t1)
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

void inprint(leaf* t1)
{
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
		    		cout<<"(";
		    	}
		    }
		    if(t->data[0]>='0'&&t->data[0]<='9')
		    t->m++;
			t->m++;
			if(t->m==2)
			cout<<t->data;
		}
		else if(t->right!=NULL&&t->right->m==0)
		{
		    t=t->right;
		    if(t->data[0]=='+'||t->data[0]=='-')
		    {
		    	if(t->last->data[0]=='*'||t->last->data[0]=='/'||t->last->data[0]=='^')
		    	{
		    		sp=t;
		    		cout<<"(";
		    	}
		    }
		    if(t->data[0]>='0'&&t->data[0]<='9')
		    t->m++;
			t->m++;
			if(t->m==2)
			cout<<t->data;
		}
		else
		{
			t=t->last;
			if(t==NULL)
			break;
			t->m++;
			if(t->m==2)
			cout<<t->data;
		}
		if(t==sp&&t->m==3)
		cout<<")";
	}
	cout<<endl;
	reset(t1);
}





int recure(int k,int b)
{
	if(k==0)
	return b;
	else
	return recure(k-1,2*b+2); 
} 

void print_tree(leaf* t1)
{
	leaf *y;
	y=t1;
	int de,k,d1,d2;
	while(y->left!=NULL)
	{
		y=y->left;
	}
	d1=y->deep;
	y=t1;
	while(y->right!=NULL)
	{
		y=y->right;
	}
	d2=y->deep;
	if(d1>d2)
	de=d1;
	else
	de=d2;
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
			if(q.front()->data[0]!=' ')
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
			if(q.front()->data[0]!=' ')
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
					if(q.front()->data[0]!=' ')
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
					if(q.front()->data[0]!=' ')
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

void preprint(leaf* t1)
{
	leaf *t;
	t=t1;
	t->last=NULL;
	if(t->data!="")
	cout<<t->data;
	t->m=1;
	while(t!=NULL)
	{
		if(t->left!=NULL&&t->left->m!=1)
		{
			t=t->left;
			cout<<t->data;
			t->m=1;
		}
		else if(t->right!=NULL&&t->right->m!=1)
		{
			t=t->right;
			cout<<t->data;
			t->m=1;
		}
		else
		{
			t=t->last;
		}
	}
	cout<<endl;
	reset(t1);
}

int main()
{
	leaf *t,*t1;
	string s;
	cin>>s;
	t=create(s);
	t1=t;
    preprint(t1);
	inprint(t1);
	print_tree(t1); 
} 
