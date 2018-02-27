#include <iostream>
#include <string>
#include <string.h>
#include <cstdlib>
#include <ctime>
using namespace std;
#include "digits.h"
#include "player.h"
#include "playerHuman.h"
#include "playerComputer.h"
#include "game.h"
int main()                                                                //main function
{
	game g1;
	g1.gameCreate();
	cout<<endl<<endl<<"****************游戏结束！欢迎下次再来玩！****************"<<endl; 
	system("pause");
	return 0;
}
