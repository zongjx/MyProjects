//È¥³ý×Ö·û´®ÖÐ¿Õ¸ñ 


#include <iostream>
#include <string>
#include <string.h>
#include <cstring>
using namespace std;
int main()
{
	string s,s1;
	char a;
	getline(cin,s,'\n');
	int size,k=0;
	size=s.length();
	for(int i=0;i<size;i++)
	{
		if(s.at(i)==' ')
		{
			s.replace(i,1,"");
			size--;
			i--;
		}
	} 
	cout<<s<<endl;
}
