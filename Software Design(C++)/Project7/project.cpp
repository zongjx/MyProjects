/////////////////////////////////////////////////////////////贪心+小优化（几乎没有） 

#include <iostream>
#include <string>
#include <string.h>
#include <time.h>
#include <algorithm>
using namespace std;

int ans[10001];
int ans2[10001];
int ans3[10001];

///////////////////////////////////////////////////////////////////////////////////////////////////船类 

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
	private:
		int arrival_time;
		int service_time;
		int breths_occupied;
		int assign_time;
};

vessel& vessel::operator=(const vessel& v){                        //运算符重载 
	set_data(v.arrival_time,v.service_time,v.breths_occupied);
	return *this;
}

vessel::vessel(){
	
}

vessel::~vessel(){
	
}

void vessel::set_data(int arrival_time_,int service_time_,int breths_occupied_){ //设置数据 
	arrival_time=arrival_time_;
	service_time=service_time_;
	breths_occupied=breths_occupied_;
	assign_time=-1;
}

int vessel::get_arrival_time(){         //到达时间 
	return arrival_time;
}

int vessel::get_service_time(){         //服务时长 
	return service_time;
}

int vessel::get_breths_occupied(){      //占用长度 
	return breths_occupied;
}

int vessel::get_assign_time(){          //获取放置时的时间 
	return assign_time;
}

void vessel::set_assign_time(int arrival_time){   //放置船时设置时间 
	assign_time=arrival_time;
}

int vessel::get_waiting_time(){           //计算等待时间 
	if(get_assign_time()==-1)
	return -1;
	else return (get_assign_time()-get_arrival_time());
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
		void occupy(int time,int breth,int index,int xs,int ys);
		bool check(int time,int breth,int xs,int ys);
		void arrive(vessel &vessels,int index);
		void arrive2(vessel &vessels,int index);
		void arrive3(vessel &vessels,int index);
		int cal_last_departure_time();
		int *maxtime;
	private:
		int total_time;
		int total_breth;
		int** location;
}; 

breth::breth(int total_time_,int total_breth_){    //初始化 
	set_total_time(total_time_);
	set_total_breth(total_breth_);
	maxtime=new int[total_breth];
	location=new int*[total_breth];
	for(int i=0;i<total_breth;i++)
	location[i]=new int[total_time];
}

breth::~breth(){    
	for(int i=0;i<total_breth;i++)
	delete [] location[i];
	delete [] location;
}

void breth::set_total_time(int total_time_){   //设置长度 
	total_time=total_time_;
}

void breth::set_total_breth(int total_breth_){  //设置宽度 
	total_breth=total_breth_;
}

void breth::op1(){   //操作1，清空港口 
	for(int i=0;i<total_breth;i++){
		for(int k=0;k<total_time;k++){
			location[i][k]=-1;
		}
	}
	for(int i=0;i<total_breth;i++)
	maxtime[i]=0;
}

void breth::op2(){    //操作2，输出港口 
	for(int i=0;i<total_breth;i++){
		for(int k=0;k<total_time;k++){
			if(location[i][k]==-1)
			cout<<"0 ";
			else 
			cout<<location[i][k]<<" ";
		}
		cout<<endl;
	}
}

void breth::arrive(vessel &vessels,int index){  //有船到达，放置在港口相应位置 （优化1） 判断是否有“从中间突出来的船”，排到两边 
	for(int i=vessels.get_arrival_time();i<total_time;i++){
		for(int k=0;k<total_breth;k++){
			if(check(vessels.get_service_time(),vessels.get_breths_occupied(),k,i)){
				if(vessels.get_service_time()+i>maxtime[k]&&k!=0){                        // 
					if(k+vessels.get_breths_occupied()!=total_breth){
						if(k+vessels.get_breths_occupied()<total_breth){
							if(location[k+vessels.get_breths_occupied()][i]!=-1){
								occupy(vessels.get_service_time(),vessels.get_breths_occupied(),index,k,i);
								ans[2*(index-1)]=k;
								ans[2*(index-1)+1]=i;
								vessels.set_assign_time(i);
								for(int p=k;p<total_breth;p++){
									if(maxtime[p]<i+vessels.get_service_time())
									maxtime[p]=i+vessels.get_service_time();
								}
								return;
							}
							else{
								continue;
							}
						}
					    else continue;
					}
					else{
						occupy(vessels.get_service_time(),vessels.get_breths_occupied(),index,k,i);
						ans[2*(index-1)]=k;
						ans[2*(index-1)+1]=i;
						vessels.set_assign_time(i);
						for(int p=k;p<total_breth;p++){
							if(maxtime[p]<i+vessels.get_service_time())
							maxtime[p]=i+vessels.get_service_time();
						}
						return;
					}
				}
				else{
					occupy(vessels.get_service_time(),vessels.get_breths_occupied(),index,k,i);
					ans[2*(index-1)]=k;
					ans[2*(index-1)+1]=i;
					vessels.set_assign_time(i);
					for(int p=k;p<total_breth;p++){
						if(maxtime[p]<i+vessels.get_service_time())
						maxtime[p]=i+vessels.get_service_time();
					}
					return;
				}
				
			}
		}
	}
}

void breth::arrive2(vessel &vessels,int index){  //有船到达，放置在港口相应位置 （贪心无优化） 
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

void breth::arrive3(vessel &vessels,int index){  //有船到达，放置在港口相应位置 （优化2） 
	for(int i=vessels.get_arrival_time();i<total_time;i++){
		for(int k=0;k<total_breth;k++){
			if(check(vessels.get_service_time(),vessels.get_breths_occupied(),k,i)){
				if(vessels.get_service_time()+i>maxtime[k]){                                   //优化1与优化2的区别 
					if(k+vessels.get_breths_occupied()!=total_breth){
						if(k+vessels.get_breths_occupied()<total_breth){
							if(location[k+vessels.get_breths_occupied()][i]!=-1){
								occupy(vessels.get_service_time(),vessels.get_breths_occupied(),index,k,i);
								ans3[2*(index-1)]=k;
								ans3[2*(index-1)+1]=i;
								vessels.set_assign_time(i);
								for(int p=k;p<total_breth;p++){
									if(maxtime[p]<i+vessels.get_service_time())
									maxtime[p]=i+vessels.get_service_time();
								}
								return;
							}
							else{
								continue;
							}
						}
					    else continue;
					}
					else{
						occupy(vessels.get_service_time(),vessels.get_breths_occupied(),index,k,i);
						ans3[2*(index-1)]=k;
						ans3[2*(index-1)+1]=i;
						vessels.set_assign_time(i);
						for(int p=k;p<total_breth;p++){
							if(maxtime[p]<i+vessels.get_service_time())
							maxtime[p]=i+vessels.get_service_time();
						}
						return;
					}
				}
				else{
					occupy(vessels.get_service_time(),vessels.get_breths_occupied(),index,k,i);
					ans3[2*(index-1)]=k;
					ans3[2*(index-1)+1]=i;
					vessels.set_assign_time(i);
					for(int p=k;p<total_breth;p++){
						if(maxtime[p]<i+vessels.get_service_time())
						maxtime[p]=i+vessels.get_service_time();
					}
					return;
				}
				
			}
		}
	}
}

bool breth::check(int time,int breth,int xs,int ys){ //检查是否能把船放进去 
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

///////////////////////////////////////////////////////////////////////////////////////////////////主函 

int main(){
	char op='y',show='n';
	while(op=='y'){
		int _time,_breth,_vessels,arrival_time_,service_time_,breths_occupied_;
		int weight_of_unassigned_vessels,weight_of_total_waiting_time,weight_of_last_departure_time; 
		string ch;
		memset(ans,-1,sizeof(ans));
		memset(ans2,-1,sizeof(ans2));
		memset(ans3,-1,sizeof(ans3));
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
		breth new_breth(_time+1,_breth+1);                                //分别做了三个港口，三艘船，做三次运算，比较哪种算法的出来的结果更优 
		breth new_breth2(_time+1,_breth+1);
		breth new_breth3(_time+1,_breth+1);
		new_breth.op1();
		new_breth2.op1();
		new_breth3.op1();
		cout<<"please input the number of vessels: ";
		cin>>_vessels;
		vessel vessels[_vessels+1];
		vessel vessels2[_vessels+1];
		vessel vessels3[_vessels+1];
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
			vessels2[i].set_data(arrival_time_,service_time_,breths_occupied_);
			vessels3[i].set_data(arrival_time_,service_time_,breths_occupied_);
		}
		clock_t start = clock();
	//	sortv(); 
	    for(int i=1;i<=_vessels;i++){               //sort time                       把船按到达时间按排序（其实样例里面已经有序的） 
	    	for(int k=i+1;k<=_vessels;k++){
	    		if(vessels[k].get_arrival_time()<vessels[i].get_arrival_time()){
	    			vessel temp=vessels[k];
	    			vessels[k]=vessels[i];
	    			vessels[i]=temp;
	    		}
	    	}
	    }
	    for(int i=1;i<=_vessels;i++){               //sort time
	    	for(int k=i+1;k<=_vessels;k++){
	    		if(vessels2[k].get_arrival_time()<vessels2[i].get_arrival_time()){
	    			vessel temp=vessels2[k];
	    			vessels2[k]=vessels2[i];
	    			vessels2[i]=temp;
	    		}
	    	}
	    }
	    for(int i=1;i<=_vessels;i++){               //sort time
	    	for(int k=i+1;k<=_vessels;k++){
	    		if(vessels3[k].get_arrival_time()<vessels3[i].get_arrival_time()){
	    			vessel temp=vessels3[k];
	    			vessels3[k]=vessels3[i];
	    			vessels3[i]=temp;
	    		}
	    	}
	    }
		for(int i=1;i<=_vessels;i++){                                   //把船摆进港口 
			new_breth.arrive(vessels[i],i);
			new_breth2.arrive2(vessels2[i],i);
			new_breth3.arrive3(vessels3[i],i);
		}
		clock_t ends = clock();
		
		cout <<"Running Time : "<<(double)(ends - start)/ CLOCKS_PER_SEC*1000<<"ms" << endl;
		int count_of_not_arrive=0,count_of_time=0,the_last_departure_time=0;
		int count_of_not_arrive2=0,count_of_time2=0,the_last_departure_time2=0;
		int count_of_not_arrive3=0,count_of_time3=0,the_last_departure_time3=0;
		for(int i=1;i<=_vessels;i++){
			if(vessels[i].get_waiting_time()==-1)
			count_of_not_arrive++;
			else{
				count_of_time+=vessels[i].get_waiting_time();
			}
			
		}
		for(int i=1;i<=_vessels;i++){
			if(vessels2[i].get_waiting_time()==-1)
			count_of_not_arrive2++;
			else{
				count_of_time2+=vessels2[i].get_waiting_time();
			}
			
		}
		for(int i=1;i<=_vessels;i++){
			if(vessels3[i].get_waiting_time()==-1)
			count_of_not_arrive3++;
			else{
				count_of_time3+=vessels3[i].get_waiting_time();
			}
			
		}
		the_last_departure_time=new_breth.cal_last_departure_time();
		the_last_departure_time2=new_breth2.cal_last_departure_time();
		the_last_departure_time3=new_breth3.cal_last_departure_time();
		int punish=0,punish2=0,punish3=0;
		
		punish=count_of_not_arrive*weight_of_unassigned_vessels+count_of_time*weight_of_total_waiting_time+the_last_departure_time*weight_of_last_departure_time;
		punish2=count_of_not_arrive2*weight_of_unassigned_vessels+count_of_time2*weight_of_total_waiting_time+the_last_departure_time2*weight_of_last_departure_time; 
		punish3=count_of_not_arrive3*weight_of_unassigned_vessels+count_of_time3*weight_of_total_waiting_time+the_last_departure_time3*weight_of_last_departure_time; 
		if(punish<=punish2&&punish<=punish3){                                           //输出最优的结果（虽然不是很优） 
	        cout<<endl<<"Answer:  ";
			for(int i=0;i<2*_vessels-2;i+=2)
			cout<<ans[i]<<","<<ans[i+1]<<";";
			cout<<ans[2*_vessels-2]<<","<<ans[2*_vessels-1];
			cout<<endl;
			
			cout<<"The number of unassigned vessels is: "<<count_of_not_arrive<<endl;
			cout<<"The total waiting time is: "<<count_of_time<<endl;	
			cout<<"The last departure time is: "<<the_last_departure_time<<endl;
			
			
			cout<<"The total cost is: "<<punish<<endl;
			
			cout<<endl<<"input 'y' to show the breth or input other to skip ";
			cin>>show;
			if(show=='y'){
				new_breth.op2();
			}
			show='n';
        }
		else if(punish2<=punish&&punish2<=punish3){
			cout<<endl<<"Answer:  ";
			for(int i=0;i<2*_vessels-2;i+=2)
			cout<<ans2[i]<<","<<ans2[i+1]<<";";
			cout<<ans2[2*_vessels-2]<<","<<ans2[2*_vessels-1];
			cout<<endl;
			
			cout<<"The number of unassigned vessels is: "<<count_of_not_arrive2<<endl;
			cout<<"The total waiting time is: "<<count_of_time2<<endl;	
			cout<<"The last departure time is: "<<the_last_departure_time2<<endl;
			
			
			cout<<"The total cost is: "<<punish2<<endl;
			
			cout<<endl<<"input 'y' to show the breth or input other to skip ";
			cin>>show;
			if(show=='y'){
				new_breth2.op2();
			}
			show='n';
		}
		else if(punish3<=punish&&punish3<=punish2){
			cout<<endl<<"Answer:  ";
			for(int i=0;i<2*_vessels-2;i+=2)
			cout<<ans3[i]<<","<<ans3[i+1]<<";";
			cout<<ans3[2*_vessels-2]<<","<<ans3[2*_vessels-1];
			cout<<endl;
			
			cout<<"The number of unassigned vessels is: "<<count_of_not_arrive3<<endl;
			cout<<"The total waiting time is: "<<count_of_time3<<endl;	
			cout<<"The last departure time is: "<<the_last_departure_time3<<endl;
			
			
			cout<<"The total cost is: "<<punish3<<endl;
			
			cout<<endl<<"input 'y' to show the breth or input other to skip ";
			cin>>show;
			if(show=='y'){
				new_breth3.op2();
			}
			show='n';
		}
		
		cout<<endl<<"continue?(input 'y' continue) ";
		cin>>op;
	}
	return 0;
}
