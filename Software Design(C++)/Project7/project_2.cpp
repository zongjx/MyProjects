//////////////////////////////////////////////////////////////////////（局部）全排列贪心搜索 



#include <iostream>
#include <string>
#include <string.h>
#include <algorithm>
#include <time.h>
using namespace std;

int ans[10001];
int ans2[10001];
int a[1001];
int m;
int interrupt=0; 
int weight_of_unassigned_vessels,weight_of_total_waiting_time,weight_of_last_departure_time; 
		
///////////////////////////////////////////////////////////////////////////////////////////////////  船类 

class vessel{
	public:
		vessel();
		~vessel();
		void set_data(int arrival_time_,int service_time_,int breths_occupied_);
		int get_arrival_time();
		int get_service_time();
		int get_breths_occupied();
		int get_assign_time();
		void set_assign_time(int arrival_time);
		int get_waiting_time();
		vessel& operator=(const vessel& v);
		void erase_mark();
	private:
		int arrival_time;
		int service_time;
		int breths_occupied;
		int assign_time;
};

vessel& vessel::operator=(const vessel& v){                    //运算符重载 
	set_data(v.arrival_time,v.service_time,v.breths_occupied);
	return *this;
}

vessel::vessel(){
	
}

vessel::~vessel(){
	
}

void vessel::set_data(int arrival_time_,int service_time_,int breths_occupied_){   //设置数据 
	arrival_time=arrival_time_;
	service_time=service_time_;
	breths_occupied=breths_occupied_;
	assign_time=-1;
}

int vessel::get_arrival_time(){           //到达时间
	return arrival_time;
}

int vessel::get_service_time(){           //服务时长 
	return service_time;
}

int vessel::get_breths_occupied(){        //占用长度
	return breths_occupied;
}

int vessel::get_assign_time(){            //获取放置时的时间 
	return assign_time;
}

void vessel::set_assign_time(int arrival_time){   //放置船时设置时间 
	assign_time=arrival_time;
}

int vessel::get_waiting_time(){    //计算等待时间
	if(get_assign_time()==-1)
	return -1;
	else return (get_assign_time()-get_arrival_time());
}

void vessel::erase_mark(){     //清除船的放置时间 
	assign_time=-1;
}

///////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////////////////港口类 

class breth{
	public:
		breth(int total_time_,int total_breth_);
		~breth();
		void set_total_time(int total_time_);
		void set_total_breth(int total_breth_);
		void op1();
		void op2();
		void op3();
		void occupy(int time,int breth,int index,int xs,int ys);
		bool check(int time,int breth,int xs,int ys);
		void arrive(vessel &vessels,int index);
		int cal_last_departure_time();
		void change(int punish,int count_of_time,int count_of_not_arrive,int the_last_departure_time);
		int best_punish;
		int best_count_of_time;
		int best_count_of_not_arrive;
		int best_the_last_departure_time;
	private:
		int total_time;
		int total_breth;
		int** location;
		int** best;
}; 

breth::breth(int total_time_,int total_breth_){   //初始化 
	best_punish=1000000;
	best_count_of_time=1000000;
	best_count_of_not_arrive=1000000;
	best_the_last_departure_time=1000000;
	set_total_time(total_time_);
	set_total_breth(total_breth_);
	best=new int*[total_breth];
	location=new int*[total_breth];
	for(int i=0;i<total_breth;i++)
	location[i]=new int[total_time];
	for(int i=0;i<total_breth;i++)
	best[i]=new int[total_time];
}

breth::~breth(){
	for(int i=0;i<total_breth;i++)
	delete [] location[i];
	delete [] location;
	for(int i=0;i<total_breth;i++)
	delete [] best[i];
	delete [] best;
}

void breth::set_total_time(int total_time_){   //设置长度 
	total_time=total_time_;
}

void breth::set_total_breth(int total_breth_){   //设置宽度 
	total_breth=total_breth_;
}

void breth::op1(){    //操作1，清空港口 
	for(int i=0;i<total_breth;i++){
		for(int k=0;k<total_time;k++){
			location[i][k]=-1;
		}
	}
}

void breth::op2(){    //操作2，输出港口 
	for(int i=0;i<total_breth;i++){
		for(int k=0;k<total_time;k++){
			if(best[i][k]==-1)
			cout<<"0 ";
			else 
			cout<<best[i][k]<<" ";
		}
		cout<<endl;
	}
}

void breth::op3(){  //操作3，清空最优解 
	for(int i=0;i<total_breth;i++){
		for(int k=0;k<total_time;k++){
			best[i][k]=-1;
		}
	}
}

void breth::arrive(vessel &vessels,int index){ //有船到达，放置在港口相应位置（用贪心放置） 
	for(int i=vessels.get_arrival_time();i<total_time;i++){
		for(int k=0;k<total_breth;k++){
			if(check(vessels.get_service_time(),vessels.get_breths_occupied(),k,i)){
				occupy(vessels.get_service_time(),vessels.get_breths_occupied(),index,k,i);
				ans2[2*(index-1)]=k;
				ans2[2*(index-1)+1]=i;
				vessels.set_assign_time(i);
				return;
			}
		}
	}
}

bool breth::check(int time,int breth,int xs,int ys){//检查是否能把船放进去 
	if(xs+breth<=total_breth&&ys+time<=total_time){
		for(int i=xs;i<xs+breth;i++)
		for(int k=ys;k<ys+time;k++){
			if(location[i][k]!=-1)
		    return false;
		}
	}
	else{
		return false; 
	}
	return true;
}

void breth::occupy(int time,int breth,int index,int xs,int ys){  //放置船 
	for(int i=xs;i<xs+breth;i++)
	for(int k=ys;k<ys+time;k++)
	location[i][k]=index;
}

int breth::cal_last_departure_time(){   //计算最后离开的时间 
	int res=total_time;
	bool mark=0;
	for(int i=total_time-1;i>=0;i--){
		mark=0;
		for(int k=0;k<total_breth;k++){
			if(location[k][i]!=-1)
			mark=1;
		}
		if(!mark){
			if(i<res) res=i;
		}
	}
	return res;
}

void breth::change(int punish,int count_of_time,int count_of_not_arrive,int the_last_departure_time){     //更新最优解 
	for(int i=0;i<total_breth;i++){
		for(int k=0;k<total_time;k++){
			best[i][k]=location[i][k];
		}
	}
	best_punish=punish;
	for(int i=0;i<2*m;i++){
		ans[i]=ans2[i];
	}
	best_count_of_time=count_of_time;
	best_count_of_not_arrive=count_of_not_arrive;
	best_the_last_departure_time=the_last_departure_time;
}

///////////////////////////////////////////////////////////////////////////////////////////////////

void solve_pre(breth &new_breth,vessel *vessels,int a[]){        //放船 
    memset(ans2,-1,sizeof(ans2));
	for(int i=1;i<=m;i++){
		int k=a[i];
		
		new_breth.arrive(vessels[k],k);
	}
	int count_of_not_arrive=0,count_of_time=0,the_last_departure_time=0;
	for(int i=1;i<=m;i++){
		if(vessels[i].get_waiting_time()==-1)
		count_of_not_arrive++;
		else{
			count_of_time+=vessels[i].get_waiting_time();
		}
	}
	the_last_departure_time=new_breth.cal_last_departure_time();
	int punish=0;
	punish=count_of_not_arrive*weight_of_unassigned_vessels+count_of_time*weight_of_total_waiting_time+the_last_departure_time*weight_of_last_departure_time;
	if(punish<new_breth.best_punish){
    	new_breth.change(punish,count_of_time,count_of_not_arrive,the_last_departure_time);
    	interrupt=0;
    }
    else interrupt++;
} 

void f1(int visited[],int y,breth &new_breth,vessel *vessels)//递归求全排列 
{
    int i;
    if(y==m+1)
    {
    	new_breth.op1();
    	for(int i=1;i<=m;i++)
    	vessels[i].erase_mark();
        solve_pre(new_breth,vessels,a);
    }
    else
    {
        for(i=1;i<=m;i++)
        {
            if(visited[i]==0)
            {
                a[y]=i;
                visited[i]=1;
                if(interrupt>=1000000) return;    ///中断搜索  
                f1(visited,y+1,new_breth,vessels);             
                visited[i]=0;
            }
        }
    }
}

void solve(breth &new_breth,vessel *vessels)   //求解（求全排列） 
{
    int l;
    int temp[1001];
        for(l=1;l<=m;l++)
        {
            memset(temp,0,sizeof(temp));
            memset(a,0,sizeof(a));
            a[1]=l;
            temp[l]=1;
            f1(temp,2,new_breth,vessels);
            cout<<l<<endl; 
            if(interrupt>=1000000) {
            	interrupt=0;
            	continue;
            }
        }
}     

/////////////////////////////////////////////////////////////////////////////////////////////////// 
int main(){
	char op='y',show='n';
	while(op=='y'){
		interrupt=0;
		int _time,_breth,_vessels,arrival_time_,service_time_,breths_occupied_;
		string ch;
		memset(ans,-1,sizeof(ans));
		cout<<"\n\n                                BAP\n";
		cout<<"please input the weight of the unassigned vessels: ";
		cin>>weight_of_unassigned_vessels;
		cout<<"please input the weight of total waiting time: ";
		cin>>weight_of_total_waiting_time;
		cout<<"please input the weight oflast departure time: ";
		cin>>weight_of_last_departure_time;
		cout<<"please input the total time of the time: ";
		cin>>_time;
		_time--;
		cout<<"please input the total length of the breth: ";
		cin>>_breth;
		_breth--;
		breth new_breth(_time+1,_breth+1);
		new_breth.op1();
		new_breth.op3();
		cout<<"please input the number of vessels: ";
		cin>>_vessels;
		m=_vessels;
		vessel vessels[_vessels+1];
		for(int i=1;i<=_vessels;i++){
			if(i%10==1) ch="st";
			else if(i%10==2) ch="nd";
			else if(i%10==3) ch="rd";
			else ch="th";
			cout<<"please input the "<<i<<ch<<" vessel's data (arrival time , service time , breths occupued): ";
			cin>>arrival_time_;
			cin>>service_time_;
			cin>>breths_occupied_;
			vessels[i].set_data(arrival_time_,service_time_,breths_occupied_);
		}
		clock_t start = clock();
	    for(int i=1;i<=_vessels;i++){               //sort time
	    	for(int k=i+1;k<=_vessels;k++){
	    		if(vessels[k].get_arrival_time()<vessels[i].get_arrival_time()){
	    			vessel temp=vessels[k];
	    			vessels[k]=vessels[i];
	    			vessels[i]=temp;
	    		}
	    	}
	    }
		
		solve(new_breth,vessels);
		clock_t ends = clock();
		cout <<"Running Time : "<<(double)(ends - start)/ CLOCKS_PER_SEC*1000<<"ms" << endl;
		cout<<endl<<"Answer:  ";
		for(int i=0;i<2*_vessels-2;i+=2)
		cout<<ans[i]<<","<<ans[i+1]<<";";
		cout<<ans[2*_vessels-2]<<","<<ans[2*_vessels-1];
		cout<<endl;
		
		cout<<"The number of unassigned vessels is: "<<new_breth.best_count_of_not_arrive<<endl;
		cout<<"The total waiting time is: "<<new_breth.best_count_of_time<<endl;	
		cout<<"The last departure time is: "<<new_breth.best_the_last_departure_time<<endl;
		
		
		cout<<"The total cost is: "<<new_breth.best_punish<<endl;
		
		cout<<endl<<"input 'y' to show the breth or input other to skip ";
		cin>>show;
		if(show=='y'){
			new_breth.op2();
		}
		show='n';
		cout<<endl<<"continue?(input 'y' continue) ";
		cin>>op;
	}
	return 0;
}
