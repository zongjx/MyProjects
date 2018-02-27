#include <iostream>
#include <iomanip>
#include <string>
#include <stack> 
#include <cmath>

using namespace std;


bool check(string s)                                       //��������ʽ�ӵĸ�ʽ�Ƿ�����ĺ��� 
{
	int l = 0,bra = 0;
	l = s.length();
	for (int i = 0 ; i < l ; i++)                          //���ʽ�����Ƿ��зǷ��ַ� 
	{ 
		if ( (s[i] < 48 || s[i] > 57) && s[i] != '(' && s[i] != ')' && s[i] != '+' && s[i] != '-' && s[i] != '*' && s[i] != '/' && s[i] != '^' && s[i] != '.')
		{
			return false;
			break;
		}
	}
	for (int i = 0 ; i < l ; i++)                          //���ʽ�ӵĸ�ʽ�Ƿ����� 
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
	if ( (s[0] < 48 || s[0] > 57) && s[0] != '(' && s[0] != '-')    //���ʽ�ӵ�һ���ַ� 
	return false;                                                    
	if (bra>0)                                             //���Ÿ�ʽ��� 
	return false;
	return true;
}


void cal(string st)                                        //����ʽ�ӽ���ĺ��� 
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
	while (cnt <= l)                                       //���� 
	{
		c = 0;
		t = 1;
		e1 = 0;
		e2 = 0;
		ex = 0;
		if (s[cnt] < 48 || s[cnt] > 57)                    //���������ֵ���� 
		{
			
		}
		if (s[cnt] == '.')                                 //������С��������
		{
			p = cnt;
	    }
		if (s[cnt] == '(')                                 //�����������ŵ���� 
		{
			front = cnt;
			sc.push('(');
		}
		if (s[cnt] == '+')                                 //�������Ӻŵ���� 
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
		if (s[cnt] == '-')                            //���������ŵ���� 
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
	    if (s[cnt] == '*')                            //�������˺ŵ���� 
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
		if (s[cnt] == '/')                            //���������ŵ���� 
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
		if (s[cnt] == ')')                            //�����������ŵ���� 
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
		if (s[cnt] == '^')                            //�������˷��ŵ���� 
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
		if (s[cnt] == '#')                            //���������ŵ���� 
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


void print_stack(string st)                                //��һ����������һ��������ʵ���һ����ֻ�������������������̣�������������ջ������ݵ���� 
{                                                          //ʹ�����ܹ�����ջ�ı仯���� 
	cout << std::left << setw(8) << "����" << std::left << setw(40) << "������ջ" << std::left << setw(40) << "������ջ" << endl; 
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
	while (cnt <= l)                                       //���� 
	{
		c = 0;
		t = 1;
		e1 = 0;
		e2 = 0;
		ex = 0;
		if (s[cnt] < 48 || s[cnt] > 57)                    //���������ֵ���� 
		{
			
		}
		if (s[cnt] == '.')                                 //������С��������
		{
			p = cnt;
	    }
		if (s[cnt] == '(')                                 //�����������ŵ���� 
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
			cout<<"      �����ַ�: " << s[cnt] <<endl;
			front = cnt;
			sc.push('(');
		}
		if (s[cnt] == '+')                                 //�������Ӻŵ���� 
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
			cout<<"      �����ַ�: " << c <<endl; 
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
			cout<<"      �����ַ�: " << s[cnt] <<endl; 
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
		if (s[cnt] == '-')                            //���������ŵ���� 
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
			cout<<"      �����ַ�: " << c <<endl; 
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
			cout<<"      �����ַ�: " << s[cnt] <<endl; 
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
	    if (s[cnt] == '*')                            //�������˺ŵ���� 
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
			cout<<"      �����ַ�: " << c <<endl; 
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
			cout<<"      �����ַ�: " << s[cnt] <<endl; 
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
		if (s[cnt] == '/')                            //���������ŵ���� 
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
			cout<<"      �����ַ�: " << c <<endl; 
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
			cout<<"      �����ַ�: " << s[cnt] <<endl; 
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
		if (s[cnt] == ')')                            //�����������ŵ���� 
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
			cout<<"      �����ַ�: " << c <<endl; 
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
			cout<<"      �����ַ�: " << s[cnt] <<endl; 
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
			cout<<"      �����ַ�: " << s[cnt] <<endl; 
				if(sc.top() == '(')
				sc.pop();
			}
			front = cnt;
			p = -1;
		}
		if (s[cnt] == '^')                            //�������˷��ŵ���� 
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
			cout<<"      �����ַ�: " << c <<endl; 
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
			cout<<"      �����ַ�: " << s[cnt] <<endl; 
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
		if (s[cnt] == '#')                            //���������ŵ���� 
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
			cout<<"      �����ַ�: " << c <<endl; 			
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
	cout<<"      �����ַ�: " << "#" << endl << endl << endl; 
}


int main()                                                 //������ 
{
	bool test = 0;
	char pick = '1';
	string s1;
	cout << "                                     ��ӭʹ�ü�����" << endl << endl;
	cout << "      ʹ��˵��:�����������Խ�����������������㣬ֱ������Ϸ���ʽ�ӾͿ��Լ���ó������" << endl;
	cout <<"      ʹ��ע������:�����ʽ�ӵĸ�ʽһ��Ҫ��ȷ���������ո�" << endl << "      ֻ��������ַ�����  ���� 0 ~ 9 ��ӢʽС���� ( )���Ӽ��˳��źͳ˷��� + - * / ^ ��С���� . " << endl << endl; 
	while (pick != '0')
	{
		cout << "������ʽ��:" << endl; 
		cin >> s1;
		test = check(s1);
		while (test == 0)
		{
			cout << "�����ʽ�ӵĸ�ʽ�������������룡" << endl;
			cin >> s1;
			test = check(s1);
		}
		cout << "��:"; 
		cal(s1);
		pick = '1';
		while(pick == '1')
		{
			cout << endl << "���� 1 ���������̣� ��������������һ�μ��㣬 ���� 0 ��������" << endl;
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
