#include <iostream>
#include <iomanip>
#include <string>
#include <stack> 
#include <cmath>

using namespace std;


bool check(string s)                                       //检查输入的式子的格式是否有误的函数 
{
	int l = 0,bra = 0;
	l = s.length();
	for (int i = 0 ; i < l ; i++)                          //检查式子中是否有非法字符 
	{ 
		if ( (s[i] < 48 || s[i] > 57) && s[i] != '(' && s[i] != ')' && s[i] != '+' && s[i] != '-' && s[i] != '*' && s[i] != '/' && s[i] != '^' && s[i] != '.')
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
		else if (s[i] == '+' || s[i] == '-' || s[i] == '*' || s[i] == '/' || s[i] == '^' || s[i] == '.')
		{
			if (s[i] == '.')
			{
				if (s[i+1] < 48 || s[i+1] > 57)
				{
					return false;
				}
			}
			else
			{
				if ( (s[i+1] < 48 || s[i+1] > 57) && s[i+1] != '(')
				{
					return false;
				}
			}
		} 
	}
	if ( (s[0] < 48 || s[0] > 57) && s[0] != '(' && s[0] != '-')    //检查式子第一个字符 
	return false;                                                    
	if (bra>0)                                             //括号格式检查 
	return false;
	return true;
}


void cal(string st)                                        //计算式子结果的函数 
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
	cout << sd.top() << endl;
}


void print_stack(string st)                                //这一个函数跟上一个函数其实差不多一样，只是在这个函数（计算过程）里面加入了输出栈里的内容的语句 
{                                                          //使程序能够体现栈的变化过程 
	cout << std::left << setw(8) << "步骤" << std::left << setw(40) << "操作符栈" << std::left << setw(40) << "运算数栈" << endl; 
	char oper[100001];
	double opnum[100001];
	int step = 1,er = 0,nu = 0; 
	string sout;
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
		    while(!sc.empty())
			{
				oper[er] = sc.top();
				sc.pop();
				er++;
			}
			while(!sd.empty())
			{
				opnum[nu] = sd.top();
				sd.pop();
				nu++; 
			}
			cout << std::left << setw(8) << step++;
			while(er)
			{
				er--;
				sout += oper[er];
				sc.push(oper[er]);
			}
			cout << std::left << setw(40) << sout;
			sout = "";
			while(nu)
			{
				nu--;
				cout << opnum[nu] << " ";
				sd.push(opnum[nu]);
			}
			cout<<"      输入字符: " << s[cnt] <<endl;
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
	    	while(!sc.empty())
			{
				oper[er] = sc.top();
				sc.pop();
				er++;
			}
			while(!sd.empty())
			{
				opnum[nu] = sd.top();
				sd.pop();
				nu++; 
			}
			cout << std::left << setw(8) << step++;
			while(er)
			{
				er--;
				sout += oper[er];
				sc.push(oper[er]);
			}
			cout << std::left << setw(40) << sout;
			sout = "";
			while(nu)
			{
				nu--;
				cout << opnum[nu] << " ";
				sd.push(opnum[nu]);
			}
			cout<<"      输入字符: " << c <<endl; 
			while(!sc.empty())
			{
				oper[er] = sc.top();
				sc.pop();
				er++;
			}
			while(!sd.empty())
			{
				opnum[nu] = sd.top();
				sd.pop();
				nu++; 
			}
			cout << std::left << setw(8) << step++;
			while(er)
			{
				er--;
				sout += oper[er];
				sc.push(oper[er]);
			}
			cout << std::left << setw(40) << sout;
			sout = "";
			while(nu)
			{
				nu--;
				cout << opnum[nu] << " ";
				sd.push(opnum[nu]);
			}
			cout<<"      输入字符: " << s[cnt] <<endl; 
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
	    	while(!sc.empty())
			{
				oper[er] = sc.top();
				sc.pop();
				er++;
			}
			while(!sd.empty())
			{
				opnum[nu] = sd.top();
				sd.pop();
				nu++; 
			}
			cout << std::left << setw(8) << step++;
			while(er)
			{
				er--;
				sout += oper[er];
				sc.push(oper[er]);
			}
			cout << std::left << setw(40) << sout;
			sout = "";
			while(nu)
			{
				nu--;
				cout << opnum[nu] << " ";
				sd.push(opnum[nu]);
			}
			cout<<"      输入字符: " << c <<endl; 
			while(!sc.empty())
			{
				oper[er] = sc.top();
				sc.pop();
				er++;
			}
			while(!sd.empty())
			{
				opnum[nu] = sd.top();
				sd.pop();
				nu++; 
			}
			cout << std::left << setw(8) << step++;
			while(er)
			{
				er--;
				sout += oper[er];
				sc.push(oper[er]);
			}
			cout << std::left << setw(40) << sout;
			sout = "";
			while(nu)
			{
				nu--;
				cout << opnum[nu] << " ";
				sd.push(opnum[nu]);
			}
			cout<<"      输入字符: " << s[cnt] <<endl; 
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
	    	while(!sc.empty())
			{
				oper[er] = sc.top();
				sc.pop();
				er++;
			}
			while(!sd.empty())
			{
				opnum[nu] = sd.top();
				sd.pop();
				nu++; 
			}
			cout << std::left << setw(8) << step++;
			while(er)
			{
				er--;
				sout += oper[er];
				sc.push(oper[er]);
			}
			cout << std::left << setw(40) << sout;
			sout = "";
			while(nu)
			{
				nu--;
				cout << opnum[nu] << " ";
				sd.push(opnum[nu]);
			}
			cout<<"      输入字符: " << c <<endl; 
			while(!sc.empty())
			{
				oper[er] = sc.top();
				sc.pop();
				er++;
			}
			while(!sd.empty())
			{
				opnum[nu] = sd.top();
				sd.pop();
				nu++; 
			}
			cout << std::left << setw(8) << step++;
			while(er)
			{
				er--;
				sout += oper[er];
				sc.push(oper[er]);
			}
			cout << std::left << setw(40) << sout;
			sout = "";
			while(nu)
			{
				nu--;
				cout << opnum[nu] << " ";
				sd.push(opnum[nu]);
			}
			cout<<"      输入字符: " << s[cnt] <<endl; 
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
	    	while(!sc.empty())
			{
				oper[er] = sc.top();
				sc.pop();
				er++;
			}
			while(!sd.empty())
			{
				opnum[nu] = sd.top();
				sd.pop();
				nu++; 
			}
			cout << std::left << setw(8) << step++;
			while(er)
			{
				er--;
				sout += oper[er];
				sc.push(oper[er]);
			}
			cout << std::left << setw(40) << sout;
			sout = "";
			while(nu)
			{
				nu--;
				cout << opnum[nu] << " ";
				sd.push(opnum[nu]);
			}
			cout<<"      输入字符: " << c <<endl; 
			while(!sc.empty())
			{
				oper[er] = sc.top();
				sc.pop();
				er++;
			}
			while(!sd.empty())
			{
				opnum[nu] = sd.top();
				sd.pop();
				nu++; 
			}
			cout << std::left << setw(8) << step++;
			while(er)
			{
				er--;
				sout += oper[er];
				sc.push(oper[er]);
			}
			cout << std::left << setw(40) << sout;
			sout = "";
			while(nu)
			{
				nu--;
				cout << opnum[nu] << " ";
				sd.push(opnum[nu]);
			}
			cout<<"      输入字符: " << s[cnt] <<endl; 
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
	    	while(!sc.empty())
			{
				oper[er] = sc.top();
				sc.pop();
				er++;
			}
			while(!sd.empty())
			{
				opnum[nu] = sd.top();
				sd.pop();
				nu++; 
			}
			cout << std::left << setw(8) << step++;
			while(er)
			{
				er--;
				sout += oper[er];
				sc.push(oper[er]);
			}
			cout << std::left << setw(40) << sout;
			sout = "";
			while(nu)
			{
				nu--;
				cout << opnum[nu] << " ";
				sd.push(opnum[nu]);
			}
			cout<<"      输入字符: " << c <<endl; 
			while(!sc.empty())
			{
				oper[er] = sc.top();
				sc.pop();
				er++;
			}
			while(!sd.empty())
			{
				opnum[nu] = sd.top();
				sd.pop();
				nu++; 
			}
			cout << std::left << setw(8) << step++;
			while(er)
			{
				er--;
				sout += oper[er];
				sc.push(oper[er]);
			}
			cout << std::left << setw(40) << sout;
			sout = "";
			while(nu)
			{
				nu--;
				cout << opnum[nu] << " ";
				sd.push(opnum[nu]);
			}
			cout<<"      输入字符: " << s[cnt] <<endl; 
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
				while(!sc.empty())
			{
				oper[er] = sc.top();
				sc.pop();
				er++;
			}
			while(!sd.empty())
			{
				opnum[nu] = sd.top();
				sd.pop();
				nu++; 
			}
			cout << std::left << setw(8) << step++;
			while(er)
			{
				er--;
				sout += oper[er];
				sc.push(oper[er]);
			}
			cout << std::left << setw(40) << sout;
			sout = "";
			while(nu)
			{
				nu--;
				cout << opnum[nu] << " ";
				sd.push(opnum[nu]);
			}
			cout<<"      输入字符: " << s[cnt] <<endl; 
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
	    	while(!sc.empty())
			{
				oper[er] = sc.top();
				sc.pop();
				er++;
			}
			while(!sd.empty())
			{
				opnum[nu] = sd.top();
				sd.pop();
				nu++; 
			}
			cout << std::left << setw(8) << step++;
			while(er)
			{
				er--;
				sout += oper[er];
				sc.push(oper[er]);
			}
			cout << std::left << setw(40) << sout;
			sout = "";
			while(nu)
			{
				nu--;
				cout << opnum[nu] << " ";
				sd.push(opnum[nu]);
			}
			cout<<"      输入字符: " << c <<endl; 
			while(!sc.empty())
			{
				oper[er] = sc.top();
				sc.pop();
				er++;
			}
			while(!sd.empty())
			{
				opnum[nu] = sd.top();
				sd.pop();
				nu++; 
			}
			cout << std::left << setw(8) << step++;
			while(er)
			{
				er--;
				sout += oper[er];
				sc.push(oper[er]);
			}
			cout << std::left << setw(40) << sout;
			sout = "";
			while(nu)
			{
				nu--;
				cout << opnum[nu] << " ";
				sd.push(opnum[nu]);
			}
			cout<<"      输入字符: " << s[cnt] <<endl; 
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
			while(!sc.empty())
			{
				oper[er] = sc.top();
				sc.pop();
				er++;
			}
			while(!sd.empty())
			{
				opnum[nu] = sd.top();
				sd.pop();
				nu++; 
			}
			cout << std::left << setw(8) << step++;
			while(er)
			{
				er--;
				sout += oper[er];
				sc.push(oper[er]);
			}
			cout << std::left << setw(40) << sout;
			sout = "";
			while(nu)
			{
				nu--;
				cout << opnum[nu] << " ";
				sd.push(opnum[nu]);
			}
			cout<<"      输入字符: " << c <<endl; 			
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
				
			}
			p = -1;
		}
		cnt++;
	}
	while(!sc.empty())
	{
		oper[er] = sc.top();
		sc.pop();
		er++;
	}
	while(!sd.empty())
	{
		opnum[nu] = sd.top();
		sd.pop();
		nu++; 
	}
	cout << std::left << setw(8) << step++;
	while(er)
	{
		er--;
		sout += oper[er];
		sc.push(oper[er]);
	}
	cout << std::left << setw(40) << sout;
	sout = "";
	while(nu)
	{
		nu--;
		cout << opnum[nu] << " ";
		sd.push(opnum[nu]);
	}
	cout<<"      输入字符: " << "#" << endl << endl << endl; 
}


int main()                                                 //主函数 
{
	bool test = 0;
	char pick = '1';
	string s1;
	cout << "                                     欢迎使用计算器" << endl << endl;
	cout << "      使用说明:本计算器可以进行四则运算和幂运算，直接输入合法的式子就可以计算得出结果。" << endl;
	cout <<"      使用注意事项:输入的式子的格式一定要正确，不包含空格，" << endl << "      只能输入的字符包括  数字 0 ~ 9 ，英式小括号 ( )，加减乘除号和乘方号 + - * / ^ ，小数点 . " << endl << endl; 
	while (pick != '0')
	{
		cout << "请输入式子:" << endl; 
		cin >> s1;
		test = check(s1);
		while (test == 0)
		{
			cout << "输入的式子的格式有误，请重新输入！" << endl;
			cin >> s1;
			test = check(s1);
		}
		cout << "答案:"; 
		cal(s1);
		pick = '1';
		while(pick == '1')
		{
			cout << endl << "输入 1 输出计算过程， 输入其他进行下一次计算， 输入 0 结束程序" << endl;
			cin >> pick; 
			if(pick == '1')
			{
				print_stack(s1);
			}
		}
		cout << endl << endl;
//	    system("pause");
//		system("cls");
	} 
	return 0;
} 
