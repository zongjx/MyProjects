#ifndef GAME_H
#define GAME_H
//**************************************************************************** class game 
class game
{
	public:
		game();                                                           //constructor of the game
		~game();                                                          //distructor of the game
		void gameCreate();                                                //create a game
		void gameMode_CH();                                               //Human vs Computer
		void gameMode_HH();                                               //Human vs Human
		void gameMode_CC();                                               //Computer vs Computer
		void gameMode_H();                                                //Single player(Human)
		digits getAnswer();                                               //return the digits which is the answer
		int chooseDifficulty; 
		int toInt(string);                                                //transform the string to int
	private:
		int round;                                                        //stroge the number of rounds
		string player1;                                                   //the name of player1
		string player2;                                                   //the name of player2
		string winner;                                                    //the name of the winner
		string loser;                                                     //the name of loser
		int step;                                                         //storge the step of the guess
		digits answer;                                                    //storge the answer of the digits
};
//**************************************************************************** class game

game::game()
{
	round=0;
	player1="none";
	player2="none";
	winner="none";
	loser="none";
	chooseDifficulty=0;
	step=0;
	cout<<"***************************************************************************"<<endl<<"                        欢 迎 来 玩 猜 数 字 ！ ！ ！ !"<<endl<<"***************************************************************************"<<endl;
	cout<<endl<<endl<<endl;
}

game::~game()
{
	
}

int game::toInt(string s)
{
	int d1,d2,d3,d0;
  	d3=s[3]+'0'-96;
	d2=s[2]+'0'-96;
	d1=s[1]+'0'-96;
	d0=s[0]+'0'-96;
	return d0*1000+d1*100+d2*10+d3;
}

void game::gameCreate()
{
    char choose1='0';
	char choose2='Y';
	while(choose2=='Y'||choose2=='y')
	{
	    digits newdigits;
		answer=newdigits;
		round++;
		step=0;
		cout<<"                                   Round "<<round<<endl<<endl;
		cout<<"请选择游戏模式 : 输入 0 进行单人模式   输入 1 进行人人对战模式   输入 2 进行人机对战模式   输入 3 进行电脑与电脑的对战模式"<<endl; 
		cin>>choose1;
		while(choose1!='0'&&choose1!='1'&&choose1!='2'&&choose1!='3')
		{
			cout<<"输入有误！请重新输入！"<<endl;
			cout<<"请选择游戏模式 : 输入 0 进行单人模式   输入 1 进行人人对战模式   输入 2 进行人机对战模式   输入 3 进行电脑与电脑的对战模式"<<endl; 
	    	cin>>choose1;
		}
		if(choose1=='0')
		gameMode_H();
		else if(choose1=='1')
		gameMode_HH();
		else if(choose1=='2')
		gameMode_CH();
		else if(choose1=='3')
		gameMode_CC();
		cout<<"再来一盘？ （输入 Y 或 y 再来一盘 ， 输入 N 或 n 结束游戏）"<<endl;
		cin>>choose2;
		while(choose2!='Y'&&choose2!='y'&&choose2!='N'&&choose2!='n')
		{
			cout<<"输入有误！请重新输入！"<<endl;
			cout<<"再来一盘？ （输入 Y 或 y 再来一盘 ， 输入 N 或 n 结束游戏）"<<endl;
	    	cin>>choose2;
		}
	}
}

void game::gameMode_HH()
{
    cout<<endl<<endl;
	cout<<"                                               "<<"Step"<<"    Number     "<<"A and B"<<endl; 
	player1="player1";
	player2="player2";
	int correct=0;
	playerHuman p1(player1),p2(player2);
	digits p1d,p2d;
	string in;
	int p1_in,p2_in;
	while(correct!=4)
	{
		step++;
		cout<<"Player 1   Please enter your digits:";
		cin>>in;
		while(p1d.checkFormat(in)!=true)
		{
			cout<<"Digits illegal\nPlayer 1   Please enter your digits:";
			cin>>in;
		}
		p1_in=toInt(in);
		p1d.setDigits(p1_in);
		p1d.compare(getAnswer());
		cout<<"                                                 "<<step<<"       ";
		p1d.display();
		cout<<"     "<<p1d.getValueAndPosition()<<"A"<<p1d.getValueOnly()<<"B"<<endl;
		if(p1d.getValueAndPosition()==4)
		{
			cout<<p1.getName()<<" Win!"<<endl;
			winner=p1.getName();
			break;
		}
		p1d.set_getValueOnly();
		p1d.set_getValueAndPosition();
		step++;
		cout<<"Player 2   Please enter your digits:";
		cin>>in;
		while(p2d.checkFormat(in)!=true)
		{
			cout<<"Digits illegal\nPlayer 2   Please enter your digits:";
			cin>>in;
		}
		p2_in=toInt(in);
		p2d.setDigits(p2_in);
		p2d.compare(getAnswer());
		cout<<"                                                 "<<step<<"       ";
		p2d.display();
		cout<<"     "<<p2d.getValueAndPosition()<<"A"<<p2d.getValueOnly()<<"B"<<endl;
		if(p2d.getValueAndPosition()==4)
		{
			cout<<p2.getName()<<" Win!"<<endl;
			winner=p2.getName();
			break;
		}
		p2d.set_getValueOnly();
		p2d.set_getValueAndPosition();
	}
	cout<<"Winner："<<winner<<"!  Congratulations!!"<<endl; 
}

void game::gameMode_CH()
{
	char first='0'; 
	int correct=0;
	cout<<"请选择难度：    输入 1 菜鸟难度      输入 2 困难难度"<<endl;
	cin>>chooseDifficulty;
	while(chooseDifficulty!=1&&chooseDifficulty!=2)
	{
		cout<<"输入有误！请重新输入！"<<endl;
		cout<<"请选择难度：    输入 1 菜鸟难度      输入 2 困难难度"<<endl;
		cin>>chooseDifficulty;
	} 
	cout<<"请决定哪方先猜：      输入 1 玩家先猜       输入 2 电脑先猜"<<endl;
	cin>>first;
	while(first!='1'&&first!='2')
	{
		cout<<"输入有误！请重新输入！"<<endl;
		cout<<"请决定哪方先猜：      输入 1 玩家先猜       输入 2 电脑先猜"<<endl;
		cin>>first;
	}
	cout<<endl<<endl;
	cout<<"                                               "<<"Step"<<"    Number     "<<"A and B"<<endl; 
	if(first=='1')
	{
		player1="player Human";
	    player2="player Computer";
		playerHuman p1(player1);
		playerComputer p2(player2);
		digits p1d,p2d;
		string in;
		int p1_in,p2_in;
		while(correct!=4)
		{
			step++;
			cout<<"Player 1   Please enter your digits:";
			cin>>in;
			while(p1d.checkFormat(in)!=true)
			{
				cout<<"Digits illegal\nPlayer 1   Please enter your digits:";
				cin>>in;
			}
			p1_in=toInt(in);
			p1d.setDigits(p1_in);
			p1d.compare(getAnswer());
			cout<<"                                                 "<<step<<"       ";
			p1d.display();
			cout<<"     "<<p1d.getValueAndPosition()<<"A"<<p1d.getValueOnly()<<"B"<<endl;
			if(chooseDifficulty==2)
			p2.getInformation(p1_in,p1d.getValueAndPosition(),p1d.getValueOnly());
			else if(chooseDifficulty==1)
			p2.getInformation_(p1_in);
			if(p1d.getValueAndPosition()==4)
			{
				cout<<p1.getName()<<" Win!"<<endl;
				winner=p1.getName();
				break;
			}
			p1d.set_getValueOnly();
			p1d.set_getValueAndPosition();
			step++;
			cout<<"Player 2   Please enter your digits:";
			p2_in=p2.inputDigits_AI();
			p2d.setDigits(p2_in);
			p2d.display();
			while(p2d.checkFormat(p2_in)!=true)
    		{
	     		cout<<"\nDigits illegal\nPlayer 2   Please enter your digits:";
 	    		p2_in=p2.inputDigits_AI();
 	    		p2d.setDigits(p2_in);
			    p2d.display();
     		}
			p2d.compare(getAnswer());
			cout<<endl;
			cout<<"                                                 "<<step<<"       ";
			p2d.display();
			cout<<"     "<<p2d.getValueAndPosition()<<"A"<<p2d.getValueOnly()<<"B"<<endl;
			if(chooseDifficulty==2)
			p2.getInformation(p2_in,p2d.getValueAndPosition(),p2d.getValueOnly());
			else if(chooseDifficulty==1)
			p2.getInformation_(p2_in);
			if(p2d.getValueAndPosition()==4)
			{
				cout<<p2.getName()<<" Win!"<<endl;
				winner=p2.getName();
				break;
			}
			p2d.set_getValueOnly();
			p2d.set_getValueAndPosition();
		}
	}
	else if(first=='2')
	{
		player2="player Human";
	    player1="player Computer";
	    playerComputer p1(player1);
		playerHuman p2(player2);
		digits p1d,p2d;
		string in;
		int p1_in,p2_in;
		while(correct!=4)
		{
			step++;
			cout<<"Player 1   Please enter your digits:";
			p1_in=p1.inputDigits_AI();
			p1d.setDigits(p1_in);
			p1d.display();
			while(p1d.checkFormat(p1_in)!=true)
	    	{
    			cout<<"\nDigits illegal\nPlayer 1   Please enter your digits:";
	    		p1_in=p1.inputDigits_AI();
	    		p1d.setDigits(p1_in);
			    p1d.display();
	    	}
			cout<<endl;
			p1d.compare(getAnswer());
			cout<<"                                                 "<<step<<"       ";
			p1d.display();
			cout<<"     "<<p1d.getValueAndPosition()<<"A"<<p1d.getValueOnly()<<"B"<<endl;
			if(chooseDifficulty==2)
			p1.getInformation(p1_in,p1d.getValueAndPosition(),p1d.getValueOnly());
			else if(chooseDifficulty==1)
			p1.getInformation_(p1_in);
			if(p1d.getValueAndPosition()==4)
			{
				cout<<p1.getName()<<" Win!"<<endl;
				winner=p1.getName();
				break;
			}
			p1d.set_getValueOnly();
			p1d.set_getValueAndPosition();
			step++;
			cout<<"Player 2   Please enter your digits:";
			cin>>in;
			while(p2d.checkFormat(in)!=true)
			{
				cout<<"Digits illegal\nPlayer 2   Please enter your digits:";
				cin>>in;
			}
			p2_in=toInt(in);
			p2d.setDigits(p2_in);
			p2d.compare(getAnswer());
			cout<<"                                                 "<<step<<"       ";
			p2d.display();
			cout<<"     "<<p2d.getValueAndPosition()<<"A"<<p2d.getValueOnly()<<"B"<<endl;
			if(chooseDifficulty==2)
			p1.getInformation(p2_in,p2d.getValueAndPosition(),p2d.getValueOnly());
			else if(chooseDifficulty==1)
			p1.getInformation_(p2_in);
			if(p2d.getValueAndPosition()==4)
			{
				cout<<p2.getName()<<" Win!"<<endl;
				winner=p2.getName();
				break;
			}
			p2d.set_getValueOnly();
			p2d.set_getValueAndPosition();
		}
	}
	cout<<"Winner："<<winner<<"!  Congratulations!!"<<endl<<endl; 
	if(winner=="player Human")
	cout<<"You Win! You beat the Computer!"<<endl<<endl;
	else if(winner=="player Computer")
	cout<<"You Lose! That's a pity!"<<endl<<endl;
}

void game::gameMode_CC()
{ 
    int chooseDifficulty1=0,chooseDifficulty2=0; 
	int correct=0;
	cout<<"请选择电脑1的难度：    输入 1 菜鸟难度      输入 2 困难难度"<<endl;
	cin>>chooseDifficulty1;
	while(chooseDifficulty1!=1&&chooseDifficulty1!=2)
	{
		cout<<"输入有误！请重新输入！"<<endl;
		cout<<"请选择电脑1的难度：    输入 1 菜鸟难度      输入 2 困难难度"<<endl;
		cin>>chooseDifficulty1;
	}
	cout<<"请选择电脑2的难度：    输入 1 菜鸟难度      输入 2 困难难度"<<endl;
	cin>>chooseDifficulty2;
	while(chooseDifficulty2!=1&&chooseDifficulty2!=2)
	{
		cout<<"输入有误！请重新输入！"<<endl;
		cout<<"请选择电脑2的难度：    输入 1 菜鸟难度      输入 2 困难难度"<<endl;
		cin>>chooseDifficulty2;
	}
	cout<<endl<<endl;
	cout<<"                                               "<<"Step"<<"    Number     "<<"A and B"<<endl; 
	player1="player Computer1";
    player2="player Computer2";
	playerComputer p1(player1);
	playerComputer p2(player2);
	digits p1d,p2d;
	string in;
	int p1_in,p2_in;
	while(correct!=4)
	{
		step++;
		cout<<"Player 1   Please enter your digits:";
		p1_in=p1.inputDigits_AI();
		p1d.setDigits(p1_in);
		p1d.display();
		while(p1d.checkFormat(p1_in)!=true)
		{
			cout<<"\nDigits illegal\nPlayer 1   Please enter your digits:";
			p1_in=p1.inputDigits_AI();
			p1d.setDigits(p1_in);
		    p1d.display();
		}
		p1d.compare(getAnswer());
		cout<<endl;
		cout<<"                                                 "<<step<<"       ";
		p1d.display();
		cout<<"     "<<p1d.getValueAndPosition()<<"A"<<p1d.getValueOnly()<<"B"<<endl;
		if(chooseDifficulty1==2)
		p1.getInformation(p1_in,p1d.getValueAndPosition(),p1d.getValueOnly());
		else if(chooseDifficulty1==1)
		p1.getInformation_(p1_in);
		if(chooseDifficulty2==2)
		p2.getInformation(p1_in,p1d.getValueAndPosition(),p1d.getValueOnly());
		else if(chooseDifficulty2==1)
		p2.getInformation_(p1_in);
		if(p1d.getValueAndPosition()==4)
		{
			cout<<p1.getName()<<" Win!"<<endl;
			winner=p1.getName();
			break;
		}
		p1d.set_getValueOnly();
		p1d.set_getValueAndPosition();
		step++;
		cout<<"Player 2   Please enter your digits:";
		p2_in=p2.inputDigits_AI();
		p2d.setDigits(p2_in);
		p2d.display();
		while(p2d.checkFormat(p2_in)!=true)
		{
			cout<<"\nDigits illegal\nPlayer 2   Please enter your digits:";
			p2_in=p2.inputDigits_AI();
			p2d.setDigits(p2_in);
		    p2d.display();
		}
		p2d.compare(getAnswer());
		cout<<endl;
		cout<<"                                                 "<<step<<"       ";
		p2d.display();
		cout<<"     "<<p2d.getValueAndPosition()<<"A"<<p2d.getValueOnly()<<"B"<<endl;
		if(chooseDifficulty1==2)
		p1.getInformation(p2_in,p2d.getValueAndPosition(),p2d.getValueOnly());
		else if(chooseDifficulty1==1)
		p1.getInformation_(p2_in);
		if(chooseDifficulty2==2)
		p2.getInformation(p2_in,p2d.getValueAndPosition(),p2d.getValueOnly());
		else if(chooseDifficulty2==1)
		p2.getInformation_(p2_in);
		if(p2d.getValueAndPosition()==4)
		{
			cout<<p2.getName()<<" Win!"<<endl;
			winner=p2.getName();
			break;
		}
		p2d.set_getValueOnly();
		p2d.set_getValueAndPosition();
	}
}

void game::gameMode_H()
{
	cout<<endl<<endl;
	cout<<"                                               "<<"Step"<<"    Number     "<<"A and B"<<endl; 
	player1="player";
	playerHuman p1(player1);
	int correct=0;
	digits p1d;
	string in;
	int p1_in;
	while(correct!=4)
	{
		step++;
		cout<<"Player   Please enter your digits:";
		cin>>in;
		while(p1d.checkFormat(in)!=true)
		{
			cout<<"Digits illegal\nPlayer   Please enter your digits:";
			cin>>in;
		}
		p1_in=toInt(in);
		p1d.setDigits(p1_in);
		p1d.compare(getAnswer());
		cout<<"                                                 "<<step<<"       ";
		p1d.display();
		cout<<"     "<<p1d.getValueAndPosition()<<"A"<<p1d.getValueOnly()<<"B"<<endl;
		if(p1d.getValueAndPosition()==4)
		{
			cout<<"You Win!"<<endl;
			winner=p1.getName();
			break;
		}
		p1d.set_getValueOnly();
		p1d.set_getValueAndPosition();
	}
	cout<<"Winner："<<winner<<"!  Congratulations!!"<<endl; 
}

digits game::getAnswer()
{
	return answer;
}
#endif
