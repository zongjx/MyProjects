#ifndef PLAYER_H
#define PLAYER_H
//**************************************************************************** class player
class player                                                              //base class
{
	public:
		player();                                                         //constructor of player
		player(string&);                                                  //constructor of player
	    ~player();                                                        //distructor of player
	    void inputDigits(digits&);                                        //input digits;
	    string getName();                                                 //return name
	private:
		string name;                                                      //storge the name of the player
		digits inputDigits_;                                              //storge the number which player inputed
};
//**************************************************************************** class player

player::player()
{
	name="player";
}

player::player(string& name_)
{
	name=name_;
}

player::~player()
{
	
}

void player::inputDigits(digits& d)
{
	inputDigits_=d;
}

string player::getName()
{
	return name;
}
#endif
