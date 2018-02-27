#ifndef PLAYERHUMAN_H
#define PLAYERHUMAN_H
//**************************************************************************** class playerHuman
class playerHuman:public player                                           //derived class
{
	public:
		playerHuman(string&);                                             //constructor of playerHuman
	    ~playerHuman();                                                   //distructor of playerHuman
};
//**************************************************************************** class playerHuman

playerHuman::playerHuman(string& s):player(s)
{
	
}

playerHuman::~playerHuman()
{
	
}
#endif
