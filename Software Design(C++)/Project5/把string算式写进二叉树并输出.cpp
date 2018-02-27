#include <iostream>
#include <string>
using namespace std;

struct leaf{
	leaf *last,*left,*right;
	char data;
	int m;
};

void reset(leaf*);

leaf* create(string s)
{
	leaf *head,*p,*q;
	head=NULL;
	p=new leaf;
	p->last=NULL;
	p->left=NULL;
	p->right=NULL;
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
	    		p->data=s[i];
	    		p->last=q;
	    		p->left=NULL;
	    		p->right=NULL;
	    		p->m=0;
	    		q=p;
			}
		}
		else if(s[i]>='0'&&s[i]<='9')
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
		}
	}
	return head;
}

void preprint(leaf* t1)
{
	leaf *t;
	t=t1;
	t->last=NULL;
	if(t->data)
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
		    if(t->data=='+'||t->data=='-')
		    {
		    	if(t->last->data=='*'||t->last->data=='/'||t->last->data=='^')
		    	{
		    		sp=t;
		    		cout<<"(";
		    	}
		    }
		    if(t->data>='0'&&t->data<='9')
		    t->m++;
			t->m++;
			if(t->m==2)
			cout<<t->data;
		}
		else if(t->right!=NULL&&t->right->m==0)
		{
		    t=t->right;
		    if(t->data=='+'||t->data=='-')
		    {
		    	if(t->last->data=='*'||t->last->data=='/'||t->last->data=='^')
		    	{
		    		sp=t;
		    		cout<<"(";
		    	}
		    }
		    if(t->data>='0'&&t->data<='9')
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


int main()
{
	leaf *t,*t1;
	string s;
	cin>>s;
	t=create(s);
	t1=t;
    preprint(t1);
	inprint(t1);
} 
