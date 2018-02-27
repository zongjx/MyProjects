#include <iostream>
#include <string>
#include <queue>
#include <stack>
using namespace std;

int mat[50][50]; 

struct es;

struct e{
	int mark,length,last;
	int lv,nv;
	e *e1,*e2;
	e()
	{
		last=0;
		length=0;
		mark=0;
		lv=0;
		nv=0;
		e1=NULL;
		e2=NULL;
	}
};

struct v{
	string data;
	int label;
	e *edge;
	es *edge1; 
	v()
	{
		data="";
		label=-1;
		edge=NULL;
		edge1=NULL;
	} 
};

struct es{
	int vex;
	es *next;
	es()
	{
		vex=-1;
		next=NULL;
	}
};


struct node{
	int visit;
	int label;
	string data;
	node *last;
	node *child;
	node *cousin;
	int depth;
	node()
	{
		visit=0;
		label=-1;
		data="";
		last=NULL;
		child=NULL;
		cousin=NULL;
		depth=0;
	}
};


node* dfs(int nov,v vec[],int start)
{
	
	int visit[nov];
	for(int i=0;i<nov;i++)
	visit[i]=0;
	stack<node*> s;
	stack<int> st;
	cout<<vec[start].data<<"              "<<vec[vec[start].edge->lv].data<<"------>"<<vec[vec[start].edge->nv].data<<"  权值:"<<mat[vec[start].edge->lv][vec[start].edge->nv]<<endl;
	node *p,*h,*q;
	p=new node;
	p->last=NULL;
	p->cousin=NULL;
	p->data=vec[start].data;
	p->label=1;
	h=p;
	s.push(h);
	st.push(start);
	visit[start]=1;
	while(!st.empty())
	{
		bool mark=0;
		int m=st.top();
		e *te=vec[m].edge;
		while(te!=NULL)
		{
			if(visit[te->nv]==0)
			{
				mark=1;
				visit[te->nv]=1;
				cout<<vec[te->nv].data<<"              "<<vec[te->lv].data<<"------>"<<vec[te->nv].data<<"  权值:"<<mat[te->lv][te->nv]<<endl;
				p=new node;
				p->last=s.top();
				p->cousin=NULL;
				p->data=vec[te->nv].data;
				p->label=te->nv;
				if(s.top()->child==NULL)
				s.top()->child=p;
				else
				{
					node *po;
					po=s.top()->child;
					while(po->cousin!=NULL)
					{
						po=po->cousin;
					}
					po->cousin=p;
				}
				s.push(p);
				st.push(te->nv);
				break;
			}
			te=te->e1;
		}
		if(mark==0)
		{
			st.pop();
			s.pop();
		}
	}
	return h;
}


node* bfs(e *fe,int nov,v vec[])
{
	node *h,*p,*q;
	e *t;
	node *tl;
	t=fe;
	int v[nov+1];
	int llv=t->lv;
	for(int i=0;i<nov;i++)
	v[i]=0;
	queue<node*> ql;
	queue<e*> qq;
	cout<<vec[t->lv].data<<"              "<<vec[t->lv].data<<"------>"<<vec[t->nv].data<<"  权值:"<<mat[t->lv][t->nv]<<endl;
	p=new node;
	p->last=NULL;
	p->cousin=NULL;
	p->data=vec[t->lv].data;
	p->label=t->lv;
	h=p;
	q=p;
	v[t->lv]=1;
	qq.push(t);
	tl=p;
	ql.push(tl);
	t=t->e1;
	while(t!=NULL)
	{
		qq.push(t);
		ql.push(tl);
		t=t->e1;
	}
	while(!qq.empty())
	{
		int mark=0;
		t=qq.front();
		if(v[t->nv]==0)
		{
			v[t->nv]=1;
			p=new node;
			p->cousin=NULL;
			p->data=vec[t->nv].data;
			p->label=t->nv;
			p->last=ql.front();
			if(ql.front()->child==NULL)
			{
				ql.front()->child=p;
				q=p;
			}
			else
			{
//				cout<<ql.front()->data<<endl;
				q->cousin=p;
				q=p;
			}
			ql.pop();
			cout<<vec[t->nv].data<<"              "<<vec[t->lv].data<<"------>"<<vec[t->nv].data<<"  权值:"<<mat[t->lv][t->nv]<<endl;
			tl=p;
			t=t->e2;
			while(t!=NULL)
			{
//				cout<<"  "<<t->lv<<" "<<t->nv<<endl;
				ql.push(tl);
				qq.push(t);
				t=t->e1;
			} 
		}
		else
		ql.pop();
		qq.pop();
	}
	return h;
}

void recur(node* h)
{
	node *te=h;
	if(te->visit!=0)
	te->visit=0;
	te=te->child;
	while(te!=NULL)
	{
		if(te->visit!=0)
		te->visit=0;
		if(te->child!=NULL)
		{
			if(te->child->visit!=0)
			te=te->child;
			else
			{
				if(te->cousin!=NULL)
				{
					te=te->cousin;
				}
				else
				te=te->last;
			} 
		}
		else
		{
			if(te->cousin!=NULL)
			{
				te=te->cousin;
			}
			else
			te=te->last;
		}
	}
}

int wdepth(node *h)
{
	int deepest=1;
	queue<node*> q;
	h->depth=1;
	node *t=h->child;
	while(t!=NULL)
	{
		q.push(t);
		t=t->cousin;
	}
	while(!q.empty())
	{
		t=q.front();
		t->depth=t->last->depth+1;
		if(t->depth>=deepest)
		deepest=t->depth;
		t=t->child;
		while(t!=NULL)
		{
			q.push(t);
			t=t->cousin;
		}
		q.pop();
	}
	return deepest;
}

void print_tree(node *h)
{
	int mark2=0;
	int max,ld=1;
	max=wdepth(h);
	queue<node*> q;
	node *t1=h,*t2=NULL;
	cout<<"( "<<t1->data<<" ";
	t1=t1->child;
	while(t1!=NULL)
	{
		q.push(t1);
		t1=t1->cousin;
	}
	while(!q.empty())
	{
		t1=q.front(); 
		if(t1->label==-1)
		{
			if(t1->depth==max)
			{
				
			}
			else
			{
				if(t1->depth!=ld-1)
				{
					if(mark2)
					cout<<"( )";
					else
					{
						cout<<")"<<endl;
						mark2=1;
					}
				}
				else
				{
					cout<<" )( ";
					mark2=0;
				}
				t1->depth+=1;
				q.push(t1);
			}
			
		}
		else
		{
			if(mark2)
			cout<<"( ";
			if(t1->last!=t2)
			{
				cout<<")";
				if(t1->depth!=ld)
				{
					if(!mark2)
					cout<<endl;
			    	cout<<"(";
					ld=t1->depth;
				}
				else
				cout<<"(";
				t2=t1->last;
			}
			cout<<" "<<t1->data<<" ";
			int k=t1->depth;
			t1=t1->child;
			if(t1!=NULL)
			while(t1!=NULL)
			{
				q.push(t1);
				t1=t1->cousin;
			}
			else
			{
				if(k!=max)
				{
					node *emp=new node;
                	emp->label=-1;
                	emp->depth=k;
					q.push(emp);
				}
			}	
			ld=k;	
			mark2=0;
		}
		q.pop();
	}
	cout<<")"<<endl;
}


void pre_visit(node *h)
{
	int v1,v2;
	node *te;
	te=h;
	te->visit=1;
	cout<<te->data;
	v1=te->label;
	te=te->child;
	while(te!=NULL)
	{
		if(te->visit==0)
		{
			te->visit=1;
			v2=te->label;
			cout<<endl;
			v1=te->last->label;
			v2=te->label;
			cout<<te->data<<"          "<<v1<<"  "<<v2<<"  "<<mat[v1][v2];
			v1=te->label;
			if(te->child!=NULL)
			te=te->child;
			else if(te->cousin!=NULL)
			te=te->cousin;
			else
			te=te->last;
		}
		else
		{
			if(te->cousin!=NULL)
			te=te->cousin;
			else
			te=te->last;
		}
	}
	recur(h);
}


void in_visit(node *h)
{
	int v1,v2;
	node *te;
	te=h;
	te->visit++;
	te->last=NULL;
	if(te->child!=NULL)
	te=te->child;
	else
	te->visit++;
	if(te->visit==2)
	cout<<te->data<<endl;
	while(te!=NULL)
	{
		if(te->last==NULL)
		break;
		te->visit++;
		if(te->visit>1)
		{
			if(te->last->visit==1)
			{
				te->last->visit++;
				cout<<te->last->data<<endl;	
			}	
		}
		if(te->visit==2)
		{
			cout<<te->data<<endl;		
		}
		if(te->visit==1)
		{
			if(te->child!=NULL)
			{
				te=te->child;
			}
			else
			{
				te->visit++;
				cout<<te->data<<endl;
			}
		}
		else if(te->visit>1)
		{
			if(te->cousin!=NULL)
			te=te->cousin;
			else 
			te=te->last;
		}
	}
	recur(h);
}

void post_visit(node *h)
{
	node *te;
	te=h;
	te->visit++;
	if(te->child==NULL)
	cout<<te->data<<endl;
	te=te->child;
	while(te!=NULL)
	{
		te->visit++;
		if(te->child==NULL)
		{
			if(te->cousin!=NULL)
			{
				cout<<te->data<<endl;
				te=te->cousin;
			}
			else
			{
				cout<<te->data<<endl;
				te=te->last;
			}
		}
		else
		{
			if(te->child->visit!=0)
			{
				cout<<te->data<<endl;
				if(te->cousin!=NULL)
				te=te->cousin;
				else
				te=te->last;
			}
			else
			te=te->child;
		}
	}
	recur(h);
}





int main()
{
	int nov;
	cout<<"请输入点的总数    "; 
	cin>>nov;
//	int mat[nov][nov];
	for(int i=0;i<nov;i++)
	for(int k=0;k<nov;k++)
	mat[i][k]=0;
	v vec[nov+1];
	cout<<"请输入各个点的数据，第一个输入的点为起点"<<endl;
	for(int i=0;i<nov;i++)
	{
		cout<<"请输入第"<<i+1<<"个点的数据    ";
		cin>>vec[i].data;
	}

	{
		int v1,v2,l;
		cout<<"请输入两个连接的点以及其边的长度    ";
		cin>>v1>>v2; 
		while(v1||v2)
		{
			cin>>l;
			mat[v1-1][v2-1]=l;
			mat[v2-1][v1-1]=l;
			cout<<"请输入两个连接的点以及其边的长度    ";
			cin>>v1>>v2; 
		}
	}
//	for(int i=0;i<nov;i++)
//	{
//		for(int k=0;k<nov;k++)
//		cout<<mat[i][k]<<" ";
//		cout<<endl;
//	}
    cout<<endl<<endl; 
	for(int i=0;i<nov;i++)
	{
		cout<<"编号: "<<i<<"   "<<vec[i].data<<endl;
	}
    cout<<endl<<endl;


    int start;
	e *edge[nov][nov]; 	
	for(int i=0;i<nov;i++)
	for(int k=0;k<nov;k++)
	{
		if(mat[i][k]!=0)
		{
			e *p=new e;
			p->mark=0;
			p->lv=i;
			p->nv=k;
			p->e1=NULL;
			p->e2=NULL;
			p->length=mat[i][k];
			edge[i][k]=p;
		}
		else 
		{
			edge[i][k]=NULL;
		} 
	}
    
	{
	    for(int i=0;i<nov;i++)
	    {
	    	for(int k=0;k<nov;k++)
	    	{
	    		if(mat[i][k]!=0)
	    		{
	    			if(vec[i].edge==NULL)
	    			{
					    vec[i].edge=edge[i][k];
					    break;
	    			}
	    		}
	    	}
	    }
	    
        for(int i=0;i<nov;i++)
        {
        	e* temp;
        	temp=vec[i].edge;
        	for(int k=vec[i].edge->nv+1;k<nov;k++)
        	{
        		if(mat[i][k]!=0)
        		{
        			temp->e1=edge[i][k];
        			temp=temp->e1;
        		}
        	}
        }
        
        for(int i=0;i<nov;i++)
        {
        	for(int k=0;k<nov;k++)
        	{
        		if(mat[i][k]!=0)
        		{
        			edge[i][k]->e2=vec[k].edge;
        	    }
        	}
        }
        
        int start=0;
        node *head;
		char cho='1';
        while(cho=='1'||cho=='2')
		{
			cout<<"请输入起点的编号(输入的范围是 0 ~ "<<nov-1<<"):    ";
			cin>>start;
			while(start<0||start>=nov)
			{
				cout<<"输入非法，请重新输入(输入的范围是 0 ~ "<<nov-1<<"):     ";
				cin>>start;
			} 
			cout<<"输入 1 输出深度优先搜索序列， 输入 2 输出广度优先搜索序列， 输入其他退出程序"<<endl;
	        cin>>cho;
	        if(cho=='2')
	        {
	        	cout<<"各点的遍历序列:    边集:"<<endl;
	        	head=bfs(vec[start].edge,nov,vec);
	        	cout<<endl; 
	        	cout<<"广度优先生成树图:"<<endl; 
				print_tree(head);
				cout<<endl<<endl;
//				cout<<endl<<"前序遍历:"<<endl; 
//				pre_visit(head);
//				cout<<endl<<endl<<"中序遍历:"<<endl;
//				in_visit(head);
//				cout<<endl<<"后序遍历:"<<endl;
//				post_visit(head);
//				cout<<endl;
	        }
		    else if(cho=='1')
		    {
		    	cout<<"各点的遍历序列:    边集:"<<endl;
		    	head=dfs(nov,vec,start);
		    	cout<<endl;
		    	cout<<"深度优先生成树图:"<<endl;
		    	print_tree(head);
		    	cout<<endl<<endl;
//		    	cout<<endl<<"前序遍历:"<<endl; 
//				pre_visit(head);
//				cout<<endl<<endl<<"中序遍历:"<<endl;
//				in_visit(head);
//				cout<<endl<<"后序遍历:"<<endl;
//				post_visit(head);
//				cout<<endl;
		    } 
		} 
	}
	
	return 0;
}


                                
